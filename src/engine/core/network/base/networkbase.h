#pragma once

#include "core/network/thread/networkthread.h"

namespace Unicorn
{
    class NetworkBase
    {
    public:
        virtual ~NetworkBase();
        void Init();
        inline void SetNetworkThread(NetworkThread* thread) { m_NetworkThread = thread; }

        void AddSocketListener(SOCKET socket);
        void RemoveSocketListener(SOCKET socket);
        void AddSendRequest(SendRequest* sendRequest);

    private:
        NetworkThread* m_NetworkThread = nullptr; //TODO: shared ptr
    };
}
