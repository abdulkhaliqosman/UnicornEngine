#pragma once

#include "engine/core/coreheader.h"

namespace uniassets
{
    struct AssetFileData;

    struct NodeRecordFormat;

    class FBXFileAsset
    {
    public:
        static AssetFileData* ImportFromFile(const TCHAR* path);
    };

    
}
