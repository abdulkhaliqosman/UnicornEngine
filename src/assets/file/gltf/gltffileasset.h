#pragma once
#include "core/coreheader.h"

namespace uniassets
{
    struct AssetFileData;
    class GLTFFileAsset
    {
    public:
        static AssetFileData* ImportFromFile(const TCHAR* path);
    };
}