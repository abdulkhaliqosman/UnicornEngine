#pragma once

#include "platform/windows/windowsplatform.h"
#include "input/keyboard/keyboardinput.h"
#include "input/gamepad/gamepadinput.h"

namespace Unicorn
{   
    class InputManager
    {
    public:
        static InputManager& GetInstance() { return *ms_Instance; }

        void Init();
        void Startup();
        void Update();
        void Shutdown();

        inline void SetWindowsPlatform(uniplatform::WindowsPlatform* platform) { m_WindowsPlatform = platform; }
        const KeyboardInput& GetKeyboard() const { return m_Keyboard; }
        const GamepadInputList& GetGamepads() const { return m_Gamepads; }

    private:
        void OnRawInputEvent(WPARAM wParam, LPARAM lParam);
        
        KeyboardInput m_Keyboard;
        GamepadInputList m_Gamepads;

        uniplatform::WindowsPlatform* m_WindowsPlatform = nullptr;
        static inline InputManager* ms_Instance = nullptr;
    };
}
