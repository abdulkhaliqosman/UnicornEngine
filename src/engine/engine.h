#pragma once

#include "core/coreheader.h"
#include "input/manager/inputmanager.h"
#include "render/manager/rendermanager.h"
#include "editor/server/editornetworkserver.h"
#include "gamecore/gamecoreheader.h"
#include "debugging/debuggingheader.h"

namespace uniplatform
{
    class  WindowsPlatforma;
}

namespace uniengine
{
    enum class EngineState
    {
        Uninitialized,
        Startup,
        Update,
        Shutdown,
    };

    class Engine
    {
    public:
        Engine();

        void Run();

        void Initialize();
        void Uninitialize();
        void Startup();
        void Update();
        void Shutdown();
        
        inline ucr::RenderManager& GetRenderManager() { return m_RenderManager; }
        inline ucg::SceneManager& GetSceneManager() { return m_SceneManager; }

        inline uniplatform::WindowsPlatform* GetWindowsPlatform() { return m_WindowsPlatform; }
        inline void SetWindowsPlatform(uniplatform::WindowsPlatform* platform) { m_WindowsPlatform = platform; }

    private:
        ucr::RenderManager m_RenderManager;
        uniplatform::WindowsPlatform* m_WindowsPlatform = nullptr;

        EditorNetworkServer m_EditorServer;
        Unicorn::MemoryManager m_MemoryManager;
        Unicorn::ThreadManager m_ThreadManager;
        Unicorn::InputManager m_InputManager;
        ucc::NetworkThread m_NetworkThread;
        ucd::ImguiManager m_ImguiManager;
        ucg::SceneManager m_SceneManager;

        EngineState m_State = EngineState::Uninitialized;
        void FakeSceneUpdate();
    };
}
