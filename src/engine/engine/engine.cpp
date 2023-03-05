#include "engine.h"
#include <iostream>

namespace uniengine
{
    Engine::Engine(const EngineParams& params)
        :m_Core(params.coreParams),
        m_RenderManager(m_Core)
    {

    }

    void Engine::Run()
    {
        Startup();
        while(1) // TODO hook up to exit button
        {
            Update();
        }
        Shutdown();
    }

    void Engine::Startup()
    {
        std::cout << "Engine::Startup()" << std::endl;
        m_Core.Startup();
        m_RenderManager.Startup();
    }

    void Engine::Update()
    {
        m_Core.Update();
        m_RenderManager.Update();
    }

    void Engine::Shutdown()
    {
        std::cout << "Engine::Shutdown()" << std::endl;
        m_RenderManager.Shutdown();
        m_Core.Shutdown();

    }
}
