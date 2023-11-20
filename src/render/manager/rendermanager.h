#pragma once

#include "core/coreheader.h"
#include "render/renderheader.h"

#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>


namespace unirender
{
    struct MVP
    {
        ucc::Matrix4x4f model = ucc::Matrix4x4f::Identity();
        ucc::Matrix4x4f view = ucc::Matrix4x4f::Identity();
        ucc::Matrix4x4f projection = ucc::Matrix4x4f::Identity();
    };

    class RenderObject;
    class CameraObject;
    class RenderInstance;

	class RenderManager
	{
	public:
        void Init();
		void Startup();
		void Update();
		void Shutdown();
        void LoadShaders();

        RenderObject* CreateRenderObject(const uca::MeshData& meshData);
        RenderInstance* CreateRenderInstance(const RenderObject* mesh); // TODO: change the ptr to an id
        
        
        CameraObject* AddCamera();
        inline void SetActiveCamera(CameraObject* camera) { m_ActiveCamera = camera; } // must exist in the list
        CameraObject* GetActiveCamera() { return m_ActiveCamera; } // must exist in the list

        ID3D11Buffer* CreateVertexBuffer(uint32_t size, const void* src);
        ID3D11Buffer* CreateIndexBuffer(uint32_t size, const void* src);

        ID3D11Buffer* CreateConstantBuffer(uint32_t size);

        void SetHwnd(HWND hWnd) { m_Hwnd = hWnd; }

        inline void SetProjectionMatrix(const ucc::Matrix4x4f& mat) { m_MVP.projection = mat; }
        inline void SetViewMatrix(const ucc::Matrix4x4f& mat) { m_MVP.view = mat; }
        inline void SetModelMatrix(const ucc::Matrix4x4f& mat) { m_MVP.model = mat; }

    private:

        void CreateSwapChain();
        void CreateRenderTarget();

        ID3D11Buffer* CreateSubresourceBuffer(D3D11_BIND_FLAG bindFlag, uint32_t size, const void* src);

        void CopyMappedBuffer(ID3D11Buffer* buffer, const void* data, size_t size);

        void UpdateMVPCBuffer();

        HWND m_Hwnd = nullptr;

        IDXGISwapChain* m_SwapChain = nullptr;
        ID3D11Device* m_Device = nullptr;
        ID3D11DeviceContext* m_DeviceContext = nullptr;

        ID3D11RenderTargetView* m_BackBuffer = nullptr;

        ID3D11VertexShader* m_VertexShader = nullptr;
        ID3D11PixelShader* m_PixelShader = nullptr;

        ID3D11Buffer* m_ConstantBuffer = nullptr;

        ID3D11InputLayout* m_InputLayout = nullptr;

        MVP m_MVP;

        CameraObject* m_ActiveCamera = nullptr;

        ucc::List<RenderObject*> m_RenderObjects;
        ucc::List<CameraObject*> m_CameraObjects;
	};
}
