#ifndef __MY_CLIENT_SOCK_HANDLE__
#define __MY_CLIENT_SOCK_HANDLE__

#include <ace/OS.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Acceptor.h"
#include "ace/Log_Msg.h"
#include "commonace.h"
#include "MyProtoMsg.h"
#include "MyMsgQueue.h"
#include "ace/Thread.h"
#include "ace/Task.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread_Mutex.h"

class MyClientHandle
{
public:
    MyClientHandle(int nPort, string strIP);
    
    ~MyClientHandle();

    int ConnectToServer();

    int RecvFromServer(uint8_t *buf, uint32_t max_length);

    int SendToServer(uint8_t *pData, uint32_t nLength);

    int Close();

private:
    ACE_SOCK_Stream m_clientStream;
    ACE_INET_Addr m_remoteAddr;
    ACE_SOCK_Connector m_connector;
};

#endif

