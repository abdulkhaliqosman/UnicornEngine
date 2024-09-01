#pragma once

#include "debugging/debuggingheader.h"

namespace unigamecore
{
    class SceneImguiPage : public ucd::ImguiPage
    {
    public:
        void Update() override;
        inline const char* GetMenu() override { return "GameCore"; }
        inline const char* GetMenuItem() override { return "Scene"; } 
    private:

    };
}