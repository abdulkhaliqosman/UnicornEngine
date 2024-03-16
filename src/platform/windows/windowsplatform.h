#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <functional>

namespace uniplatform
{
    class WindowsPlatform
    {
    public:
        WindowsPlatform(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

        void Run();

        void Startup();
        void Update();
        void Shutdown();

        inline HWND GetHWnd() { return m_HWnd; }

        using WindowsEventFunc = void(WPARAM, LPARAM);

        void RegisterWindowCloseEvent(const std::function<WindowsEventFunc>&);
        void RegisterRawInputEvent(const std::function<WindowsEventFunc>&);
        void RegisterWindowResizeEvent(const std::function<void(UINT, UINT)>&); // width, height

        inline static LRESULT WndProc(WindowsPlatform* mgr, HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
        {
            return mgr->WndProc(hwnd, iMsg, wParam, lParam);
        }

    private:

        HINSTANCE m_hInstance;
        HINSTANCE m_hPrevInstance;
        LPTSTR    m_lpCmdLine;
        int       m_nCmdShow;

        HWND m_HWnd;

        std::function<WindowsEventFunc> m_OnWindowCloseEvent;
        std::function<WindowsEventFunc> m_OnRawInputEvent;
        std::function<void(UINT, UINT)> m_OnWindowResizeEvent;

        LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
    };
}
