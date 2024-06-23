#pragma once

namespace uniassets
{
    class TextureAsset;

    class MaterialAsset
    {
    public:
        TextureAsset* m_BaseColor = nullptr;
        TextureAsset* m_Roughness = nullptr;
    };
}
