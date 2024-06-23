#pragma once
#include "sceneimguipage.h"
#include "imgui.h"
#include "scene/manager/scenemanager.h"
#include "debugging/debuggingheader.h"
#include "scene/scene.h"

namespace unigamecore
{
    void SceneImguiPage::Update()
    {
        if (ImGui::Begin("Scene"))
        {
            SceneManager* mgr = SceneManager::GetInstance();
            Scene* scene = mgr->GetActiveScene();
            ucd::ImguiSerializer& ser = ucd::ImguiManager::GetSerializer();
            ser.SerializeObject(scene);


            
        }
        ImGui::End();
    }
}
