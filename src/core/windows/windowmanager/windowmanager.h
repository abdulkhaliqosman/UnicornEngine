#pragma once

#include <Windows.h>
#include <functional>
#include "core/container/list.h"

namespace unicore
{
    struct WindowsParams
    {
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        LPTSTR    lpCmdLine;
        int       nCmdShow;
    };

    class WindowManager
    {
    public:
        WindowManager(const WindowsParams& params);
        void Startup();
        void Update();
        void Shutdown();

        inline HWND GetHWnd() { return m_HWnd; }

        void RegisterWindowCloseEvent(const std::function<void()>&);
        void RegisterRawInputEvent(const std::function<void(WPARAM, LPARAM)>&);

        inline static LRESULT WndProc(WindowManager* mgr, HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
        {
            return mgr->WndProc(hwnd, iMsg, wParam, lParam);
        }

    private:

        HINSTANCE m_hInstance;
        HINSTANCE m_hPrevInstance;
        LPTSTR    m_lpCmdLine;
        int       m_nCmdShow;
        
        HWND m_HWnd;

        List<std::function<void()> > m_OnWindowCloseEvent;
        List<std::function<void(WPARAM, LPARAM)> > m_OnRawInputEvent;

        LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
    };
}
