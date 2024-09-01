#pragma once

namespace Unicorn
{
    static constexpr float PI = 3.141592653589793238f;

    class Math
    {
    public:
        static inline float DegToRad(float deg) { return deg / 180.0f * PI; }
        static inline float RadToDeg(float rad) { return rad / PI * 180.0f; }
    };

    struct Vector2f
    {
        float x;
        float y;
    };

    struct Vector4u8
    {
        uint8_t data[4];
    };

    struct Vector2i16
    {
        int16_t data[2];
    };
}

#include "core/math/vector4f.h"
#include "core/math/quaternion4f.h"
#include "core/math/matrix4x4f.h"
#include "core/math/transform.h"
#include "core/math/color.h"
