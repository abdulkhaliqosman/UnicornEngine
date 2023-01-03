#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>


namespace uni
{
	class Dx11Graphics
	{
	public:
		void Init();
		void Shutdown();
		void Update();

		void LoadShaders();
		void CreateVertexBuffer();
		void MapToBuffer();

		void SetHwnd(HWND hWnd) { m_Hwnd = hWnd; }
	private:
		HWND m_Hwnd;

		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
		ID3D11RenderTargetView* m_BackBuffer;

		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;

		ID3D11Buffer* m_VertexBuffer;

		ID3D11InputLayout* m_InputLayout;
	};
}
