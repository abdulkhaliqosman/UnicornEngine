#pragma once
#include "core/coreheader.h"

namespace unieditor
{
    class EditorNetworkClient : public ucc::NetworkClient
    {
        void OnSocketConnected() override;
    };
}