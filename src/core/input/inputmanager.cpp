#include "inputmanager.h"
#include "core/memory/memory.h"

#include <hidusage.h>
#include <strsafe.h>
#include <iostream>

namespace unicore
{
    void InputManager::Startup()
    {
        RAWINPUTDEVICE Rid[2];

        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;          // HID_USAGE_PAGE_GENERIC
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;              // HID_USAGE_GENERIC_MOUSE
        Rid[0].dwFlags = 0;
        Rid[0].hwndTarget = nullptr;

        Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;          // HID_USAGE_PAGE_GENERIC
        Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;              // HID_USAGE_GENERIC_KEYBOARD
        Rid[1].dwFlags = 0;
        Rid[1].hwndTarget = nullptr;

        if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE)
        {
            //registration failed. Call GetLastError for the cause of the error
        }

        // m_Core.GetWindowsClient().RegisterRawInputEvent([this](WPARAM wParam, LPARAM lParam) { this->OnRawInputEvent(wParam, lParam); });
    }

    void InputManager::Update()
    {

    }

    void InputManager::Shutdown()
    {

    }

    void InputManager::OnRawInputEvent(WPARAM wParam, LPARAM lParam)
    {
        UINT dwSize;

        GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
        LPBYTE lpb = ucNewArray(BYTE, dwSize);
        if (lpb == nullptr)
        {
            return;
        }
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
        {
            OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));
        }

        RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);

        TCHAR szTempOutput[512];

        if (raw->header.dwType == RIM_TYPEKEYBOARD)
        {
            // HRESULT hResult = StringCchPrintf(szTempOutput, 512,
            //     TEXT(" Kbd: make=%04x Flags:%04x Reserved:%04x ExtraInformation:%08x, msg=%04x VK=%04x \n"),
            //     raw->data.keyboard.MakeCode,
            //     raw->data.keyboard.Flags,
            //     raw->data.keyboard.Reserved,
            //     raw->data.keyboard.ExtraInformation,
            //     raw->data.keyboard.Message,
            //     raw->data.keyboard.VKey);
            // if (FAILED(hResult))
            // {
            //     // TODO: write error handler
            // }
            // std::cout << (szTempOutput) << std::endl;
        }
        else if (raw->header.dwType == RIM_TYPEMOUSE)
        {
            // HRESULT hResult = StringCchPrintf(szTempOutput, 512,
            //     TEXT("Mouse: usFlags=%04x ulButtons=%04x usButtonFlags=%04x usButtonData=%04x ulRawButtons=%04x lLastX=%04x lLastY=%04x ulExtraInformation=%04x\r\n"),
            //     raw->data.mouse.usFlags,
            //     raw->data.mouse.ulButtons,
            //     raw->data.mouse.usButtonFlags,
            //     raw->data.mouse.usButtonData,
            //     raw->data.mouse.ulRawButtons,
            //     raw->data.mouse.lLastX,
            //     raw->data.mouse.lLastY,
            //     raw->data.mouse.ulExtraInformation);
            // 
            // if (FAILED(hResult))
            // {
            //     // TODO: write error handler
            // }
            // std::cout << (szTempOutput) << std::endl;
        }

        ucDeleteArray(lpb, dwSize);
    }
}
