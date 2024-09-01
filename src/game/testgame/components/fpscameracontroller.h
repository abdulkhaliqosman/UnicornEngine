#pragma once

#include "engine/engineheader.h"

namespace testgame
{
    class FPSCameraController : public ucg::Component
    {
    public:
        void Update() override;

    private:
        void UpdateInput();
        void UpdateCamera();

        ucc::Vector4f m_Position = ucc::Vector4f::Zero();
        float m_Pitch = 0.0f;
        float m_Yaw = 0.0f;
    };
}