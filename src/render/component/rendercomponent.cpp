#include "renderheader.h"

#include "rendercomponent.h"

namespace unirender
{
    void RenderObject::Startup(RenderManager* mgr)
    {
        assert(m_Geometry != nullptr);

        const auto& vertices = m_Geometry->GetVertices();
        const auto& indices = m_Geometry->GetVertexIndices();
        const uint32_t indicesSize = static_cast<uint32_t>(indices.size());
        const uint32_t verticesSize = static_cast<uint32_t>(vertices.size());

        m_VertexBuffer = mgr->CreateVertexBuffer(verticesSize * sizeof(uca::Vertex), vertices.data());
        m_IndexBuffer = mgr->CreateIndexBuffer(indicesSize * sizeof(uint32_t), indices.data());

        m_IndicesSize = indicesSize;
    }

    void RenderObject::Shutdown(RenderManager* mgr)
    {
        m_VertexBuffer->Release();
        m_IndexBuffer->Release();
    }
}
