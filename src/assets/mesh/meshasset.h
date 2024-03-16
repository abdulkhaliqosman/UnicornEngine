#pragma once
#include "core/coreheader.h"
#include "assets/geometry/vertex.h"

namespace uniassets
{
    class MeshAsset
    {
    public:
        inline const ucc::List<Vertex>& GetVertices() const { return m_Vertices; }
        inline ucc::List<Vertex>& GetVertices() { return m_Vertices; }

        inline const ucc::List<uint32_t>& GetIndices() const { return m_Indices; }
        inline ucc::List<uint32_t>& GetIndices() { return m_Indices; }
        
        static MeshAsset* CreateCubeMesh();

    private:
        ucc::List<Vertex> m_Vertices;
        ucc::List<uint32_t> m_Indices;

    };
}
