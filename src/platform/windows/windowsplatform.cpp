#include "windowsplatform.h"

#include <iostream>
#include <chrono>
#include "strsafe.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

namespace uniplatform
{
    LRESULT CALLBACK sWndProc(HWND, UINT, WPARAM, LPARAM);

    WindowsPlatform::WindowsPlatform(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
        :m_hInstance(hInstance),
        m_hPrevInstance(hPrevInstance),
        m_lpCmdLine(lpCmdLine),
        m_nCmdShow(nCmdShow)
    {

    }

    void WindowsPlatform::Startup()
    {
        WNDCLASSEX wndclass;
        wndclass.cbSize = sizeof(WNDCLASSEX);
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = sWndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = m_hInstance;
        wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);

        wndclass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
        wndclass.lpszMenuName = nullptr;
        wndclass.lpszClassName = TEXT("Unicorn Engine Window Class");
        RegisterClassEx(&wndclass);

        const TCHAR lpWindowName[] = TEXT("Unicorn Engine");

        m_HWnd = CreateWindow(
            wndclass.lpszClassName,
            lpWindowName,
            WS_OVERLAPPEDWINDOW,
            300, 300,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            nullptr, nullptr, m_hInstance, nullptr);

        if (m_HWnd == nullptr)
        {
            std::cout << "CreateWindow exploded: " << GetLastError() << std::endl;
        }

        SetWindowLongPtr(m_HWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        ShowWindow(m_HWnd, m_nCmdShow);
        UpdateWindow(m_HWnd);

        // m_Engine->GetRenderManager().SetHwnd(m_HWnd);
        // 
        // m_Engine->Startup();
    }

    void WindowsPlatform::Update()
    {
        // static auto prev = std::chrono::high_resolution_clock::now();
        // auto now = std::chrono::high_resolution_clock::now();
        // auto durationNano = now - prev;
        // TCHAR text[256];
        // StringCchPrintf(text, 256, TEXT("fps:%f, milliseconds:%f"), 
        //     1000000000.0/max(1.0, static_cast<double>(durationNano.count())),
        //     static_cast<double>(durationNano.count()) / 1000000.0
        // );
        // prev = now;
        // SetWindowText(m_HWnd, text);

        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }

    void WindowsPlatform::Shutdown()
    {
        // m_Engine->Shutdown();
    }

    void WindowsPlatform::RegisterWindowCloseEvent(const std::function<WindowsEventFunc>& func)
    {
        m_OnWindowCloseEvent = func;
    }

    void WindowsPlatform::RegisterRawInputEvent(const std::function<WindowsEventFunc>& func)
    {
        m_OnRawInputEvent = func;
    }

    LRESULT WindowsPlatform::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (iMsg)
        {
        case WM_CLOSE:
            if (m_OnWindowCloseEvent)
            {
                m_OnWindowCloseEvent(wParam, lParam);
            }
            break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
        case WM_INPUT:
            if(m_OnRawInputEvent)
            {
                m_OnRawInputEvent(wParam, lParam);
            }
            break;
        default:
            break;
        }
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }

    LRESULT CALLBACK sWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
        LONG_PTR winmgrLP = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        WindowsPlatform* winmgr = reinterpret_cast<WindowsPlatform*>(winmgrLP);

        return WindowsPlatform::WndProc(winmgr, hwnd, iMsg, wParam, lParam);
    }

}

