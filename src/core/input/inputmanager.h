#pragma once

#include <Windows.h>

namespace unicore
{
    class Core;

    class InputManager
    {
    public:
        InputManager(Core& core);
        void Startup();
        void Update();
        void Shutdown();

    private:
        void OnRawInputEvent(WPARAM wParam, LPARAM lParam);

        Core& m_Core;
    };
}
