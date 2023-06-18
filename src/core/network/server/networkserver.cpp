#include "networkserver.h"
#include <ws2tcpip.h>
#include <stdio.h>
#include <cassert>

#pragma comment(lib, "Ws2_32.lib")

namespace unicore
{
    constexpr const char DEFAULT_PORT[] = "27016";

    void NetworkServer::Init()
    {
        NetworkBase::Init();

        WSADATA wsaData;

        // 1. Initialize Winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            printf("WSAStartup failed: %d\n", iResult);
            return;
        }

        CreateListenSocket();
    }

    void NetworkServer::Update()
    {
        // poll (select) new client sockets to accept
        AcceptClientSockets();

        // poll (select) current client sockets to recv
        RecvClientSockets();
    }
    
    void NetworkServer::Shutdown()
    {

    }

    void NetworkServer::CreateListenSocket()
    {
        printf("NetworkServer::CreateListenSocket()\n");
        // 2. Create a socket.
        assert(m_ListenSocket == INVALID_SOCKET);

        addrinfo* result = nullptr;
        addrinfo* ptr = nullptr;
        addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and port to be used by the server
        int getResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
        if (getResult != 0)
        {
            printf("getaddrinfo failed: %d\n", getResult);
            WSACleanup();
            return;
        }

        // Create a SOCKET for the server to listen for client connections

        m_ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (m_ListenSocket == INVALID_SOCKET)
        {
            printf("Error at socket(): %d\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return;
        }

        // 3. Bind the socket.
        
        // Setup the TCP listening socket
        int bindResult = bind(m_ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (bindResult == SOCKET_ERROR)
        {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(m_ListenSocket);
            WSACleanup();
            return;
        }

        freeaddrinfo(result);

        if (listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            printf("Listen failed with error: %d\n", WSAGetLastError());
            closesocket(m_ListenSocket);
            WSACleanup();
            return;
        }
        
        char addr_str[256]{ 0 };
        inet_ntop(result->ai_family, result->ai_addr, addr_str, 256);
        printf("Listen socket created at %s\n", addr_str);
    }

    void NetworkServer::CloseClientSocket(SOCKET client)
    {
        for (int i = 0; i < m_ClientSockets.size(); ++i)
        {
            if (client == m_ClientSockets[i])
            {
                // 7. Disconnect.
                // shutdown the send half of the connection since no more data will be sent
                int iResult = shutdown(client, SD_BOTH);
                if (iResult == SOCKET_ERROR)
                {
                    printf("shutdown failed: %d\n", WSAGetLastError());
                }

                // cleanup
                closesocket(client);
                WSACleanup();
                m_ClientSockets.erase(m_ClientSockets.begin() + i);
                return;
            }
        }
        printf("CloseClientSocket() failed, cannot find socket\n");

        return;
    }

    void NetworkServer::AcceptClientSockets()
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(m_ListenSocket, &readset);

        TIMEVAL timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
        int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
        if (readyfd == SOCKET_ERROR)
        {
            // printf("select failed: %d\n", WSAGetLastError());
            return;
        }

        if (readyfd == 0)
        {
            // no fd just early out
            return;
        }

        // 4. Accept a connection from a client.
        SOCKET clientSocket = INVALID_SOCKET;

        // Accept a client socket
        sockaddr addr;
        int size = sizeof(addr);
        ZeroMemory(&addr, size);

        clientSocket = accept(m_ListenSocket, &addr, &size);

        if (clientSocket == INVALID_SOCKET)
        {
            printf("accept failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            // WSACleanup();
            return;
        }
        if (addr.sa_family == AF_INET)
        {
            char strbuf[256] = { 0 };

            const sockaddr_in* addrin = reinterpret_cast<sockaddr_in*>(&addr);
            inet_ntop(addr.sa_family, &addrin->sin_addr, strbuf, 256);

            printf("accept socket: %s", strbuf);
        }

        m_ClientSockets.push_back(clientSocket);
    }

    void NetworkServer::RecvClientSockets()
    {
        for (const SOCKET& sock : m_ClientSockets)
        {
            int iResult = 0;
            fd_set readset;
            FD_ZERO(&readset);
            FD_SET(sock, &readset);

            TIMEVAL timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 1000;
            int readyfd = select(0, &readset, nullptr, nullptr, &timeout);
            if (readyfd == SOCKET_ERROR)
            {
                // printf("select failed: %d\n", WSAGetLastError());
                continue;
            }
            printf("RecvClientSockets() readyfd = %d\n", readyfd);
            if (readyfd == 0)
            {
                // no fd just early out
                continue;
            }

            


            // Receive until the peer shuts down the connection
            do
            {
                int iSendResult;
                int recvbuflen = PACKET_LENGTH;
                char recvbuf[PACKET_LENGTH];
                iResult = recv(sock, recvbuf, recvbuflen, 0);
                if (iResult > 0)
                {
                    recvbuf[iResult] = 0;
                    printf("NetworkServer recv[%d]: %s \n", iResult, recvbuf);

                    // Echo the buffer back to the sender
                    iSendResult = send(sock, recvbuf, iResult, 0);
                    if (iSendResult == SOCKET_ERROR)
                    {
                        printf("NetworkServer::RecvClientSockets() send failed: %d\n", WSAGetLastError());
                        closesocket(sock);
                        break;
                    }
                    printf("RecvClientSockets() Bytes sent: %d\n", iSendResult);
                }
                else if (iResult == 0)
                {
                    printf("Connection closing...\n");
                }
                else
                {
                    printf("recv failed: %d\n", WSAGetLastError());
                    closesocket(sock);
                    break;
                }
            
            }
            while (iResult > 0);
        }
    }
}
