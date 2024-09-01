#include "fpscameracontroller.h"
#include "engine/input/manager/inputmanager.h"

namespace testgame
{
    void FPSCameraController::Update()
    {
        
    }

    void FPSCameraController::UpdateInput()
    {
        // TODO: game input system
        // right stick rotate
        const auto& gamepads = Unicorn::InputManager::GetInstance().GetGamepads();
        const auto& gamepad0 = gamepads.GetGamepad(0);
        if (gamepad0.IsConnected())
        {
            // gamepad0.Get
        }


        ucc::Transform::Rotation(m_Pitch, m_Yaw, 0.0f);

        // left stick move

    }

    void FPSCameraController::UpdateCamera()
    {
        ucr::CameraObject* camera = ucr::RenderManager::GetInstance()->GetActiveCamera();
        camera->SetViewPosition(m_Position);
    }
}