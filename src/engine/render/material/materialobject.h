#pragma once

#include "assets/assetsheader.h"

namespace unirender
{
    class TextureObject;

    class MaterialObject
    {
    public:
        inline const uca::MaterialAsset* GetAsset() const { return m_Asset; }
        inline const TextureObject* GetBaseColor() const { return m_BaseColor; }
        inline const TextureObject* GetRoughness() const { return m_Roughness; }

        inline void SetAsset(uca::MaterialAsset* asset) { m_Asset = asset; }
        inline void SetBaseColor(TextureObject* color) { m_BaseColor = color; }
        inline void SetRoughness(TextureObject* roughness) { m_Roughness = roughness; }

    private:
        uca::MaterialAsset* m_Asset = nullptr;
        TextureObject* m_BaseColor = nullptr;
        TextureObject* m_Roughness = nullptr;
    };
}
