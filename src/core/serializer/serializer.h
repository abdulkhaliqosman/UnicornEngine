#pragma once

#include "math/vector4f.h"
#include "math/matrix4f.h"

namespace unicore
{
    class ISerializer
    {
    public:
        virtual void Serialize(char&) = 0;
        virtual void Serialize(short&) = 0;
        virtual void Serialize(int&) = 0;
        virtual void Serialize(long&) = 0;
        virtual void Serialize(long long&) = 0;

        virtual void Serialize(unsigned char&) = 0;
        virtual void Serialize(unsigned short&) = 0;
        virtual void Serialize(unsigned int&) = 0;
        virtual void Serialize(unsigned long&) = 0;
        virtual void Serialize(unsigned long long&) = 0;

        virtual void Serialize(float&) = 0;
        virtual void Serialize(double&) = 0;

        virtual void Serialize(Vector4f&) = 0;
        virtual void Serialize(Matrix4f&) = 0;
    };
}