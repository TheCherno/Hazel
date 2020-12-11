#pragma once
#include "Hazel/Core/Process.h"

namespace Hazel {
    class ProcessManager
    {
    public:
        ProcessManager() {}
        virtual ~ProcessManager() = default;

        virtual int Initialize();
        virtual void Finalize();

        virtual int Tick(Timestep ts);

        // interface
        uint64_t UpdateProcesses(unsigned long deltaMs);  // updates all attached processes
        WeakProcessPtr AttachProcess(StrongProcessPtr pProcess);  // attaches a process to the process mgr
        void AbortAllProcesses(bool immediate);

        // accessors
        unsigned int GetProcessCount(void) const { return m_ProcessList.size(); }
    private:
        typedef std::list<StrongProcessPtr> ProcessList;
	    ProcessList m_ProcessList;
    };

    extern ProcessManager* g_ProcessManager;
}
