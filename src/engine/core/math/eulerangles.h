#pragma once

#include "core/math/math.h"
#include "core/math/vector4f.h"

namespace Unicorn
{
    class EulerAngles : private Vector4f
    {
    public:
        inline EulerAngles() : Vector4f() {}
		inline float GetI() const { return GetX(); }
		inline float GetJ() const { return GetY(); }
		inline float GetK() const { return GetZ(); }

        static inline EulerAngles FromDeg(float x, float y, float z) { return EulerAngles(Math::DegToRad(x), Math::DegToRad(y), Math::DegToRad(z)); }
        static inline EulerAngles FromRad(float x, float y, float z) { return EulerAngles(x, y, z); }
    private:
        inline EulerAngles(float x, float y, float z) : Vector4f(x, y, z) {}
    };
}