#pragma once

namespace uniassets
{
    struct MeshData;

    struct AssetFileData
    {
        inline ucc::List<MeshData*>& GetMeshes() { return m_Meshes; }
    private:
        ucc::List<MeshData*> m_Meshes;
    };
}