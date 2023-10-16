#pragma once

#include "core/coreheader.h"
#include "assets/geometry/vertex.h"

namespace uniassets
{
    class Geometry
    {
    public:
        inline virtual ~Geometry() {}
        virtual const ucc::List<Vertex>& GetVertices() const = 0;
        virtual const ucc::List<uint32_t>& GetVertexIndices() const = 0;
    };
}
