#pragma once

#include "core/coreheader.h"

namespace uniassets
{
    struct Vertex
    {
        uc::Vector4f position;
        uc::Vector4f color;
    };

    class Geometry
    {
    public:
        inline virtual ~Geometry() {}
        virtual const uc::List<Vertex>& GetVertices() const = 0;
        virtual const uc::List<uint32_t>& GetVertexIndices() const = 0;
    };
}
