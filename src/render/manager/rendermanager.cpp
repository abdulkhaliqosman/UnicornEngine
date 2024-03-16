#include "renderheader.h"

#include "rendermanager.h"

#include <iostream>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
static constexpr auto PI_4 = 0.78539816339;
static constexpr auto NEARPLANE = 0.001f;
static constexpr auto FARPLANE = 1000.0f;

namespace unirender
{
    void RenderManager::Init()
    {
        std::cout << "RenderManager::Startup()" << std::endl;
        assert(m_Hwnd != nullptr);
        m_WindowSize.width = SCREEN_WIDTH;
        m_WindowSize.height = SCREEN_HEIGHT;

        CreateDeviceResources();

        CreateWindowSizeDependentResources();


        CreateConstantBuffer(sizeof(ConstantBufferData));

        UpdateConstantBuffer(); // set to identity
    }

    void RenderManager::Startup()
    {
        LoadShaders();
    }
    
    void RenderManager::PreUpdate()
    {
        ClearBackBuffer();
    }

    void RenderManager::Update()
    {
        if (m_DepthStencilView == nullptr)
        {
            return;
        }
        static constexpr float blue[]{ 0.0f, 0.2f, 0.4f, 1.0f };
        FLOAT clearDepth = 1.0f;
        UINT8 clearStencil = 0;
        // clear the back buffer to a deep blue
        m_DeviceContext->ClearRenderTargetView(m_BackBuffer, blue);
        m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);

