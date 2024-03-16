#include "engine.h"
#include <iostream>
#include "assets/file/fbx/fbxfileasset.h"
#include "assets/file/gltf/gltffileasset.h"
#include "assets/mesh/meshasset.h"
#include "assets/file/assetfiledata.h"
#include "imgui.h"
#include "extern/imgui/backends/imgui_impl_win32.h"
#include "extern/imgui/backends/imgui_impl_dx11.h"


namespace uniengine
{
    Engine::Engine()
    {

    }

    void Engine::Run()
    {
        Initialize();
        Startup();
        while (1)
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

        m_WindowsPlatform->RegisterWindowResizeEvent([this](UINT width, UINT height) { m_RenderManager.OnWindowResizeEvent(width, height); });

        ID3D11Device* device = m_RenderManager.GetDevice();
        ID3D11DeviceContext* deviceContext = m_RenderManager.GetDeviceContext();

        ImGui::CreateContext();
        
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX11_Init(device, deviceContext);
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

        
        FakeSceneStartup();

        m_RenderManager.Startup();

    }
    
    const ucr::TextureObject* g_debugTexture = nullptr;

    void Engine::Update()
    {
        m_InputManager.Update();
        m_WindowsPlatform->Update();

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::Text("Hello, world!");

        static bool s_ShowDemoWindow = true;
        ImGui::ShowDemoWindow(&s_ShowDemoWindow);

        if (g_debugTexture)
        {
            auto* srv = g_debugTexture->GetSRVAddress();
            auto width = g_debugTexture->GetAsset()->width;
            auto height = g_debugTexture->GetAsset()->height;

            ImGui::Begin("DirectX11 Texture Test");
            ImGui::Text("pointer = %p", *srv);
            ImGui::Text("size = %d x %d", width, height);
            ImGui::Image((void*)g_debugTexture->GetSRV(), ImVec2(height, height));
            ImGui::End();
        }
        

        m_MemoryManager.Update();
        m_ThreadManager.Update();

        // m_Scene->Update();
        FakeSceneUpdate();

        m_RenderManager.Update();
        m_EditorServer.Update();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        m_RenderManager.PostUpdate();
    }

    void Engine::Shutdown()
    {
        std::cout << "Engine::Shutdown()" << std::endl;

        // m_Scene->Shutdown();
        // ucDelete(m_Scene);

        m_RenderManager.Shutdown();

        m_InputManager.Shutdown();
        m_ThreadManager.Shutdown();
        m_MemoryManager.Shutdown();

        ImGui::DestroyContext();
    }

    void Engine::FakeSceneStartup()
    {
        m_Scene = ucNew(ucc::Scene);

        const TCHAR* path = "../content/meshes/mixamogirl.fbx";

        // uniassets::FBXFileAsset::ImportFromFile(path);

        auto* asset = uniassets::GLTFFileAsset::ImportFromFile("../content/meshes/mixamogirl.glb");

        auto* mesh = m_RenderManager.CreateMeshObject(*asset->GetMeshes()[0]);
        auto* material = m_RenderManager.CreateMaterialObject(*asset->GetMaterials()[0]);
        auto* obj = m_RenderManager.CreateRenderObject();

        obj->SetMesh(mesh);
        obj->SetMaterial(material);
        g_debugTexture = material->GetBaseColor();

        constexpr int INST_CNT = 1;

        for (int i = -INST_CNT; i <= INST_CNT; ++i)
        {
            for (int j = -INST_CNT; j <= INST_CNT; ++j)
            {
                for (int k = -INST_CNT; k <= INST_CNT; ++k)
                {
                    auto* inst = obj->CreateInstance();
                    auto sMtx = ucc::Transform::Scale(ucc::Vector4f::One()); // ucc::Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
                    auto tMtx = ucc::Transform::Translation(i * 3.0f, j * 3.0f, k * 3.0f);
                    inst->SetModelTransform(sMtx * tMtx);
                }
            }
        }

        auto* cam = m_RenderManager.AddCamera();

        constexpr float TAN45 = 1.0f;
        constexpr float DEFAULT_NEARPLANE = 0.001f;
        constexpr float DEFAULT_FARPLANE = 1000.0f;
        constexpr float ASPECT_RATIO_16_9 = 16.0f / 9.0f;
        constexpr float ASPECT_RATIO_4_3 = 4.0f / 3.0f;

        float top = TAN45 * DEFAULT_NEARPLANE / ASPECT_RATIO_4_3;
        float right = TAN45 * DEFAULT_NEARPLANE;

        // cam->SetPerspective(DEFAULT_NEARPLANE, DEFAULT_FARPLANE, top, right);
        // cam->SetPerspectiveFov(TAN45, ASPECT_RATIO_4_3, DEFAULT_NEARPLANE, DEFAULT_FARPLANE);
        m_RenderManager.SetActiveCamera(cam);
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
