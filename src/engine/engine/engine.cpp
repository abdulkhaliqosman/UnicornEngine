#include "engine.h"
#include <iostream>

namespace uniengine
{
    Engine::Engine()
    {

    }

    void Engine::Startup()
    {
        std::cout << "Engine::Startup()" << std::endl;

        m_ThreadManager.AddThread(&m_NetworkThread);

        m_MemoryManager.Startup();
        m_ThreadManager.Startup();
        m_InputManager.Startup();

        m_RenderManager.Startup();

        m_EditorServer.Init();
    }

    void Engine::Update()
    {
        m_InputManager.Update();
        m_MemoryManager.Update();
        m_ThreadManager.Update();

        m_RenderManager.Update();
        m_EditorServer.Update();

    }

    void Engine::Shutdown()
    {
        std::cout << "Engine::Shutdown()" << std::endl;
        m_RenderManager.Shutdown();

        m_InputManager.Shutdown();
        m_ThreadManager.Shutdown();
        m_MemoryManager.Shutdown();

    }
}
