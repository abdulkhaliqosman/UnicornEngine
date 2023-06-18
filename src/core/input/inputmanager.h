#pragma once

#include <Windows.h>

namespace unicore
{
    class InputManager
    {
    public:
        void Startup();
        void Update();
        void Shutdown();

    private:
        void OnRawInputEvent(WPARAM wParam, LPARAM lParam);

    };
}
