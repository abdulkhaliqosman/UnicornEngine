#pragma once
#include "core/coreheader.h"

namespace unidebug
{
    class ImguiSerializer : public ucc::ISerializer
    {
    public:
        inline ~ImguiSerializer() override {}

        void Serialize(const char* name) override;

        void Serialize(const char* name, int8_t&) override;
        void Serialize(const char* name, int16_t&) override;
        void Serialize(const char* name, int32_t&) override;
        void Serialize(const char* name, int64_t&) override;

        void Serialize(const char* name, uint8_t&) override;
        void Serialize(const char* name, uint16_t&) override;
        void Serialize(const char* name, uint32_t&) override;
        void Serialize(const char* name, uint64_t&) override;

        void Serialize(const char* name, float&) override;
        void Serialize(const char* name, double&) override;

        void Serialize(const char* name, ucc::Vector4f&) override;
        void Serialize(const char* name, ucc::Quaternion4f&) override;
        void Serialize(const char* name, ucc::Matrix4x4f&) override;

        void Serialize(const char* name, ucc::String&) override;

        void SerializeObject(ucc::Object*) override;

        bool SerializeArrayBegin(const char* name, uint64_t& size) override;
        void SerializeArrayEnd(const char* name) override;

    };

    
}
