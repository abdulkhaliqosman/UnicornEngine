#include "cube.h"

namespace uniassets
{
    static const ucc::List<uint32_t> s_Indices =
    {
        0, 1, 2,
        0, 2, 3,
        4, 5, 1,
        4, 1, 0,
        7, 6, 5,
        7, 5, 4,
        3, 2, 6,
        3, 6, 7,
        4, 0, 3,
        4, 3, 7,
        6, 2, 1,
        6, 1, 5
    };

    static const ucc::List<Vertex> s_Vertices =
    {
        Vertex{ucc::Vector4f(0.5f, 0.5f,  -0.5f, 1.0f), ucc::Vector4f(1.0f, 1.0f, 0.0f, 1.0f)},
        Vertex{ucc::Vector4f(0.5f, -0.5f,  -0.5f, 1.0f), ucc::Vector4f(1.0f, 0.0f, 0.0f, 1.0f)},
        Vertex{ucc::Vector4f(-0.5f, -0.5f,  -0.5f, 1.0f), ucc::Vector4f(0.0f, 0.0f, 0.0f, 1.0f)},
        Vertex{ucc::Vector4f(-0.5f, 0.5f,  -0.5f, 1.0f), ucc::Vector4f(0.0f, 1.0f, 0.0f, 1.0f)},
        Vertex{ucc::Vector4f(0.5f, 0.5f,  0.5f, 1.0f), ucc::Vector4f(1.0f, 1.0f, 1.0f, 1.0f)},
        Vertex{ucc::Vector4f(0.5f, -0.5f,  0.5f, 1.0f), ucc::Vector4f(1.0f, 0.0f, 1.0f, 1.0f)},
        Vertex{ucc::Vector4f(-0.5f, -0.5f,  0.5f, 1.0f), ucc::Vector4f(0.0f, 0.0f, 1.0f, 1.0f)},
        Vertex{ucc::Vector4f(-0.5f, 0.5f,  0.5f, 1.0f), ucc::Vector4f(0.0f, 1.0f, 1.0f, 1.0f)}
    };

    const ucc::List<Vertex>& Cube::GetVertices() const
    {
        //     7-------4
        //    /|      /|
        //   / |     / |
        //  /  |    /  |
        // 3-------0   |
        // |   6---|---5
        // |  /    |  /
        // | /     | /
        // |/      |/
        // 2-------1

        return s_Vertices;
    }

    const ucc::List<uint32_t>& Cube::GetVertexIndices() const
    {
        return s_Indices;
    }
}
