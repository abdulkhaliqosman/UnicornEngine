#include "meshasset.h"

namespace uniassets
{
    MeshAsset* MeshAsset::CreateCubeMesh()
    {
        MeshAsset* meshAsset = ucNew(MeshAsset);
        meshAsset->m_Vertices.reserve(8);

        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(-1.0f, -1.0f, -1.0f, 1.0f), ucc::Vector4f(0.0f, 0.0f, 0.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(-1.0f,  1.0f, -1.0f, 1.0f), ucc::Vector4f(0.0f, 1.0f, 0.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(1.0f,  1.0f, -1.0f, 1.0f) , ucc::Vector4f(1.0f, 1.0f, 0.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(1.0f, -1.0f, -1.0f, 1.0f) , ucc::Vector4f(1.0f, 0.0f, 0.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(-1.0f, -1.0f,  1.0f, 1.0f), ucc::Vector4f(0.0f, 0.0f, 1.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(-1.0f,  1.0f,  1.0f, 1.0f), ucc::Vector4f(0.0f, 1.0f, 1.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(1.0f,  1.0f,  1.0f, 1.0f) , ucc::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) });
        meshAsset->m_Vertices.push_back(Vertex{ ucc::Vector4f(1.0f, -1.0f,  1.0f, 1.0f) , ucc::Vector4f(1.0f, 0.0f, 1.0f, 1.0f) });
        
        std::initializer_list<uint32_t> indices = {
                0, 1, 2, 0, 2, 3,
                4, 6, 5, 4, 7, 6,
                4, 5, 1, 4, 1, 0,
                3, 2, 6, 3, 6, 7,
                1, 5, 6, 1, 6, 2,
                4, 0, 3, 4, 3, 7
        };

        meshAsset->GetIndices().insert(meshAsset->GetIndices().begin(), indices);

        return meshAsset;
    }
}