        // do 3D rendering on the back buffer here
        m_DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, m_DepthStencilView);
        m_DeviceContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

        const UINT stride = sizeof(uca::Vertex);

        // TODO: Replace all DirectX::XM with internal math library
        // 
        // auto vTrans = ucc::Transform::Translation(m_ActiveCamera ? m_ActiveCamera->GetViewPosition() : ucc::Vector4f::Zero());
        // auto vYaw = ucc::Transform::RotationYaw(m_ActiveCamera ? m_ActiveCamera->m_Yaw : 0.0f);
        // auto vPitch = ucc::Transform::RotationPitch(m_ActiveCamera ? m_ActiveCamera->m_Pitch : 0.0f);
        // m_MVP.view = vTrans * vYaw * vPitch;
        // m_MVP.view.Inverse();
        // m_MVP.projection = ucc::Matrix4x4f::Identity();
        // m_MVP.projection = m_ActiveCamera ? m_ActiveCamera->GetProjectionMatrix() : ucc::Matrix4x4f::Identity();

        float aspectratio = float(m_WindowSize.width) / float(m_WindowSize.height);
        auto proj = DirectX::XMMatrixPerspectiveFovLH(PI_4, aspectratio, NEARPLANE, FARPLANE);

        auto vpos = m_ActiveCamera ? m_ActiveCamera->GetViewPosition() : ucc::Vector4f::Zero();
        auto vPitch = m_ActiveCamera ? m_ActiveCamera->m_Pitch : 0.0f;
        auto vYaw = m_ActiveCamera ? m_ActiveCamera->m_Yaw : 0.0f;
        auto vRot = DirectX::XMMatrixRotationRollPitchYaw(vPitch, vYaw, 0.0f);
        auto vLook = DirectX::XMMatrixLookToLH(vpos.GetData(), vRot.r[2], vRot.r[1]);

        m_MVP.view = reinterpret_cast<ucc::Matrix4x4f&>(vLook);
        m_MVP.projection = reinterpret_cast<ucc::Matrix4x4f&>(proj);

        for (const auto* object : m_RenderObjects)
        {
            const MeshObject* mesh = object->GetMesh();
            if (mesh == nullptr)
            {
                continue;
            }
            
            UINT offset = 0;
            ID3D11Buffer* vertexBuffer = mesh->GetVertexBuffer();

            // select which vertex buffer to display
            m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
            m_DeviceContext->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

            // select which primitive type we are using
            m_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            const auto* mat = object->GetMaterial();
            if (mat)
            {
                const auto* basecolor = mat->GetBaseColor();
                if (basecolor)
                {
                    m_DeviceContext->PSSetSamplers(0, 1, &m_SamplerState);
                    m_DeviceContext->PSSetShaderResources(0, 1, basecolor->GetSRVAddress());
                }
            }

            for (const auto* instance : object->GetInstances())
            {
                m_MVP.model = instance->GetModelTransform();
                UpdateConstantBuffer();
                // draw the vertex buffer to the back buffer
                m_DeviceContext->DrawIndexed(mesh->GetIndicesCount(), 0, 0);
            }
        }
    }

    void RenderManager::PostUpdate()
    {
        // switch the back buffer and the front buffer
        m_SwapChain->Present(0, 0);
    }

    void RenderManager::Shutdown()
    {
        std::cout << "RenderManager::Shutdown()" << std::endl;

        for (auto* object : m_RenderObjects)
        {
            object->Shutdown();
            ucDelete(object);
        }
        m_RenderObjects.clear();

        for (auto* object : m_MeshObjects)
        {
            object->Shutdown();
            ucDelete(object);
        }
        m_MeshObjects.clear();

        m_SwapChain->SetFullscreenState(FALSE, nullptr);

        m_VertexShader->Release();
        m_PixelShader->Release();

        m_SwapChain->Release();
        m_BackBuffer->Release();

        m_Device->Release();
        m_DeviceContext->Release();
    }

    void RenderManager::CreateDeviceResources()
    {
        CreateFactory();
        CreateDevice();
        CreateSamplerState();
    }

    void RenderManager::CreateWindowSizeDependentResources()
    {
        CreateSwapChain();
        CreateRenderTargetView();
        CreateDepthStencilView();
        SetViewports();
    }

    void RenderManager::ReleaseWindowSizeDependentResources()
    {
        ID3D11RenderTargetView* nullViews[] = { nullptr };
        m_DeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);

        m_BackBuffer->Release();
        m_BackBuffer = nullptr;

        m_DepthStencilView->Release();
        m_DepthStencilView = nullptr;

        m_DepthStencilBuffer->Release();
        m_DepthStencilBuffer = nullptr;

        m_DeviceContext->Flush();
    }

    void RenderManager::CreateFactory()
    {
        CreateDXGIFactory1(IID_PPV_ARGS(&m_Factory));
    }
    
    void RenderManager::CreateDevice()
    {
        UINT createDeviceFlags = 0;
#if _DEBUG
        createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif
        HRESULT result = D3D11CreateDevice(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, 
            nullptr, 0, D3D11_SDK_VERSION, 
            &m_Device, nullptr, &m_DeviceContext);
        //TODO: verify result == S_OK
    }

    void RenderManager::CreateSwapChain()
    {
        // create a struct to hold information about the swap chain
        DXGI_SWAP_CHAIN_DESC1 scd;

        // clear out the struct for use
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC1));

        // fill the swap chain description struct
        scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
        scd.Width = m_WindowSize.width;  // use 32-bit color
        scd.Height = m_WindowSize.height;  // use 32-bit color

        scd.SampleDesc.Count = 1;             // how many multisamples
        scd.SampleDesc.Quality = 0;

        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is to be used
        scd.BufferCount = 1;                                 // one back buffer
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        // scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        // create a device, device context and swap chain using the information in the
        // scd struct

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd;
        ZeroMemory(&scfd, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));

        scfd.RefreshRate.Numerator = 60;
        scfd.RefreshRate.Denominator = 1;
        scfd.Windowed = TRUE;                  // windowed/full-screen mode

        UINT createDeviceFlags = 0;
