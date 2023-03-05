#pragma once

namespace unicore
{
    static constexpr float PI = 3.141592653589793238f;

    class Math
    {
    public:
        static inline float DegToRad(float deg) { return deg / 180.0f * PI; }
        static inline float RadToDeg(float rad) { return rad / PI * 180.0f; }
    };
}

#include "core/math/vector4f.h"
#include "core/math/quaternion4f.h"
#include "core/math/matrix4f.h"
#include "core/math/transform.h"
#include "core/math/color.h"
