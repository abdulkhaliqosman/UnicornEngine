#pragma once

#include <stdint.h>

namespace uniassets
{
    class TextureAsset
    {
    public:
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t channels = 0;
        uint32_t req_channels = 0;
        uint8_t* buffer = nullptr;
    private:
    };
}
