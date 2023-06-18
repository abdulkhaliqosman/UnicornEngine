#pragma once

#include "assets/geometry/geometry.h"
#include "core/container/list.h"

namespace uniassets
{
    class Cube : public Geometry
    {
    public:
        const ucc::List<Vertex>& GetVertices() const override;
        const ucc::List<uint32_t>& GetVertexIndices() const override;
    private:

    };
}
