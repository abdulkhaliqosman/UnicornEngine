#include "engine.h"
#include <iostream>
#include "engine/scene/scene.h"
#include "assets/file/fbx/fbxfileasset.h"
#include "assets/file/gltf/gltffileasset.h"
#include "assets/file/assetfiledata.h"

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

    }

    void Engine::Uninitialize()
    {

    }

    void Engine::Startup()
    {
        std::cout << "Engine::Startup()" << std::endl;

        m_WindowsPlatform->Startup();

        m_RenderManager.SetHwnd(m_WindowsPlatform->GetHWnd());

        m_ThreadManager.AddThread(&m_NetworkThread);

        m_MemoryManager.Startup();
        m_ThreadManager.Startup();

        m_InputManager.SetWindowsPlatform(m_WindowsPlatform);
        m_InputManager.Startup();

        m_RenderManager.Init();

        m_EditorServer.Init();

        m_Scene = ucNew(Scene);
        const TCHAR* path = "../content/meshes/mixamogirl.fbx";

        // uniassets::FBXFileAsset::ImportFromFile(path);

        auto* asset = uniassets::GLTFFileAsset::ImportFromFile("../content/meshes/mixamogirl.glb");
        // asset->GetMeshes()
        auto* obj = m_RenderManager.CreateRenderObject(*asset->GetMeshes()[0]);

        constexpr int INST_CNT = 5;

        for (int i = -INST_CNT; i <= INST_CNT; ++i)
        {
            for (int j = -INST_CNT; j <= INST_CNT; ++j)
            {
                for (int k = -INST_CNT; k <= INST_CNT; ++k)
                {
                    auto* inst = obj->CreateInstance();
                    auto sMtx = ucc::Transform::Scale(ucc::Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
                    auto tMtx = ucc::Transform::Translation(i * 0.2f, j * 0.2f, k * 0.2f);
                    inst->SetModelTransform(tMtx * sMtx);
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

        cam->SetPerspective(DEFAULT_NEARPLANE, DEFAULT_FARPLANE, top, right);
        m_RenderManager.SetActiveCamera(cam);
        m_RenderManager.Startup();
    }

    void Engine::Update()
    {
        m_InputManager.Update();
        m_WindowsPlatform->Update();

        m_MemoryManager.Update();
        m_ThreadManager.Update();

        m_Scene->Update();
        FakeSceneUpdate();
        m_RenderManager.Update();
        m_EditorServer.Update();

    }

    void Engine::Shutdown()
    {
        std::cout << "Engine::Shutdown()" << std::endl;

        m_Scene->Shutdown();
        ucDelete(m_Scene);

        m_RenderManager.Shutdown();

        m_InputManager.Shutdown();
        m_ThreadManager.Shutdown();
        m_MemoryManager.Shutdown();

    }

    void Engine::FakeSceneUpdate()
    {
        if (m_InputManager.GetKeyboard().GetKey('W'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, 0.0f, 1.0f / 60.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);

            std::cout << "x: " << pos.GetX()
                << "y: " << pos.GetY()
                << "z: " << pos.GetZ()
                << "w: " << pos.GetW()
                << std::endl;
        }

        if (m_InputManager.GetKeyboard().GetKey('S'))
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

        if (m_InputManager.GetKeyboard().GetKey('R'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, 1.0f / 60.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);


        }

        if (m_InputManager.GetKeyboard().GetKey('F'))
        {
            auto pos = m_RenderManager.GetActiveCamera()->GetViewPosition();
            pos = pos + ucc::Vector4f(0.0f, -1.0f / 60.0f, 0.0f, 0.0f);
            m_RenderManager.GetActiveCamera()->SetViewPosition(pos);


        }

        if (m_InputManager.GetKeyboard().GetKey('E'))
        {
            m_RenderManager.GetActiveCamera()->SetViewPosition(ucc::Vector4f::Zero());

        }
    }
}
