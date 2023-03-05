#pragma once

#include "assets/geometry/geometry.h"
#include "core/container/list.h"

namespace uniassets
{
    class Cube : public Geometry
    {
    public:
        const uc::List<Vertex>& GetVertices() const override;
        const uc::List<uint32_t>& GetVertexIndices() const override;
    private:

    };
}
