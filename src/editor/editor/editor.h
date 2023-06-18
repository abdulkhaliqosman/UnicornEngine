#pragma once

#include "engine/engineheader.h"
#include "editor/editor/serializer/editorserializer.h"
#include "editor/network/client/editornetworkclient.h"

namespace unieditor
{
    class Editor
    {
    public:
        void Init();
        void Run();
        void Update();

    private:
        EditorSerializer m_Serializer;
        EditorNetworkClient m_NetworkClient;
    };
}