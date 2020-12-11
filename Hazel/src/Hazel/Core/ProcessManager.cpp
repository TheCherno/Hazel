#include "Hazel/Core/ProcessManager.h"

namespace Rocket {
    ProcessManager* g_ProcessManager = new ProcessManager();

    int ProcessManager::Initialize()
    {
        return 0;
    }

    void ProcessManager::Finalize()
    {
        AbortAllProcesses(true);
        m_ProcessList.clear();
    }

    int ProcessManager::Tick(Timestep ts)
    {
        uint64_t result_i = UpdateProcesses(ts.GetMilliseconds());
        //std::stringstream stream;
        //stream << std::hex << result_i;
        //std::string result( stream.str() );
        //RK_CORE_TRACE("Process Manager Tick Result {0}", result);
        return result_i;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // The process update tick.  Called every logic tick.  This function returns the number of process chains that 
    // succeeded in the upper 32 bits and the number of process chains that failed or were aborted in the lower 32 bits.
    //---------------------------------------------------------------------------------------------------------------------
    uint64_t ProcessManager::UpdateProcesses(unsigned long deltaMs)
    {
        uint64_t successCount = 0;
        uint64_t failCount = 0;

        ProcessList::iterator it = m_ProcessList.begin();
        while (it != m_ProcessList.end())
        {
            // grab the next process
            StrongProcessPtr pCurrProcess = (*it);

            // save the iterator and increment the old one in case we need to remove this process from the list
            ProcessList::iterator thisIt = it;
            ++it;

            // process is uninitialized, so initialize it
            if (pCurrProcess->GetState() == Process::UNINITIALIZED)
                pCurrProcess->OnInit();

            // give the process an update tick if it's running
            if (pCurrProcess->GetState() == Process::RUNNING)
                pCurrProcess->OnUpdate(deltaMs);

            // check to see if the process is dead
            if (pCurrProcess->IsDead())
            {
                // run the appropriate exit function
                switch (pCurrProcess->GetState())
                {
                    case Process::SUCCEEDED :
                    {
                        pCurrProcess->OnSuccess();
                        StrongProcessPtr pChild = pCurrProcess->RemoveChild();
                        if (pChild)
                            AttachProcess(pChild);
                        else
                            ++successCount;  // only counts if the whole chain completed
                        break;
                    }

                    case Process::FAILED :
                    {
                        pCurrProcess->OnFail();
                        ++failCount;
                        break;
                    }

                    case Process::ABORTED :
                    {
                        pCurrProcess->OnAbort();
                        ++failCount;
                        break;
                    }

                    default: break;
                }

                // remove the process and destroy it
                m_ProcessList.erase(thisIt);
            }
        }

        return (static_cast<uint64_t>(successCount << 32) | static_cast<uint64_t>(failCount));
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Attaches the process to the process list so it can be run on the next update.
    //---------------------------------------------------------------------------------------------------------------------
    WeakProcessPtr ProcessManager::AttachProcess(StrongProcessPtr pProcess)
    {
        m_ProcessList.push_front(pProcess);
        return WeakProcessPtr(pProcess);
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Aborts all processes.  If immediate == true, it immediately calls each ones OnAbort() function and destroys all 
    // the processes.
    //---------------------------------------------------------------------------------------------------------------------
    void ProcessManager::AbortAllProcesses(bool immediate)
    {
        ProcessList::iterator it = m_ProcessList.begin();
        while (it != m_ProcessList.end())
        {
            ProcessList::iterator tempIt = it;
            ++it;

            StrongProcessPtr pProcess = *tempIt;
            if (pProcess->IsAlive())
            {
                pProcess->SetState(Process::ABORTED);
                if (immediate)
                {
                    pProcess->OnAbort();
                    m_ProcessList.erase(tempIt);
                }
            }
        }
    }
}
