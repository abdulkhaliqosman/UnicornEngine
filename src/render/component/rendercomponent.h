#pragma once

#include "renderheader.h"

namespace unirender
{
    class RenderManager;
    class RenderComponent;

    class RenderObject
    {
    public:
        void CreateFromGeometry(RenderManager* mgr, const uca::Geometry& geom);
        void CreateFromMeshData(RenderManager* mgr, const uca::MeshData& meshData);
        void Shutdown(RenderManager*);

        inline ID3D11Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
        inline ID3D11Buffer* GetIndexBuffer() const { return m_IndexBuffer; }
        inline uint32_t GetIndicesCount() const { return m_IndicesCount; }
        inline uint32_t GetVerticesCount() const { return m_VerticesCount; }

    private:

        uint32_t m_IndicesCount = 0;
        uint32_t m_VerticesCount = 0;

        ID3D11Buffer* m_VertexBuffer = nullptr;
        ID3D11Buffer* m_IndexBuffer = nullptr;
        ucc::List<const RenderComponent*> m_Components;
    };

    class RenderComponent
    {
    public:

        inline void SetRenderObject(const RenderObject* value) { m_RenderObject = value; }
        inline const RenderObject* GetRenderObject() const { return m_RenderObject; }
    private:
        const RenderObject* m_RenderObject;
    };
}
