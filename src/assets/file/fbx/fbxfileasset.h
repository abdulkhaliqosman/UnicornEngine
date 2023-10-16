#pragma once

#include "core/coreheader.h"

namespace uniassets
{
    struct AssetFileData;

    class NodeRecordFormat;

    class FBXFileAsset
    {
    public:
        static AssetFileData* ImportFromFile(const TCHAR* path);
    };

    
}
