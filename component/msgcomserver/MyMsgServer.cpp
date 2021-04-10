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
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::DispatchMessage>>MsgType Is REQUEST_MSG_TYPE!\n"));
        SendMsgToService(pMsg);
    }
    else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::DispatchMessage>>MsgType Is RESPONSE_MSG_TYPE!\n"));
        SendMsgToClient(pMsg);
    }
}

void MyMsgServer::SendMsgToService(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>nCmdCode:%d\n", pMsg->Header.nCmdCode));
    if (pMsg->Header.nCmdCode == CMD_MSG_SERVICE_REGISTER)
    {
        string strIP = UintToStringIP(pMsg->Header.nServerIP);
        MyClientHandle *pClientSock = new MyClientHandle(pMsg->Header.nServerPort, strIP);
        pMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
        if (!pClientSock->ConnectToServer())
        {
            pMsg->Header.nMsgRet = 0;
            m_nSendProcMapSocket.insert(map<int, MyClientHandle*>::value_type(pMsg->Header.nRecvProc, pClientSock));
        }
        else
        {
            pMsg->Header.nMsgRet = -1;
        }

        this->push(pMsg);
    }
    else 
    {
        const int BUFFER_MAX = 2048;
        char buf[BUFFER_MAX] = { 0 };
        map<int, MyClientHandle*>::iterator iter = m_nSendProcMapSocket.find(pMsg->Header.nRecvProc);
        if (iter != m_nSendProcMapSocket.end())
        {
            pData = encode(pMsg, length);
            int sendCnt = iter->second->SendToServer(pData, length);
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>sendCnt:%d, errno:%d\n", sendCnt, errno));

            int recvCnt = iter->second->RecvFromServer(buf, BUFFER_MAX);
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>recvCnt:%d, errno:%d\n", recvCnt, errno));
            if (recvCnt > 0)
            {
                if (!this->parser(buf, recvCnt))
                {
                    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>parser msg failed!\n"));
                }
                else
                {
                    cout << "!" << endl;
                    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToService>>parser msg successful!\n"));
                }
            }
            
        }
    }
}

void MyMsgServer::SendMsgToClient(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    string strIP = UintToStringIP(pMsg->Header.nClientIP);
    string strIPInfo = strIP + ":" + to_string(pMsg->Header.nClientPort);
    map<string, ACE_SOCK_Stream*>::iterator iter = m_strIPMapSocket.find(strIPInfo);
    if (iter != m_strIPMapSocket.end())
    {
        pData = encode(pMsg, length);
        int sendCnt = iter->second->send_n(pData, length);
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServer::SendMsgToClient>>sendCnt:%d, errno:%d\n", sendCnt, errno));
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
