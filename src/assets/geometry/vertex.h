#pragma once
#include "core/coreheader.h"

namespace uniassets
{
    struct Vertex
    {
        ucc::Vector4f position; // 0
        ucc::Vector4f color = { 0.6f, 0.5f, 0.4f, 1.0f }; // 16
        ucc::Vector4f normal = { 0.6f, 0.5f, 0.4f, 1.0f }; // 32
        ucc::Vector2f texcoord;
        ucc::Vector4uc joints;
        ucc::Vector4f weights;
    };
}
