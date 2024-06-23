#include "engine.h"
#include <iostream>

#include "imgui.h"

namespace uniengine
{
    Engine::Engine()
    {

    }

    void Engine::Run()
    {
        Initialize();
        Startup();
        while (m_State == EngineState::Update)
        {
            Update();
        }
        Shutdown();
        Uninitialize();
    }

    void Engine::Initialize()
    {
        std::cout << "Engine::Init()" << std::endl;

        m_WindowsPlatform->Startup();

        HWND hWnd = m_WindowsPlatform->GetHWnd();

        m_RenderManager.SetHwnd(hWnd);
        m_RenderManager.Init();

        

        ID3D11Device* device = m_RenderManager.GetDevice();
        ID3D11DeviceContext* context = m_RenderManager.GetDeviceContext();
        m_ImguiManager.SetHwnd(hWnd);
        m_ImguiManager.SetDevice(device);
        m_ImguiManager.SetDeviceContext(context);

        m_ImguiManager.Initialize();

        m_WindowsPlatform->RegisterWindowResizeEvent([this](UINT width, UINT height) { m_RenderManager.OnWindowResizeEvent(width, height); });
        m_WindowsPlatform->RegisterWindowCloseEvent([this](WPARAM, LPARAM) { m_State = EngineState::Shutdown; });

        m_SceneManager.Init();

        m_State = EngineState::Startup;
    }

    void Engine::Uninitialize()
    {

    }

    void Engine::Startup()
    {
        std::cout << "Engine::Startup()" << std::endl;

        m_ThreadManager.AddThread(&m_NetworkThread);

        m_MemoryManager.Startup();
        m_ThreadManager.Startup();

        m_InputManager.SetWindowsPlatform(m_WindowsPlatform);
        m_InputManager.Startup();

        m_EditorServer.Init();

        m_RenderManager.Startup();
        m_SceneManager.Startup();

        m_State = EngineState::Update;
    }
    
    const ucr::TextureObject* g_debugTexture = nullptr;

    void Engine::Update()
    {
        m_InputManager.Update();
        FakeSceneUpdate();
        m_WindowsPlatform->Update();
        m_ImguiManager.EarlyUpdate();

        if (g_debugTexture)
        {
            auto* srv = g_debugTexture->GetSRVAddress();
            auto width = g_debugTexture->GetAsset()->width;
            auto height = g_debugTexture->GetAsset()->height;

            ImGui::Begin("DirectX11 Texture Test");
            ImGui::Text("pointer = %p", *srv);
            ImGui::Text("size = %d x %d", width, height);
            ImGui::Image((void*)g_debugTexture->GetSRV(), ImVec2(width / 4, height / 4));
            ImGui::End();
        }
        
        m_MemoryManager.Update();
        m_ThreadManager.Update();
        m_SceneManager.Update();

        m_RenderManager.Update();
        // m_EditorServer.Update();

        
        m_ImguiManager.LateUpdate();
        m_RenderManager.PostUpdate();
    }

    void Engine::Shutdown()
    {
        std::cout << "Engine::Shutdown()" << std::endl;

        m_RenderManager.Shutdown();

        m_InputManager.Shutdown();
        m_ThreadManager.Shutdown();
        m_MemoryManager.Shutdown();
    }
    
    void Engine::FakeSceneUpdate()
    {
        if (m_InputManager.GetKeyboard().GetKey('R'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, 0.0f, 1.0f / 60.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('F'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, 0.0f, -1.0f / 60.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('A'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(-1.0f / 60.0f, 0.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('D'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(1.0f / 60.0f, 0.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('W'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, 1.0f / 60.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('S'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, -1.0f / 60.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);
        }

        if (m_InputManager.GetKeyboard().GetKey('I'))
        {
            m_RenderManager.GetActiveCamera()->m_Pitch += 1.0f / 60.0f;
        }

        if (m_InputManager.GetKeyboard().GetKey('K'))
        {
            m_RenderManager.GetActiveCamera()->m_Pitch -= 1.0f / 60.0f;
        }

        if (m_InputManager.GetKeyboard().GetKey('J'))
        {
            m_RenderManager.GetActiveCamera()->m_Yaw += 1.0f / 60.0f;
        }

        if (m_InputManager.GetKeyboard().GetKey('L'))
        {
            m_RenderManager.GetActiveCamera()->m_Yaw -= 1.0f / 60.0f;
        }

        if (m_InputManager.GetKeyboard().GetKey('E'))
        {
            m_RenderManager.GetActiveCamera()->SetViewPosition(ucc::Vector4f::Zero());
        }
    }
}
