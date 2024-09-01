#pragma once

#include <stdint.h>
#include "core/math/vector4f.h"
#include "core/math/quaternion4f.h"
#include "core/math/matrix4x4f.h"
#include "core/container/string.h"

namespace Unicorn
{
    class Object;

    class ISerializer
    {
    public:
        inline virtual ~ISerializer() {}

        template<typename T, typename... Args, template<typename...> typename CONT>
        void SerializeArray(const char* name, CONT<T*, Args...>& arr)
        {
            size_t size = arr.size();
            if (SerializeArrayBegin(name, size))
            {
                if (size != arr.size())
                {
                    // resize if we are reading from file/writing to object
                }

                for (auto& object : arr)
                {
                    SerializeObject(object);
                }
                SerializeArrayEnd(name);
            }
        }

        virtual void Serialize(const char* name) = 0;

        virtual void Serialize(const char* name, int8_t&) = 0;
        virtual void Serialize(const char* name, int16_t&) = 0;
        virtual void Serialize(const char* name, int32_t&) = 0;
        virtual void Serialize(const char* name, int64_t&) = 0;

        virtual void Serialize(const char* name, uint8_t&) = 0;
        virtual void Serialize(const char* name, uint16_t&) = 0;
        virtual void Serialize(const char* name, uint32_t&) = 0;
        virtual void Serialize(const char* name, uint64_t&) = 0;

        virtual void Serialize(const char* name, float&) = 0;
        virtual void Serialize(const char* name, double&) = 0;

        virtual void Serialize(const char* name, Vector4f&) = 0;
        virtual void Serialize(const char* name, Quaternion4f&) = 0;
        virtual void Serialize(const char* name, Matrix4x4f&) = 0;

        virtual void Serialize(const char* name, String&) = 0;

        virtual void SerializeObject(Object*) = 0;

        virtual bool SerializeArrayBegin(const char* name, uint64_t& size) = 0;
        virtual void SerializeArrayEnd(const char* name) = 0;
    };
}
