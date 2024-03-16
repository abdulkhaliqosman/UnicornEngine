#pragma once

#include "render/renderheader.h"

namespace unirender
{
    class RenderManager;
    class MeshObject
    {
    public:
        void Shutdown();

        void CreateFromGeometry(RenderManager* mgr, const uca::Geometry& geom);
        void CreateFromMeshAsset(RenderManager* mgr, const uca::MeshAsset& meshAsset);

        inline ID3D11Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
        inline ID3D11Buffer* GetIndexBuffer() const { return m_IndexBuffer; }
        inline uint32_t GetIndicesCount() const { return m_IndicesCount; }
        inline uint32_t GetVerticesCount() const { return m_VerticesCount; }
    private:

        uint32_t m_IndicesCount = 0;
        uint32_t m_VerticesCount = 0;

        ID3D11Buffer* m_VertexBuffer = nullptr;
        ID3D11Buffer* m_IndexBuffer = nullptr;
    };
}