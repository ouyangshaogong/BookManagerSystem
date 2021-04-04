#ifndef __MY_MSG_CLIENT__
#define __MY_MSG_CLIENT__

#include "MyProtoMsg.h"
#include "MyMsgQueue.h"
#include "MyClientHandle.h"

//nCmdMsg
const int CMD_MSG_SERVICE_REGISTER = 1;

//nMsgType
#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

class MyMsgServer: public MyMsgQueue
{
private:
    MyMsgServer();

public:
    ~MyMsgServer();
    static MyMsgServer* Instance();

    virtual void DispatchMessage(MyProtoMsg* pMsg);
    void SendMsgToService(MyProtoMsg* pMsg);
    void SendMsgToClient(MyProtoMsg* pMsg);

    void GetSockPeer(string strIP, ACE_SOCK_Stream *pPeer);
    void DeleteSockPeer(string strIP);

private:
    static ACE_Thread_Mutex m_mutex;
    static MyMsgServer *m_instance;

    map<int, MyClientHandle*> m_nSendProcMapSocket;  //连接服务器的socket
    map<string, ACE_SOCK_Stream*> m_strIPMapSocket;  //连接客户端的socket
};

#endif
