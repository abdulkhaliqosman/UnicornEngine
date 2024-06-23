#pragma once

#include "render/renderheader.h"

namespace unirender
{
    class RenderObject;

    class RenderInstance
    {
    public:
        inline RenderObject* GetRenderObject() { return m_RenderObject; }
        inline const ucc::Matrix4x4f& GetModelTransform() const { return m_ModelTransform; }
        inline void SetModelTransform(const ucc::Matrix4x4f& transform) { m_ModelTransform = transform; }

    private:
        RenderObject* m_RenderObject = nullptr;
        ucc::Matrix4x4f m_ModelTransform;
    };

    class RenderObject
    {
    public:
        void Shutdown();

        RenderInstance* CreateInstance();
        void DestroyInstance(RenderInstance*);

        inline const ucc::List<RenderInstance*>& GetInstances() const { return m_Instances; }

        inline const MeshObject* GetMesh() const { return m_Mesh; }
        inline const MaterialObject* GetMaterial() const { return m_Material; }

        inline void SetMesh(MeshObject* mesh) { m_Mesh = mesh; }
        inline void SetMaterial(MaterialObject* material) { m_Material = material; }
    private:

        ucc::List<RenderInstance*> m_Instances;
        MeshObject* m_Mesh = nullptr;
        MaterialObject* m_Material = nullptr;

    };

}
