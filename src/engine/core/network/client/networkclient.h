#pragma once

#include "core/network/base/networkbase.h"

namespace Unicorn
{
    class NetworkClient : public NetworkBase
    {
    public:
        enum class SocketState
        {
            Uninitialized = 0,
            Created,
            Connected,
            Shutdown,
            Closed
        };

        void Init();
        void Update();
        void Shutdown();

        void Send(const char* sendData, int len);

        inline SocketState GetSocketState() const { return m_SocketState; }
    private:
        void CreateSocket();
        void ConnectSocket();

        void ShutdownSocket();
        void CloseSocket();

        void Recv();
        virtual void OnSocketConnected() = 0;

        SOCKET m_Socket = INVALID_SOCKET;
        addrinfo* m_ServerAddrInfo = nullptr;
        SocketState m_SocketState = SocketState::Uninitialized;
    };
}
