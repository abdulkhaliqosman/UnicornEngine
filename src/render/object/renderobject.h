#pragma once

#include "render/renderheader.h"

namespace unirender
{
    class RenderManager;
    class RenderObject;

    class RenderInstance
    {
    public:
        inline RenderObject* GetRenderObject() { return m_RenderObject; }
        inline const ucc::Matrix4x4f& GetModelTransform() const { return m_ModelTransform; }
        inline void SetModelTransform(const ucc::Matrix4x4f& transform) { m_ModelTransform = transform; }

    private:
        RenderObject* m_RenderObject;
        ucc::Matrix4x4f m_ModelTransform;
    };

    class RenderObject
    {
    public:
        void Shutdown(RenderManager*);

        void CreateFromGeometry(RenderManager* mgr, const uca::Geometry& geom);
        void CreateFromMeshData(RenderManager* mgr, const uca::MeshData& meshData);

        RenderInstance* CreateInstance();
        void DestroyInstance(RenderInstance*);

        inline ID3D11Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
        inline ID3D11Buffer* GetIndexBuffer() const { return m_IndexBuffer; }
        inline uint32_t GetIndicesCount() const { return m_IndicesCount; }
        inline uint32_t GetVerticesCount() const { return m_VerticesCount; }
        inline const ucc::List<RenderInstance*>& GetInstances() const { return m_Instances; }
    private:

        uint32_t m_IndicesCount = 0;
        uint32_t m_VerticesCount = 0;

        ID3D11Buffer* m_VertexBuffer = nullptr;
        ID3D11Buffer* m_IndexBuffer = nullptr;
        ucc::List<RenderInstance*> m_Instances;
    };

}
