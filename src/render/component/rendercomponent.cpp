#include "renderheader.h"

#include "rendercomponent.h"

namespace unirender
{
    void RenderObject::CreateFromGeometry(RenderManager* mgr, const uca::Geometry& geom)
    {
        const auto& vertices = geom.GetVertices();
        const auto& indices = geom.GetVertexIndices();
        const uint32_t indicesSize = static_cast<uint32_t>(indices.size());
        const uint32_t verticesSize = static_cast<uint32_t>(vertices.size());

        m_VertexBuffer = mgr->CreateVertexBuffer(verticesSize * sizeof(uca::Vertex), vertices.data());
        m_IndexBuffer = mgr->CreateIndexBuffer(indicesSize * sizeof(uint32_t), indices.data());

        m_IndicesCount = indicesSize;
    }

    void RenderObject::CreateFromMeshData(RenderManager* mgr, const uca::MeshData& mesh)
    {
        const auto& positions = mesh.GetVertices();
        const auto& indices = mesh.GetIndices();
        const uint32_t indicesCount = static_cast<uint32_t>(indices.size());
        const uint32_t verticesCount = static_cast<uint32_t>(positions.size());

        m_IndicesCount = indicesCount;
        m_VerticesCount = verticesCount;
        const uint32_t verticesSize = verticesCount * sizeof(uca::Vertex);

        m_VertexBuffer = mgr->CreateVertexBuffer(verticesSize, positions.data());
        m_IndexBuffer = mgr->CreateIndexBuffer(indicesCount * sizeof(uint32_t), indices.data());
    }

    void RenderObject::Shutdown(RenderManager* mgr)
    {
        m_VertexBuffer->Release();
        m_IndexBuffer->Release();
    }
}
