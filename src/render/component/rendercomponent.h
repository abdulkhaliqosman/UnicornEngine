#pragma once

#include "renderheader.h"

namespace unirender
{
    class RenderManager;
    class RenderComponent;

    class RenderObject
    {
    public:
        void Startup(RenderManager*);
        void Shutdown(RenderManager*);

        inline void SetGeometry(const uca::Geometry* value) { m_Geometry = value; }
        inline const uca::Geometry* GetGeometry() const { return m_Geometry; }

        inline ID3D11Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
        inline ID3D11Buffer* GetIndexBuffer() const { return m_IndexBuffer; }
        inline uint32_t GetIndicesSize() const { return m_IndicesSize; }

    private:
        const uca::Geometry* m_Geometry = nullptr;

        uint32_t m_IndicesSize = 0;

        ID3D11Buffer* m_VertexBuffer = nullptr;
        ID3D11Buffer* m_IndexBuffer = nullptr;
        uc::List<const RenderComponent*> m_Components;
    };

    class RenderComponent
    {
    public:

        inline void SetRenderObject(const RenderObject* value) { m_RenderObject = value; }
        inline const RenderObject* GetRenderObject() const { return m_RenderObject; }

        inline const uca::Geometry* GetGeometry() { return m_RenderObject->GetGeometry(); }
    private:
        const RenderObject* m_RenderObject;
    };
}
