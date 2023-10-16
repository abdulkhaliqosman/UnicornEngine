#include "renderheader.h"

#include "rendermanager.h"

#include <iostream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace unirender
{
    void RenderManager::Init()
    {
        std::cout << "RenderManager::Startup()" << std::endl;
        assert(m_Hwnd != nullptr);

        CreateSwapChain();
        CreateRenderTarget();

        // Set the viewport
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = SCREEN_WIDTH;
        viewport.Height = SCREEN_HEIGHT;

        m_DeviceContext->RSSetViewports(1, &viewport);

        m_ConstantBuffer = CreateConstantBuffer(sizeof(ucc::Matrix4x4f));
        UpdateMVPCBuffer(); // set to identity

        // uca::Cube cube; //TODO: store the cube in an asset manager
        // auto* renderObject = ucNew(RenderObject);
        // m_RenderObjects.push_back(renderObject);
        // renderObject->CreateFromMeshData(this, *uca::MeshData::CreateCubeMesh());
    }

    void RenderManager::Startup()
    {
        
        LoadShaders();
    }

    void RenderManager::Update()
    {
        UpdateMVPCBuffer();

        static constexpr float blue[]{ 0.0f, 0.2f, 0.4f, 1.0f };
        // clear the back buffer to a deep blue
        m_DeviceContext->ClearRenderTargetView(m_BackBuffer, blue);

        // do 3D rendering on the back buffer here

        // for now we set constant buffer yes
        m_DeviceContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

        const UINT stride = sizeof(uca::Vertex);

        for (const auto* object : m_RenderObjects)
        {
            UINT offset = 0;
            ID3D11Buffer* vertexBuffer = object->GetVertexBuffer();

            // select which vertex buffer to display
            m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
            m_DeviceContext->IASetIndexBuffer(object->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

            // select which primitive type we are using
            m_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            // draw the vertex buffer to the back buffer
            m_DeviceContext->DrawIndexed(object->GetIndicesCount(), 0, 0);
        }
        

        // switch the back buffer and the front buffer
        m_SwapChain->Present(0, 0);
    }

    void RenderManager::Shutdown()
    {
        std::cout << "RenderManager::Shutdown()" << std::endl;

        for (auto* object : m_RenderObjects)
        {
            object->Shutdown(this);
            delete object;
        }
        m_RenderObjects.clear();

        m_SwapChain->SetFullscreenState(FALSE, nullptr);

        m_VertexShader->Release();
        m_PixelShader->Release();

        m_SwapChain->Release();
        m_BackBuffer->Release();

        m_Device->Release();
        m_DeviceContext->Release();
    }

    void RenderManager::CreateSwapChain()
    {
        // create a struct to hold information about the swap chain
        DXGI_SWAP_CHAIN_DESC scd;

        // clear out the struct for use
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

        // fill the swap chain description struct
        scd.BufferCount = 1;                                 // one back buffer
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // use 32-bit color
        scd.BufferDesc.Width = SCREEN_WIDTH;  // use 32-bit color
        scd.BufferDesc.Height = SCREEN_HEIGHT;  // use 32-bit color
        scd.BufferUsage =
            DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is to be used
        scd.OutputWindow = m_Hwnd;            // the window to be used
        scd.SampleDesc.Count = 4;             // how many multisamples
        scd.Windowed = TRUE;                  // windowed/full-screen mode
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        // create a device, device context and swap chain using the information in the
        // scd struct
        D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd,
            &m_SwapChain, &m_Device, nullptr, &m_DeviceContext);
    }

    void RenderManager::CreateRenderTarget()
    {
        // get the address of the back buffer
        ID3D11Texture2D* pBackBuffer;
        m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));

        // use the back buffer address to create the render target
        m_Device->CreateRenderTargetView(pBackBuffer, nullptr, &m_BackBuffer);
        pBackBuffer->Release();

        // set the render target as the back buffer
        m_DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, nullptr);

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

        constexpr uint32_t ied_count = 3;
        D3D11_INPUT_ELEMENT_DESC ied[ied_count] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        
        m_Device->CreateInputLayout(ied, ied_count, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_InputLayout);
        m_DeviceContext->IASetInputLayout(m_InputLayout);
    }

    void RenderManager::AddMesh(const uca::MeshData& meshData)
    {
        auto* renderObject = ucNew(RenderObject);
        m_RenderObjects.push_back(renderObject);

        renderObject->CreateFromMeshData(this, meshData);
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

    void RenderManager::UpdateMVPCBuffer()
    {
        static float rot = 0.0f;
        rot += 0.01f;
        // m_MVP.model[0].SetW(0.5f);
        m_MVP.model = 
            ucc::Transform::Scale(ucc::Vector4f(0.5f, 0.5f, 0.1f, 1.0f))
            * ucc::Transform::Rotation(0.0f, rot, 0.0f)
            * ucc::Transform::Translation(ucc::Vector4f(0.0f, 0.0f, 0.5f, 1.0f));
        m_MVP.view = 
        ucc::Matrix4x4f mvp = m_MVP.model * m_MVP.view * m_MVP.projection;
        CopyMappedBuffer(m_ConstantBuffer, mvp.GetData(), sizeof(mvp));
    }
}
