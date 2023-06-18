#include "core/coreheader.h"

namespace unieditor
{
    class EditorSerializer : public ucc::ISerializer
    {
    public:
        void Serialize(char&) override;
        void Serialize(short&) override;
        void Serialize(int&) override;
        void Serialize(long&) override;
        void Serialize(long long&) override;

        void Serialize(unsigned char&) override;
        void Serialize(unsigned short&) override;
        void Serialize(unsigned int&) override;
        void Serialize(unsigned long&) override;
        void Serialize(unsigned long long&) override;

        void Serialize(float&) override;
        void Serialize(double&) override;

        void Serialize(ucc::Vector4f&) override;
        void Serialize(ucc::Matrix4f&) override;
    private:

    };
}