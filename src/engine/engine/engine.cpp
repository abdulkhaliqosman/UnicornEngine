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

    void Engine::Startup()
    {
        std::cout << "Engine::Startup()" << std::endl;

        m_ThreadManager.AddThread(&m_NetworkThread);

        m_MemoryManager.Startup();
        m_ThreadManager.Startup();
        m_InputManager.Startup();

        m_RenderManager.Init();

        m_EditorServer.Init();

        m_Scene = ucNew(Scene);
        const TCHAR* path = "../content/meshes/mixamogirl.fbx";

        // uniassets::FBXFileAsset::ImportFromFile(path);

        auto* asset = uniassets::GLTFFileAsset::ImportFromFile("../content/meshes/mixamogirl.glb");
        // asset->GetMeshes()
        m_RenderManager.AddMesh(*asset->GetMeshes()[0]);
        m_RenderManager.Startup();
    }

    void Engine::Update()
    {
        m_InputManager.Update();
        m_MemoryManager.Update();
        m_ThreadManager.Update();

        m_Scene->Update();

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
}
