#include "core/network/thread/networkthread.h"
#include <stdio.h>

namespace unicore
{
    void NetworkThread::Init()
    {
        m_Mutex = CreateMutexEx(nullptr, nullptr, 0, STANDARD_RIGHTS_ALL);
        
    }

    void NetworkThread::Run()
    {
        while (1) // TODO make thread killable
        {
            Update();
            SleepEx(100, true);
        }
    }

    bool NetworkThread::AddRecvListener(RecvListener* listener)
    {
        WaitForSingleObject(m_Mutex, INFINITE); // TODO guard lock
        for (RecvListener* l : m_RecvListeners)
        {
            if (listener == l)
            {
                ReleaseMutex(m_Mutex); // TODO guard lock
                return false;
            }
        }

        m_RecvListeners.push_back(listener);
        ReleaseMutex(m_Mutex); // TODO guard lock
        return true;
    }

    bool NetworkThread::RemoveRecvListener(RecvListener* listener)
    {
        for (int i = 0; i < m_RecvListeners.size(); ++i)
        {
            if (m_RecvListeners[i] == listener)
            {
                // AddRecvListener should guarantee that only 1 listener exists
                m_RecvListeners.erase(m_RecvListeners.begin() + i);
                ReleaseMutex(m_Mutex); // TODO guard lock
                return true;
            }
        }
        ReleaseMutex(m_Mutex); // TODO guard lock
        return false;
    }

    void NetworkThread::AddSendRequest(SendRequest* sendRequest)
    {
        WaitForSingleObject(m_Mutex, INFINITE); // TODO guard lock
        m_SendRequests.push_back(sendRequest);
        ReleaseMutex(m_Mutex); // TODO guard lock
    }

    void NetworkThread::Update()
    {
        Send();
        Recv();
    }

    void NetworkThread::Send()
    {
        WaitForSingleObject(m_Mutex, INFINITE); // TODO guard lock
        // copy
        List<SendRequest*> sendingRequests = m_SendRequests;
        m_SendRequests.clear();
        ReleaseMutex(m_Mutex); // TODO guard lock

        List<SendRequest*> unsentRequests;
        for (SendRequest* req : m_SendRequests)
        {
            // test if ready
            // if ready send
        }
        WaitForSingleObject(m_Mutex, INFINITE); // TODO guard lock
        m_SendRequests.insert(m_SendRequests.end(), unsentRequests.begin(), unsentRequests.end());
        ReleaseMutex(m_Mutex); // TODO guard lock
    }

    void NetworkThread::Recv()
    {
        WaitForSingleObject(m_Mutex, INFINITE); // TODO guard lock
        // copy
        ReleaseMutex(m_Mutex); // TODO guard lock

    }
}