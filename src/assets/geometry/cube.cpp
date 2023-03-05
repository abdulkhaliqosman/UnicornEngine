#include "cube.h"

namespace uniassets
{
    static const uc::List<uint32_t> s_Indices =
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

    static const uc::List<Vertex> s_Vertices =
    {
        Vertex{uc::Vector4f(0.5f, 0.5f,  -0.5f, 1.0f), uc::Vector4f(1.0f, 1.0f, 0.0f, 1.0f)},
        Vertex{uc::Vector4f(0.5f, -0.5f,  -0.5f, 1.0f), uc::Vector4f(1.0f, 0.0f, 0.0f, 1.0f)},
        Vertex{uc::Vector4f(-0.5f, -0.5f,  -0.5f, 1.0f), uc::Vector4f(0.0f, 0.0f, 0.0f, 1.0f)},
        Vertex{uc::Vector4f(-0.5f, 0.5f,  -0.5f, 1.0f), uc::Vector4f(0.0f, 1.0f, 0.0f, 1.0f)},
        Vertex{uc::Vector4f(0.5f, 0.5f,  0.5f, 1.0f), uc::Vector4f(1.0f, 1.0f, 1.0f, 1.0f)},
        Vertex{uc::Vector4f(0.5f, -0.5f,  0.5f, 1.0f), uc::Vector4f(1.0f, 0.0f, 1.0f, 1.0f)},
        Vertex{uc::Vector4f(-0.5f, -0.5f,  0.5f, 1.0f), uc::Vector4f(0.0f, 0.0f, 1.0f, 1.0f)},
        Vertex{uc::Vector4f(-0.5f, 0.5f,  0.5f, 1.0f), uc::Vector4f(0.0f, 1.0f, 1.0f, 1.0f)}
    };

    const uc::List<Vertex>& Cube::GetVertices() const
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

    const uc::List<uint32_t>& Cube::GetVertexIndices() const
    {
        return s_Indices;
    }
}
