#include "core/coreheader.h"
#include "windowmanager.h"

#include <iostream>
#include <chrono>
#include "strsafe.h"

LRESULT CALLBACK sWndProc(HWND, UINT, WPARAM, LPARAM);

namespace unicore
{
    WindowManager::WindowManager(const WindowsParams& params)
        :m_hInstance(params.hInstance),
        m_hPrevInstance(params.hPrevInstance),
        m_lpCmdLine(params.lpCmdLine),
        m_nCmdShow(params.nCmdShow)
    {

    }

    void WindowManager::Startup()
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
    }

    void WindowManager::Update()
    {
        static auto prev = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto durationNano = now - prev;
        TCHAR text[256];
        StringCchPrintf(text, 256, TEXT("fps:%f, milliseconds:%f"), 
            1000000000.0/max(1.0, static_cast<double>(durationNano.count())),
            static_cast<double>(durationNano.count()) / 1000000.0
        );
        prev = now;
        SetWindowText(m_HWnd, text);

        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
    }

    void WindowManager::Shutdown()
    {

    }
    
    void WindowManager::RegisterWindowCloseEvent(const std::function<void()>& func)
    {
        m_OnWindowCloseEvent.push_back(func);
    }

    void WindowManager::RegisterRawInputEvent(const std::function<void(WPARAM, LPARAM)>& func)
    {
        m_OnRawInputEvent.push_back(func);
    }

    LRESULT WindowManager::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (iMsg)
        {
        case WM_CLOSE:
            for (const auto& elem : m_OnWindowCloseEvent)
            {
                elem();
            }

            break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
        case WM_INPUT:
            for (const auto& elem : m_OnRawInputEvent)
            {
                elem(wParam, lParam);
            }
            break;
        default:
            break;
        }
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }
}

LRESULT CALLBACK sWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    LONG_PTR winmgrLP = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    unicore::WindowManager* winmgr = reinterpret_cast<unicore::WindowManager*>(winmgrLP);

    return unicore::WindowManager::WndProc(winmgr, hwnd, iMsg, wParam, lParam);
}
