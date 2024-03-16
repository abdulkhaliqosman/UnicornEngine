#pragma once

#include "core/coreheader.h"
#include "render/renderheader.h"

#include <Windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <dxgi1_3.h>

namespace unirender
{
    class MeshObject;
    class TextureObject;
    class MaterialObject;
    class CameraObject;
    class RenderObject;
    class RenderInstance;

    struct MVP
    {
        ucc::Matrix4x4f model = ucc::Matrix4x4f::Identity();
        ucc::Matrix4x4f view = ucc::Matrix4x4f::Identity();
        ucc::Matrix4x4f projection = ucc::Matrix4x4f::Identity();
    };

    struct ConstantBufferData
    {
        ucc::Matrix4x4f mvp = ucc::Matrix4x4f::Identity();
        ucc::Matrix4x4f model = ucc::Matrix4x4f::Identity();
    };

    struct WindowSize
    {
        uint32_t width = 0;
        uint32_t height = 0;
    };

	class RenderManager
	{
	public:
        void Init();
		void Startup();
        void PreUpdate();
		void Update();
		void PostUpdate();
		void Shutdown();
        void LoadShaders();

        // Asset Creators

        MeshObject* CreateMeshObject(const uca::MeshAsset& meshAsset);
        TextureObject* CreateTextureObject(const uca::TextureAsset& meshAsset);
        MaterialObject* CreateMaterialObject(const uca::MaterialAsset& meshAsset);
        RenderObject* CreateRenderObject();
        
        // Camera
        CameraObject* AddCamera();
        inline void SetActiveCamera(CameraObject* camera) { m_ActiveCamera = camera; } // must exist in the list
        CameraObject* GetActiveCamera() { return m_ActiveCamera; } // must exist in the list

        // render specific creators
        ID3D11Buffer* CreateVertexBuffer(uint32_t size, const void* src);
        ID3D11Buffer* CreateIndexBuffer(uint32_t size, const void* src);
        ID3D11Buffer* CreateConstantBuffer(uint32_t size);

        void SetHwnd(HWND hWnd) { m_Hwnd = hWnd; }


        ID3D11Device* GetDevice() { return m_Device; }
        ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext; }


        inline void SetProjectionMatrix(const ucc::Matrix4x4f& mat) { m_MVP.projection = mat; }
        inline void SetViewMatrix(const ucc::Matrix4x4f& mat) { m_MVP.view = mat; }
        inline void SetModelMatrix(const ucc::Matrix4x4f& mat) { m_MVP.model = mat; }

        void OnWindowResizeEvent(UINT width, UINT height);
    private:

        // create
        void CreateDeviceResources();
        void CreateWindowSizeDependentResources();
        void ReleaseWindowSizeDependentResources();

        void CreateFactory();
        void CreateDevice();

        void CreateSwapChain();
        void CreateRenderTargetView();
        void CreateDepthStencilView();

        void CreateSamplerState();

        void SetViewports();
        void ResizeSwapChain();

        // set
        void ClearBackBuffer();
        void Render();
        void PresentSwapChain();
        ID3D11Buffer* CreateSubresourceBuffer(D3D11_BIND_FLAG bindFlag, uint32_t size, const void* src);

        void CopyMappedBuffer(ID3D11Buffer* buffer, const void* data, size_t size);

        void CreateTexture2DBuffer(const uca::TextureAsset& tex, ID3D11Texture2D*& outTex, ID3D11ShaderResourceView*& outSrv);

        void UpdateConstantBuffer();

        HWND m_Hwnd = nullptr;

        IDXGIFactory2* m_Factory = nullptr;

        ID3D11Device* m_Device = nullptr;
        ID3D11DeviceContext* m_DeviceContext = nullptr;

        IDXGISwapChain1* m_SwapChain = nullptr;

        ID3D11RenderTargetView* m_BackBuffer = nullptr;

        ID3D11Texture2D* m_DepthStencilBuffer = nullptr;
        ID3D11DepthStencilView* m_DepthStencilView = nullptr;
        
        ID3D11VertexShader* m_VertexShader = nullptr;
        ID3D11PixelShader* m_PixelShader = nullptr;

        ID3D11Buffer* m_ConstantBuffer = nullptr;

        ID3D11InputLayout* m_InputLayout = nullptr;

        MVP m_MVP;

        ID3D11SamplerState* m_SamplerState = nullptr;

        CameraObject* m_ActiveCamera = nullptr;

        ucc::List<MeshObject*> m_MeshObjects;
        ucc::List<TextureObject*> m_TextureObjects;
        ucc::List<MaterialObject*> m_MaterialObjects;
        ucc::List<RenderObject*> m_RenderObjects;
        ucc::List<CameraObject*> m_CameraObjects;

        WindowSize m_WindowSize;
	};
}
