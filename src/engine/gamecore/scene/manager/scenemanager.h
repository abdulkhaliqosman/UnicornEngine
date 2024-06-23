#pragma once

#include "core/coreheader.h"
#include "scene/scene.h"

namespace unigamecore
{
    class SceneManager
    {
    public:
        static SceneManager* GetInstance() { return ms_Instance; }

        void Init();
        void Startup();
        void Update();

        void LoadScene(Scene* scene);
        void UnloadScene(Scene* scene);

        void SaveScene(Scene* scene, const TCHAR* path);
        Scene* LoadScene(const TCHAR* path);

        Scene* GetActiveScene() { return m_ActiveScene; }
        const Scene* GetActiveScene() const { return m_ActiveScene; }

    private:
        Scene* m_ActiveScene = nullptr;
        static inline SceneManager* ms_Instance = nullptr;
    };
}
