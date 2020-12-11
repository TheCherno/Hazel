#include "Hazel/Core/Process.h"

namespace Rocket {
    //---------------------------------------------------------------------------------------------------------------------
    // Constructor
    //---------------------------------------------------------------------------------------------------------------------
    Process::Process(void)
    {
        m_state = UNINITIALIZED;
        //m_pParent = NULL;
        //m_pChild = NULL;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Destructor
    //---------------------------------------------------------------------------------------------------------------------
    Process::~Process(void)
    {
        if (m_pChild)
        {
            m_pChild->OnAbort();
        }
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Removes the child from this process.  This releases ownership of the child to the caller and completely removes it
    // from the process chain.
    //---------------------------------------------------------------------------------------------------------------------
    StrongProcessPtr Process::RemoveChild(void)
    {
        if (m_pChild)
        {
            StrongProcessPtr pChild = m_pChild;  // this keeps the child from getting destroyed when we clear it
            m_pChild.reset();
            //pChild->SetParent(NULL);
            return pChild;
        }

        return StrongProcessPtr();
    }
}
