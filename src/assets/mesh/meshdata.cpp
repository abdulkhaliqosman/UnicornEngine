#include "meshdata.h"

namespace uniassets
{
    MeshData* MeshData::CreateCubeMesh()
    {
        MeshData* meshData = ucNew(MeshData);
        meshData->m_Vertices.reserve(8);

        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(0.5f, 0.5f, -0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(0.5f, -0.5f, -0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(-0.5f, -0.5f, -0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(-0.5f, 0.5f, -0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(0.5f, 0.5f, 0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(0.5f, -0.5f, 0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(-0.5f, -0.5f, 0.5f, 1.0f) });
        meshData->m_Vertices.push_back(Vertex{ ucc::Vector4f(-0.5f, 0.5f, 0.5f, 1.0f) });
        
        std::initializer_list<uint32_t> indices = {
                0, 1, 2,
                0, 2, 3,
                4, 5, 1,
                4, 1, 0,
                7, 6, 5,
                7, 5, 4,
                3, 2, 6,
                3, 6, 7,
                4, 0, 3,
                4, 3, 7,
                6, 2, 1,
                6, 1, 5
        };

        meshData->GetIndices().insert(meshData->GetIndices().begin(), indices);

        return meshData;
    }
}