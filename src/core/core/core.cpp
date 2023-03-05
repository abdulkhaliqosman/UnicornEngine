#include "core.h"

namespace unicore
{
    Core::Core(const CoreParams& coreParams)
        :m_MemoryManager(), 
        m_ThreadManager(),
        m_WindowManager(coreParams.windowsParams),
        m_InputManager(*this)
    {


    }

    void Core::Startup()
    {
        m_MemoryManager.Startup();
        m_ThreadManager.Startup();
        m_WindowManager.Startup();
        m_InputManager.Startup();
    }

    void Core::Update()
    {
        m_MemoryManager.Update();
        m_ThreadManager.Update();
        m_WindowManager.Update();
        m_InputManager.Update();
    }

    void Core::Shutdown()
    {
        m_WindowManager.Shutdown();
        m_WindowManager.Shutdown();
        m_ThreadManager.Shutdown();
        m_InputManager.Shutdown();
    }
}
