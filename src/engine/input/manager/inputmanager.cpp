#include "inputmanager.h"

#include "core/logging/log.h"
#include "core/memory/memory.h"

#include "platform/windows/windowsplatform.h"

#include <hidusage.h>
#include <strsafe.h>
#include <iostream>

#include "input/imgui/inputimguipage.h"

namespace Unicorn
{
    void InputManager::Init()
    {
        assert(ms_Instance == nullptr);
        ms_Instance = this;
    }

    void InputManager::Startup()
    {
        InputImguiPage* page = ucNew(InputImguiPage);
        ucd::ImguiManager::GetInstance()->AddPage(page);


        constexpr int NUM_DEVICES = 2;
        RAWINPUTDEVICE Rid[NUM_DEVICES];

        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
        Rid[0].dwFlags = 0;
        Rid[0].hwndTarget = nullptr;

        Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
        Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
        Rid[1].dwFlags = 0;
        Rid[1].hwndTarget = nullptr;

        // TODO: learn HID drivers
        // https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/interpreting-hid-reports
		// Rid[2].usUsagePage = HID_USAGE_PAGE_GENERIC;
		// Rid[2].usUsage = HID_USAGE_GENERIC_GAMEPAD;
		// Rid[2].dwFlags = 0;
		// Rid[2].hwndTarget = nullptr;

        if (RegisterRawInputDevices(Rid, NUM_DEVICES, sizeof(Rid[0])) == FALSE)
        {
            //registration failed. Call GetLastError for the cause of the error
        }

        m_WindowsPlatform->RegisterRawInputEvent([this](WPARAM wParam, LPARAM lParam) { this->OnRawInputEvent(wParam, lParam); });
    }

    void InputManager::Update()
    {
        m_Keyboard.SwapBuffer();

		m_Gamepads.Update();
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
            // TODO error out here
            return;
        }

        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
        {
            OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));
        }

        RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);

        // TCHAR szTempOutput[512];

        if (raw->header.dwType == RIM_TYPEKEYBOARD)
        {
            auto idx = raw->data.keyboard.VKey;
            if (raw->data.keyboard.Flags == RI_KEY_MAKE)
            {
                m_Keyboard.SetKey(idx);
            }
            else if (raw->data.keyboard.Flags == RI_KEY_BREAK)
            {
                m_Keyboard.UnsetKey(idx);
            }
            std::cout << "idx: " << (idx) << " Key: " << m_Keyboard.GetKey(idx) << " Down: " << m_Keyboard.GetKeyDown(idx) << " Up: " << m_Keyboard.GetKeyUp(idx) << std::endl;

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
            // else
            // {
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
        else
        {
            ucLogDebug("I am a %d!", raw->header.dwType);
        }

        ucDeleteArray(lpb, dwSize);
    }
}
