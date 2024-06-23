#pragma once

#include "core/coreheader.h"
#include "debugging/imgui/serializer/imguiserializer.h"

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace unidebug
{
    class ImguiPage;

    class ImguiManager
    {
    public:
        static inline ImguiManager* GetInstance() { return ms_Instance; }
        static inline ImguiSerializer& GetSerializer() { return GetInstance()->m_Serializer; }
        void Initialize();
        void EarlyUpdate();
        void LateUpdate();
        void Shutdown();

        inline void SetHwnd(HWND hWnd) { m_HWnd = hWnd; }
        inline void SetDevice(ID3D11Device* device) { m_Device = device; }
        inline void SetDeviceContext(ID3D11DeviceContext* context) { m_DeviceContext = context; }

        void AddPage(ImguiPage* page);
    private:
        void ShowPages();

        HWND m_HWnd = nullptr;
        ID3D11Device* m_Device = nullptr;
        ID3D11DeviceContext* m_DeviceContext = nullptr;

        ImguiSerializer m_Serializer;
        ucc::Dict< const char* , ucc::List< ImguiPage* >> m_Pages;

        static inline ImguiManager* ms_Instance = nullptr;
    };
}
