#include "scenemanager.h"
#include "scene/imgui/sceneimguipage.h"

namespace unigamecore
{
    void SceneManager::Init()
    {
        assert(ms_Instance == nullptr);
        ms_Instance = this;
    }

    void SceneManager::Startup()
    {
        SceneImguiPage* page = ucNew(SceneImguiPage);

        ucd::ImguiManager::GetInstance()->AddPage(page);
    }

    void SceneManager::Update()
    {
        switch(m_ActiveScene->GetState())
        {
        case SceneState::Startup:
        {
            m_ActiveScene->Startup();
            break;
        }
        case SceneState::Update:
        {
            m_ActiveScene->Update();
            break;
        }
        case SceneState::Shutdown:
        {
            m_ActiveScene->Shutdown();
        }
        default:
        {
            break;
        }
        }
    }

    void SceneManager::LoadScene(Scene* scene)
    {
        // TODO: Assert is uninitialized
        scene->Initialize();
        m_ActiveScene = scene;
    }

    void SceneManager::UnloadScene(Scene* scene)
    {

    }

    void SceneManager::SaveScene(Scene* scene, const TCHAR* path)
    {

    }

    Scene* SceneManager::LoadScene(const TCHAR* path)
    {

    }
}
