#pragma once

namespace uniassets
{
    class MeshAsset;
    class MaterialAsset;

    struct AssetFileData
    {
        inline ucc::List<MeshAsset*>& GetMeshes() { return m_Meshes; }
        inline ucc::List<MaterialAsset*>& GetMaterials() { return m_Materials; }

    private:
        ucc::List<MeshAsset*> m_Meshes;
        ucc::List<MaterialAsset*> m_Materials;
    };
}