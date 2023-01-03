#include "unicornpch.h"
#include "dx11graphics.h"

#include <d3dcompiler.h>

#include "vertex.h"

#include "core/filesystem/file.h"


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace uni
{
    Vertex triangle[] =
    {
        {  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        { 0.45f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
        {-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
    };
    constexpr size_t triangle_size = sizeof(triangle);

    void Dx11Graphics::Init()
    {
        assert(m_Hwnd != nullptr);
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
            NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
            &scd, &m_SwapChain, &m_Device, NULL, &m_DeviceContext);

        // get the address of the back buffer
        ID3D11Texture2D* pBackBuffer;
        m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        // use the back buffer address to create the render target
        m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
        pBackBuffer->Release();

        // set the render target as the back buffer
        m_DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, NULL);

		// Set the viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = SCREEN_WIDTH;
		viewport.Height = SCREEN_HEIGHT;

        m_DeviceContext->RSSetViewports(1, &viewport);

        LoadShaders();

        CreateVertexBuffer();
        MapToBuffer();
    }

    void Dx11Graphics::Shutdown()
    {
        m_SwapChain->SetFullscreenState(FALSE, NULL);

        m_VertexShader->Release();
        m_PixelShader->Release();

        m_SwapChain->Release();
        m_BackBuffer->Release();

        m_Device->Release();
        m_DeviceContext->Release();
    }

	// this is the function used to render a single frame
	void Dx11Graphics::Update()
	{
        static constexpr float blue[] { 0.0f, 0.2f, 0.4f, 1.0f };
		// clear the back buffer to a deep blue
        m_DeviceContext->ClearRenderTargetView(m_BackBuffer, blue);

		// do 3D rendering on the back buffer here

		// select which vertex buffer to display
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
        m_DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// select which primitive type we are using
        m_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
        m_DeviceContext->Draw(3, 0);

		// switch the back buffer and the front buffer
        m_SwapChain->Present(0, 0);
	}

    void Dx11Graphics::LoadShaders()
    {
        File file("VertexShader.cso");

        // auto vertexShaderBytecode = ReadData("SimpleVertexShader.cso");
        ID3DBlob* psBlob;
		ID3DBlob* vsBlob;

        D3DCompileFromFile(
            L"shaders/PixelShader.hlsl",
            nullptr, nullptr,
            "main", "ps_5_0",
			0, 0,
			&psBlob, nullptr
        );

		D3DCompileFromFile(
			L"shaders/VertexShader.hlsl",
			nullptr, nullptr,
			"main", "vs_5_0",
			0, 0,
			&vsBlob, nullptr
		);

		// encapsulate both shaders into shader objects
        m_Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &m_VertexShader);
        m_Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &m_PixelShader);

		// set the shader objects
        m_DeviceContext->VSSetShader(m_VertexShader, 0, 0);
        m_DeviceContext->PSSetShader(m_PixelShader, 0, 0);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		m_Device->CreateInputLayout(ied, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_InputLayout);
        m_DeviceContext->IASetInputLayout(m_InputLayout);
    }

    void Dx11Graphics::CreateVertexBuffer()
    {
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
        
		bd.Usage          = D3D11_USAGE_DYNAMIC;      // write access access by CPU and GPU
		bd.ByteWidth      = triangle_size;            // size is the VERTEX struct * 3
		bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER; // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // allow CPU to write in buffer

        m_Device->CreateBuffer(&bd, NULL, &m_VertexBuffer); // create the buffer                             
    }

    void Dx11Graphics::MapToBuffer()
    {
		D3D11_MAPPED_SUBRESOURCE ms;
		m_DeviceContext->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // map the buffer
		memcpy(ms.pData, triangle, triangle_size);                                      // copy the data
		m_DeviceContext->Unmap(m_VertexBuffer, NULL);                                   // unmap the buffer
    }

}  // namespace uni