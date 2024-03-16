#pragma once

#include "assets/assetsheader.h"
#include "render/renderheader.h"

namespace unirender
{
	class TextureObject
	{
	public:
		inline const uca::TextureAsset* GetAsset() const { return m_Asset; }
		inline const ID3D11Texture2D* GetTexture2D() const { return m_Texture2D; }
		inline const ID3D11ShaderResourceView* GetSRV() const { return m_ShaderResourceView; }
		inline ID3D11ShaderResourceView*const* GetSRVAddress() const { return &m_ShaderResourceView; }
		
		inline void SetAsset(const uca::TextureAsset* asset) { m_Asset = asset; }
		inline void SetTexture2D(ID3D11Texture2D* tex2d) { m_Texture2D = tex2d; }
		inline void SetShaderResourceView(ID3D11ShaderResourceView* srv) { m_ShaderResourceView = srv; }
	
	private:
		const uca::TextureAsset* m_Asset = nullptr;
		ID3D11Texture2D* m_Texture2D = nullptr;
		ID3D11ShaderResourceView* m_ShaderResourceView = nullptr;
	};
}