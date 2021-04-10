#include "MyMsgServer.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

ACE_Thread_Mutex MyMsgServer::m_mutex;
MyMsgServer* MyMsgServer::m_instance = NULL;

MyMsgServer::MyMsgServer(TaskMgrApp *pTaskMgrApp)
:m_pTaskMgrApp(pTaskMgrApp)
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

MyMsgServer* MyMsgServer::Instance(TaskMgrApp *pTaskMgrApp)
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new MyMsgServer(pTaskMgrApp);
        }
    }
    
    return m_instance;
}

MyMsgServer* MyMsgServer::Instance()
{
    return m_instance;
}


void MyMsgServer::DispatchMessage(MyProtoMsg* pMsg)
{
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        SendCmdMsgToTask(pMsg);
    }
    else if(pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is RESPONSE_MSG_TYPE!\n"));
        SendCmdMsgToServer(pMsg);
    }
}

void MyMsgServer::GetSockPeer(string strIP, ACE_SOCK_Stream *pPeer)
{
    m_IPMapSockPeer.insert(map<string, ACE_SOCK_Stream*>::value_type(strIP, pPeer));
}

void MyMsgServer::DeleteSockPeer(string strIP)
{
    map<string, ACE_SOCK_Stream*>::iterator iter = m_IPMapSockPeer.find(strIP);
    if (iter != m_IPMapSockPeer.end())
    {
        m_IPMapSockPeer.erase(iter);
    }

}

void MyMsgServer::SendCmdMsgToTask(MyProtoMsg* pMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgServiceHandle::SendCmdMsgToTask>>\n"));
    pMsg->Header.display();
    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(pMsg->Header.nTaskMgrID);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgServiceHandle::SendCmdMsgToTask>>pTaskMgr:%d\n", pTaskMgr));
    Task *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgServiceHandle::SendCmdMsgToTask>>pTask:%d\n", pTask));
    pTask->SendMsgToTask(pMsg);
}


int MyMsgServer::SendCmdMsgToServer(MyProtoMsg* pMsg)
{
    uint8_t *pData = NULL;
    uint32_t length = 0;
    pData = encode(pMsg, length);
    string strPort = to_string(pMsg->Header.nServerPort);
    string strIP = UintToStringIP(pMsg->Header.nServerIP);
    
    string strIPInfo = strIP + ":" + strPort;
    map<string, ACE_SOCK_Stream*>::iterator iter = m_IPMapSockPeer.find(strIPInfo);
    if (iter != m_IPMapSockPeer.end())
    {
        int send_cnt = iter->second->send_n(pData, length);
        if (send_cnt == 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
            return -1;
        }

        if (send_cnt < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
            return 0;
        }
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>send_cnt:%d, errno:%d\n", send_cnt, errno));
    }
}

