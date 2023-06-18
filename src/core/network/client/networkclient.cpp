#include "networkclient.h"
#include <ws2tcpip.h>
#include <stdio.h>
#include <cassert>

#pragma comment(lib, "Ws2_32.lib")

namespace unicore
{
    
    constexpr const char DEFAULT_PORT[] = "27016";
    constexpr const char DEFAULT_ADDRESS[] = "127.0.0.1";

    void NetworkClient::Init()
    {
        WSADATA wsaData;

        // 1. Initialize Winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            printf("WSAStartup failed: %d\n", iResult);
            return;
        }

        CreateSocket();
    }

    void NetworkClient::Update()
    {
        if (m_SocketState == SocketState::Created)
        {
            ConnectSocket();
        }
        
        if (m_SocketState == SocketState::Connected)
        {
            static int slicer = 0;
            slicer++;
            if ((slicer % 1000) != 0)
            {
                return;
            }
            const char* sendbuf = "this is a test";
            // Send an initial buffer
            int iResult = send(m_Socket, sendbuf, (int)strlen(sendbuf), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("NetworkClient::Update() send failed: %d\n", WSAGetLastError());
                closesocket(m_Socket);
                return;
            }

            printf("NetworkClient::Update() Bytes Sent: %d\n", iResult);
        }
    }

    void NetworkClient::Shutdown()
    {
        if (m_SocketState == SocketState::Connected)
        {
            ShutdownSocket();
        }
        if (m_SocketState == SocketState::Created || m_SocketState == SocketState::Shutdown)
        {
            CloseSocket();
        }
        WSACleanup();

        if (m_ServerAddrInfo != nullptr)
        {
            freeaddrinfo(m_ServerAddrInfo);
            m_ServerAddrInfo = nullptr;
        }
    }

    void NetworkClient::Send(const char* sendData, int len)
    {
    }

    void NetworkClient::CreateSocket()
    {
        assert(m_Socket == INVALID_SOCKET);

        addrinfo hints;
        ZeroMemory(&hints, sizeof(hints));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        int getResult = getaddrinfo(DEFAULT_ADDRESS, DEFAULT_PORT, &hints, &m_ServerAddrInfo);
        if (getResult != 0)
        {
            printf("getaddrinfo failed: %d\n", getResult);
            return;
        }

        // Attempt to connect to the first address returned by
        // the call to getaddrinfo
        addrinfo* ptr = m_ServerAddrInfo;

        m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (m_Socket == INVALID_SOCKET)
        {
            printf("Error at socket(): %d\n", WSAGetLastError());
            freeaddrinfo(ptr);
            m_ServerAddrInfo = nullptr;
            return;
        }
        
        printf("NetworkClient::CreateSocket() socket created\n");
        m_SocketState = SocketState::Created;
    }

    void NetworkClient::ConnectSocket()
    {
        // fd_set readset;
        // FD_ZERO(&readset);
        // FD_SET(m_Socket, &readset);
        // 
        // TIMEVAL timeout;
        // timeout.tv_sec = 0;
        // timeout.tv_usec = 1000;
        // 
        // int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
        // if (readyfd == SOCKET_ERROR)
        // {
        //     printf("NetworkClient::ConnectSocket(): select failed: %d\n", WSAGetLastError());
        //     CloseSocket();
        //     return;
        // }
        // 
        // if (readyfd == 0)
        // {
        //     // no fd just early out
        //     return;
        // }


        addrinfo* ptr = m_ServerAddrInfo;

        int connResult = connect(m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (connResult == SOCKET_ERROR)
        {
            printf("NetworkClient::ConnectSocket(): connect failed: %d\n", WSAGetLastError());
            CloseSocket();
            return;
        }

        printf("NetworkClient::CreateSocket() socket connected\n");
        m_SocketState = SocketState::Connected;
        OnSocketConnected();
    }

    void NetworkClient::ShutdownSocket()
    {
        printf("NetworkClient::ShutdownSocket()\n");
        int result = shutdown(m_Socket, SD_BOTH);
        if (result == SOCKET_ERROR)
        {
            printf("shutdown failed: %d\n", WSAGetLastError());
        }

        m_SocketState = SocketState::Shutdown;
    }

    void NetworkClient::CloseSocket()
    {
        printf("NetworkClient::CloseSocket()\n");
        closesocket(m_Socket);
        m_Socket = INVALID_SOCKET;

        m_SocketState = SocketState::Closed;
    }

    void NetworkClient::Recv()
    {
        do
        {
            fd_set readset;
            FD_ZERO(&readset);
            FD_SET(m_Socket, &readset);

            TIMEVAL timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 1000;

            int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
            if (readyfd == SOCKET_ERROR)
            {
                printf("NetworkClient::ConnectSocket(): select failed: %d\n", WSAGetLastError());
                ShutdownSocket();
                CloseSocket();
                return;
            }

            if (readyfd == 0)
            {
                // no fd just early out
                return;
            }

            // Receive data until the server closes the connection
            if (FD_ISSET(m_Socket, &readset))
            {
                char recvbuf[PACKET_LENGTH];
                int recvbuflen = PACKET_LENGTH;
                int iResult = recv(m_Socket, recvbuf, recvbuflen, 0);
                if (iResult > 0)
                {
                    printf("Bytes received: %d\n", iResult);
                }
                else if (iResult == 0)
                {
                    printf("Connection closed\n");
                    ShutdownSocket();
                    CloseSocket();
                    return;
                }
                else
                {
                    printf("recv failed: %d\n", WSAGetLastError());
                    ShutdownSocket();
                    CloseSocket();
                    return;
                }
            }
        }
        while (true); // TODO timeslice
    }
}
