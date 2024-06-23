#pragma once

#include "core/network/base/networkbase.h"

namespace unicore
{
    class NetworkServer : public NetworkBase
    {
    public:
        void Init();
        void Update();
        void Shutdown();

    private:
        bool SelectSocket(SOCKET socket);

        void CreateListenSocket();
        void CloseListenSocket();

        void AcceptClientSockets();
        void RecvClientSockets();
        void CloseClientSocket(SOCKET client);

        SOCKET m_ListenSocket = INVALID_SOCKET;
        List<SOCKET> m_ClientSockets;
    };
}