#if _DEBUG
        createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

        HRESULT hresult = m_Factory->CreateSwapChainForHwnd(
            m_Device, m_Hwnd, &scd, &scfd, nullptr, &m_SwapChain);

    }

    void RenderManager::CreateRenderTargetView()
    {
        // get the address of the back buffer
        ID3D11Texture2D* pBackBuffer;
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

        // use the back buffer address to create the render target
        m_Device->CreateRenderTargetView(pBackBuffer, nullptr, &m_BackBuffer);
        pBackBuffer->Release();
    }

    void RenderManager::CreateDepthStencilView()
    {
        D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
        ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

        depthStencilBufferDesc.Width = m_WindowSize.width;
        depthStencilBufferDesc.Height = m_WindowSize.height;
        depthStencilBufferDesc.MipLevels = 1;
        depthStencilBufferDesc.ArraySize = 1;
        depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilBufferDesc.SampleDesc.Count = 1;
        depthStencilBufferDesc.SampleDesc.Quality = 0;
        depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
        depthStencilBufferDesc.MiscFlags = 0;

        HRESULT result = m_Device->CreateTexture2D(&depthStencilBufferDesc, nullptr, &m_DepthStencilBuffer);
        if (result != S_OK)
        {

        }

        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;

        result = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &descDSV, &m_DepthStencilView);
        if (result != S_OK)
        {

        }
    }

    void RenderManager::CreateSamplerState()
    {
        D3D11_SAMPLER_DESC samplerDesc;
        ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.BorderColor[0] = 1.0f;
        samplerDesc.BorderColor[1] = 1.0f;
        samplerDesc.BorderColor[2] = 1.0f;
        samplerDesc.BorderColor[3] = 1.0f;
        samplerDesc.MinLOD = -FLT_MAX;
        samplerDesc.MaxLOD = FLT_MAX;
        HRESULT hr = m_Device->CreateSamplerState(&samplerDesc, &m_SamplerState);
    }

    void RenderManager::SetViewports()
    {
        // Set the viewport
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = m_WindowSize.width;
        viewport.Height = m_WindowSize.height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        m_DeviceContext->RSSetViewports(1, &viewport);
    }

    void RenderManager::ResizeSwapChain()
    {
        m_SwapChain->ResizeBuffers(0, m_WindowSize.width, m_WindowSize.height, DXGI_FORMAT_UNKNOWN, 0);
    }

    void RenderManager::ClearBackBuffer()
    {

    }

    void RenderManager::Render()
    {

    }

    void RenderManager::PresentSwapChain()
    {

    }

    void RenderManager::OnWindowResizeEvent(UINT width, UINT height)
    {
        ReleaseWindowSizeDependentResources();

        m_WindowSize.width = width;
        m_WindowSize.height = height;

        ResizeSwapChain();

        CreateRenderTargetView();
        CreateDepthStencilView();
        SetViewports();
    }

    void RenderManager::LoadShaders()
    {
        TCHAR buffer[260];

        GetCurrentDirectory(260, buffer);

        // File file("VertexShader.cso");

        // auto vertexShaderBytecode = ReadData("SimpleVertexShader.cso");
        ID3DBlob* psBlob;
        ID3DBlob* vsBlob;

        ID3DBlob* ppErrorMsgs;
        HRESULT vsresult = D3DCompileFromFile(
            L"../content/shaders/VertexShader.hlsl",
            nullptr, nullptr,
            "main", "vs_5_0",
            0, 0,
            &vsBlob, &ppErrorMsgs
        );

        ID3DBlob* psppErrorMsgs;
        HRESULT psresult = D3DCompileFromFile(
            L"../content/shaders/PixelShader.hlsl",
            nullptr, nullptr,
            "main", "ps_5_0",
            0, 0,
            &psBlob, &psppErrorMsgs
        );

        // char* error = (char*)psppErrorMsgs->GetBufferPointer();

        // encapsulate both shaders into shader objects
        m_Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_VertexShader);
        m_Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_PixelShader);

        // set the shader objects
        m_DeviceContext->VSSetShader(m_VertexShader, nullptr, 0);
        m_DeviceContext->PSSetShader(m_PixelShader, nullptr, 0);

        constexpr uint32_t ied_count = 4;
        D3D11_INPUT_ELEMENT_DESC ied[ied_count] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };
        
        m_Device->CreateInputLayout(ied, ied_count, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_InputLayout);
        m_DeviceContext->IASetInputLayout(m_InputLayout);
    }

    MeshObject* RenderManager::CreateMeshObject(const uca::MeshAsset& meshAsset)
    {
        auto* meshObject = ucNew(MeshObject);
        m_MeshObjects.push_back(meshObject);

        meshObject->CreateFromMeshAsset(this, meshAsset);
        return meshObject;
    }

    TextureObject* RenderManager::CreateTextureObject(const uca::TextureAsset& textureAsset)
    {
        auto* textureObject = ucNew(TextureObject);
        m_TextureObjects.push_back(textureObject);

        ID3D11Texture2D* dxTex; 
        ID3D11ShaderResourceView* dxSrv;
        CreateTexture2DBuffer(textureAsset, dxTex, dxSrv);

        textureObject->SetAsset(&textureAsset);
        textureObject->SetShaderResourceView(dxSrv);
        textureObject->SetTexture2D(dxTex);

        return textureObject;
    }

    MaterialObject* RenderManager::CreateMaterialObject(const uca::MaterialAsset& materialAsset)
    {
        auto* materialObject = ucNew(MaterialObject);
        m_MaterialObjects.push_back(materialObject);
        
        if (materialAsset.m_BaseColor != nullptr)
        {
            materialObject->SetBaseColor(CreateTextureObject(*materialAsset.m_BaseColor));
        }
        if (materialAsset.m_Roughness != nullptr)
        {
            materialObject->SetRoughness(CreateTextureObject(*materialAsset.m_Roughness));
        }

        return materialObject;
    }
    
    RenderObject* RenderManager::CreateRenderObject()
    {
        auto* renderObject = ucNew(RenderObject);
        m_RenderObjects.push_back(renderObject);

        return renderObject;
    }

    CameraObject* RenderManager::AddCamera()
    {
        auto* cameraObject = ucNew(CameraObject);
        m_CameraObjects.push_back(cameraObject);
        return cameraObject;
    }

    ID3D11Buffer* RenderManager::CreateConstantBuffer(uint32_t size)
    {
        ID3D11Buffer* result = nullptr;

        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));

        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.ByteWidth = size;

        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        m_Device->CreateBuffer(&bufferDesc, nullptr, &result);

        m_ConstantBuffer = result;

        return result;
    }

    ID3D11Buffer* RenderManager::CreateVertexBuffer(uint32_t size, const void* src)
    {
        return CreateSubresourceBuffer(D3D11_BIND_VERTEX_BUFFER, size, src);
    }

    ID3D11Buffer* RenderManager::CreateIndexBuffer(uint32_t size, const void* src)
    {
        return CreateSubresourceBuffer(D3D11_BIND_INDEX_BUFFER, size, src);
    }
    
    void RenderManager::CreateTexture2DBuffer(const uca::TextureAsset& texAsset, ID3D11Texture2D*& outTex, ID3D11ShaderResourceView*& outSrv)
    {
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = texAsset.width;
        desc.Height = texAsset.height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT; // TODO: look at D3D11_USAGE_IMMUTABLE
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        // const unsigned char* bee = texAsset.buffer;
        // 
        // while(*bee)
        // {
        //     printf("%d ", *(bee++));
        // }
        D3D11_SUBRESOURCE_DATA resourceData = {};
        resourceData.pSysMem = texAsset.buffer;
        resourceData.SysMemPitch = texAsset.width * texAsset.req_channels;
        ID3D11Texture2D* tex2d;

        m_Device->CreateTexture2D(&desc, &resourceData, &tex2d);

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Format = desc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        ID3D11ShaderResourceView* texSrv;
        m_Device->CreateShaderResourceView(tex2d, &srvDesc, &texSrv);
        outTex = tex2d;
        outSrv = texSrv;
    }

    ID3D11Buffer* RenderManager::CreateSubresourceBuffer(D3D11_BIND_FLAG bindFlag, uint32_t size, const void* src)
    {
        ID3D11Buffer* result = nullptr;

        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));

        bufferDesc.BindFlags = bindFlag;
        bufferDesc.ByteWidth = size;

        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA resourceData;
        ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
        resourceData.pSysMem = src;

        m_Device->CreateBuffer(&bufferDesc, &resourceData, &result); // create the buffer   
        return result;
    }

    void RenderManager::CopyMappedBuffer(ID3D11Buffer* buffer, const void* data, size_t size)
    {
        D3D11_MAPPED_SUBRESOURCE ms;
        m_DeviceContext->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // map the buffer
        memcpy(ms.pData, data, size);                                           // copy the data
        m_DeviceContext->Unmap(buffer, NULL);                                   // unmap the buffer
    }

    void RenderManager::UpdateConstantBuffer()
    {
        // ucc::Matrix4x4f mvp = m_MVP.model * m_MVP.view * m_MVP.projection;
        ConstantBufferData cBufferData;
        cBufferData.mvp = (m_MVP.model * m_MVP.view * m_MVP.projection).GetTranspose();
        cBufferData.model = m_MVP.model.GetTranspose();

        CopyMappedBuffer(m_ConstantBuffer, &cBufferData, sizeof(cBufferData));
    }
}
