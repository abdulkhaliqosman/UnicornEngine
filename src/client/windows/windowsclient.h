#pragma once

#include "engine/engineheader.h"

#include <functional>

namespace uniclient
{
    struct WindowsParams
    {
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        LPTSTR    lpCmdLine;
        int       nCmdShow;
    };

    class WindowsClient
    {
    public:
        WindowsClient(const WindowsParams& params);

        inline void SetEngine(uce::Engine* engine) { m_Engine = engine; }

        void Run();

        void Startup();
        void Update();
        void Shutdown();

        inline HWND GetHWnd() { return m_HWnd; }

        void RegisterWindowCloseEvent(const std::function<void()>&);
        void RegisterRawInputEvent(const std::function<void(WPARAM, LPARAM)>&);

        inline static LRESULT WndProc(WindowsClient* mgr, HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
        {
            return mgr->WndProc(hwnd, iMsg, wParam, lParam);
        }

    private:

        HINSTANCE m_hInstance;
        HINSTANCE m_hPrevInstance;
        LPTSTR    m_lpCmdLine;
        int       m_nCmdShow;
        
        HWND m_HWnd;

        ucc::List<std::function<void()> > m_OnWindowCloseEvent;
        ucc::List<std::function<void(WPARAM, LPARAM)> > m_OnRawInputEvent;

        uce::Engine* m_Engine = nullptr;

        LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
    };
}
