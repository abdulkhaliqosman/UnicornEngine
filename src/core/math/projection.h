#pragma once

namespace unicore
{
    class Projection
    {
    public:
        static inline Matrix4x4f PerspectiveMatrix(float nearPlane, float farPlane, float top, float right)
        {
            Matrix4x4f result;

            result[0][0] = nearPlane / right;
            result[1][1] = nearPlane / top;
            result[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            result[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
            result[2][3] = -1;

            return result;
        }


    };
}