#include "MyMsgServer.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

ACE_Thread_Mutex MyMsgServer::m_mutex;
MyMsgServer* MyMsgServer::m_instance = NULL;

MyMsgServer::MyMsgServer()
{
    
}

MyMsgServer::~MyMsgServer()
{
    if (NULL != m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

MyMsgServer* MyMsgServer::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new MyMsgServer();
        }
    }
    
    return m_instance;
}


void MyMsgServer::DispatchMessage(MyProtoMsg* pMsg)
{
    //如果是消息请求，根据发送进程ID，找到socket，发生数据到相应service
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        SendMsgToService(pMsg);
    }
    //如果是消息响应，根据接受进程ID，找到socket，发生数据到相应的客户端
    else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is RESPONSE_MSG_TYPE!\n"));
        SendMsgToClient(pMsg);
    }
}

void MyMsgServer::SendMsgToService(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    if (pMsg->Header.nCmdMsg == CMD_MSG_SERVICE_REGISTER)  //发送进程是服务器端，接收进程为服务器端
    {
        MyClientHandle *pClientSock = new MyClientHandle(pMsg->Header.nPort, pMsg->Header.strIP);
        if (!pClientSock->ConnectToServer())
        {
            pMsg->Header.nMsgRet = 0;//表示连接成功
            m_nSendProcMapSocket.insert(map<int, MyClientHandle*>::value_type(pMsg->Header.nSendProc, pClientSock));
        }
        else
        {
            pMsg->Header.nMsgRet = -1;//表示连接失败
        }

        pData = encode(pMsg, length);
        pClientSock->SendToServer(pData, length);
    }
    else //其他发送进程是客户请求端，接收进程为该服务器端
    {
        const int BUFFER_MAX = 2048;
        char buf[BUFFER_MAX] = { 0 };
        map<int, MyClientHandle*>::iterator iter = m_nSendProcMapSocket.find(pMsg->Header.nSendProc);
        if (iter != m_nSendProcMapSocket.end())
        {
            int sendCnt = iter->second->SendToServer(pData, length);
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>sendCnt:%d, errno:%d\n", sendCnt, errno));

            int recvCnt = iter->second->RecvFromServer(buf, BUFFER_MAX);
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>recvCnt:%d, errno:%d\n", recvCnt, errno));

            if (!this->parser(buf, recvCnt))
            {
                cout << "parser msg failed!" << endl;
            }
            else
            {
                cout << "parser msg successful!" << endl;
            }
        }
    }
}

//发响应回客户端
void MyMsgServer::SendMsgToClient(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    string strIPInfo = pMsg->Header.strIP + ":" + to_string(pMsg->Header.nPort);
    map<string, ACE_SOCK_Stream*>::iterator iter = m_strIPMapSocket.find(strIPInfo);
    if (iter != m_strIPMapSocket.end())
    {
        pData = encode(pMsg, length);
        int sendCnt = iter->second->send_n(pData, length);
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>sendCnt:%d, errno:%d\n", sendCnt, errno));
    }
}

void MyMsgServer::GetSockPeer(string strIP, ACE_SOCK_Stream *pPeer)
{
    m_strIPMapSocket.insert(map<string, ACE_SOCK_Stream*>::value_type(strIP, pPeer));
}

void MyMsgServer::DeleteSockPeer(string strIP)
{
    map<string, ACE_SOCK_Stream*>::iterator iter = m_strIPMapSocket.find(strIP);
    if (iter != m_strIPMapSocket.end())
    {
        iter->second->close();
        m_strIPMapSocket.erase(iter);
    }

}
