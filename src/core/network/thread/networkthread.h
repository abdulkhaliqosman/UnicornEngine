#pragma once

#include <WinSock2.h>
#include "core/container/list.h"
#include "core/thread/base/threadbase.h"

namespace unicore
{
    constexpr int PACKET_LENGTH = 512;

    class RecvListener
    {
    public:
        SOCKET GetSocket() { return m_Socket; }
        void SetSocket(SOCKET s) { m_Socket = s; }

        virtual void OnRecv(const char* recvData, int len) = 0;
    private:
        SOCKET m_Socket;
    };

    struct SendRequest
    {
        SOCKET sendSocket;
        size_t messageLength;
        unsigned char message[PACKET_LENGTH];
        
    };

    class NetworkThread : public ThreadBase
    {
    public:
        void Init() override;
        void Run() override;

        bool AddRecvListener(RecvListener* listener);
        bool RemoveRecvListener(RecvListener* listener);

        void AddSendRequest(SendRequest* sendRequest);
    private:
        void Update();
        void Send();
        void Recv();

        List<RecvListener*> m_RecvListeners; // change to unordered set
        List<SendRequest*> m_SendRequests; // use unique ptr to pass ownership

        HANDLE m_Mutex;
    };
}