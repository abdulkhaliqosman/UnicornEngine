#pragma once

#include "core/coreheader.h"

#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>


namespace unirender
{
    struct MVP
    {
        uc::Matrix4f model = uc::Matrix4f::Identity();
        uc::Matrix4f view = uc::Matrix4f::Identity();
        uc::Matrix4f projection = uc::Matrix4f::Identity();
    };

    class RenderObject;

	class RenderManager
	{
	public:
		RenderManager(unicore::Core& core);
		void Startup();
		void Update();
		void Shutdown();
        void LoadShaders();

        ID3D11Buffer* CreateVertexBuffer(uint32_t size, const void* src);
        ID3D11Buffer* CreateIndexBuffer(uint32_t size, const void* src);

        ID3D11Buffer* CreateConstantBuffer(uint32_t size);

        void SetHwnd(HWND hWnd) { m_Hwnd = hWnd; }

        inline void SetProjectionMatrix(const uc::Matrix4f& mat) { m_MVP.projection = mat; }
        inline void SetViewMatrix(const uc::Matrix4f& mat) { m_MVP.view = mat; }
        inline void SetModelMatrix(const uc::Matrix4f& mat) { m_MVP.model = mat; }

    private:

        void CreateSwapChain();
        void CreateRenderTarget();

        ID3D11Buffer* CreateSubresourceBuffer(D3D11_BIND_FLAG bindFlag, uint32_t size, const void* src);

        void CopyMappedBuffer(ID3D11Buffer* buffer, const void* data, size_t size);

        void UpdateMVPCBuffer();

        HWND m_Hwnd;

        IDXGISwapChain* m_SwapChain;
        ID3D11Device* m_Device;
        ID3D11DeviceContext* m_DeviceContext;

        ID3D11RenderTargetView* m_BackBuffer;

        ID3D11VertexShader* m_VertexShader;
        ID3D11PixelShader* m_PixelShader;

        ID3D11Buffer* m_ConstantBuffer;

        ID3D11InputLayout* m_InputLayout;

        MVP m_MVP;

        uc::List<RenderObject*> m_RenderObjects;

		unicore::Core& m_Core;
	};
}
