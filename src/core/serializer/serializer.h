#pragma once

#include <stdint.h>
#include "core/math/vector4f.h"
#include "core/math/matrix4x4f.h"

namespace unicore
{
    class ISerializer
    {
    public:
        inline virtual ~ISerializer() {}

        virtual void Serialize(char&) = 0;
        virtual void Serialize(short&) = 0;
        virtual void Serialize(int&) = 0;
        virtual void Serialize(long&) = 0;
        virtual void Serialize(int64_t&) = 0;

        virtual void Serialize(unsigned char&) = 0;
        virtual void Serialize(unsigned short&) = 0;
        virtual void Serialize(unsigned int&) = 0;
        virtual void Serialize(unsigned long&) = 0;
        virtual void Serialize(uint64_t&) = 0;

        virtual void Serialize(float&) = 0;
        virtual void Serialize(double&) = 0;

        virtual void Serialize(Vector4f&) = 0;
        virtual void Serialize(Matrix4x4f&) = 0;
    };
}
