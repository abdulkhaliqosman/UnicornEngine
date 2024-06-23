#pragma once

#include "engine/engineheader.h"

namespace testgame
{
    class TestScene : public ucg::Scene
    {
    public:
        inline TestScene(ucc::InstanceID id, const ucc::String& name) : Scene(id, name) {}
        inline ~TestScene() override {}

        inline const char* GetClassStr() const override { return "TestScene"; }

        void Startup() override;
        void Update() override;
        void Shutdown() override;
    };
}
