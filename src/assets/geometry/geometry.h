#pragma once

#include "core/coreheader.h"

namespace uniassets
{
    struct Vertex
    {
        ucc::Vector4f position;
        ucc::Vector4f color;
    };

    class Geometry
    {
    public:
        inline virtual ~Geometry() {}
        virtual const ucc::List<Vertex>& GetVertices() const = 0;
        virtual const ucc::List<uint32_t>& GetVertexIndices() const = 0;
    };
}
