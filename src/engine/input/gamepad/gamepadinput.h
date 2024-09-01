#pragma once

#include <Windows.h>
#include <Xinput.h>
#include <cstdint>
#include "core/math/math.h"

namespace Unicorn
{
    class GamepadInput
    {
    public:
        enum class Buttons
        {
            DPAD_UP = 0x0001,
            DPAD_DOWN = 0x0002,
            DPAD_LEFT = 0x0004,
            DPAD_RIGHT = 0x0008,
            START = 0x0010,
            BACK = 0x0020,
            LEFT_THUMB = 0x0040,
            RIGHT_THUMB = 0x0080,
            LEFT_SHOULDER = 0x0100,
            RIGHT_SHOULDER = 0x0200,
            A = 0x1000,
            B = 0x2000,
            X = 0x4000,
            Y = 0x8000
        };

        GamepadInput();
        inline GamepadInput(int i) : m_Index(i) { ZeroMemory(&m_State, sizeof(m_State)); }
        inline bool IsConnected() const { return m_IsConnected; }
        void Update();
        inline bool GetButton(Buttons button) const;
        inline Vector2i16 GetLeftStick() const;
        inline Vector2i16 GetRightStick() const;
    private:
        inline int PrevBuffer() const { return (m_CurrentBuffer + 1) % 2; }
        inline int NextBuffer() const { return PrevBuffer(); }
        XINPUT_STATE m_State[2];

        int m_Index = -1;
        int m_CurrentBuffer = 0;
        bool m_IsConnected = false;
        static constexpr uint16_t DEAD_ZONE = 1024;
    };

    class GamepadInputList
    {
    public:
        GamepadInputList();
        void Update();
        inline const GamepadInput& GetGamepad(int i) const { return m_Inputs[i]; }
        static constexpr int MAX_COUNT = XUSER_MAX_COUNT;
    private:
        GamepadInput m_Inputs [MAX_COUNT];
    };

    bool GamepadInput::GetButton(Buttons button) const
    {
        return (m_State[m_CurrentBuffer].Gamepad.wButtons & static_cast<unsigned short>(button)) != 0;
    }

    Vector2i16 GamepadInput::GetLeftStick() const
    {
        return Vector2i16{ m_State[m_CurrentBuffer].Gamepad.sThumbLX, m_State[m_CurrentBuffer].Gamepad.sThumbLY };
    }

    Vector2i16 GamepadInput::GetRightStick() const
    {
        return Vector2i16{ m_State[m_CurrentBuffer].Gamepad.sThumbRX, m_State[m_CurrentBuffer].Gamepad.sThumbRX };
    }
}
