#include "MrbMsgClient.h"

extern MyMsgQueue g_pMsgQueue;
extern ACE_Condition<ACE_Thread_Mutex> g_mMsgCond;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300


MrbMsgClient::MrbMsgClient(TaskMgrApp *pTaskMgrApp)
    :m_nMsgID(1), m_pTaskMgrApp(pTaskMgrApp), m_mutex()
{
    
}

MrbMsgClient::~MrbMsgClient()
{

}


void MrbMsgClient::SetMsgValue(int nSendProc, int nTaskMgrID, TaskID nTaskID)
{
    //ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nMsgType = REQUEST_MSG_TYPE;
    m_protoMsg.Header.nSendProc = nSendProc;
    m_protoMsg.Header.nTaskMgrID = nTaskMgrID;
    m_protoMsg.Header.nTaskID = nTaskID;
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::SetMsgValue>>nTaskMgrID:%d, nTaskID:%d\n", nTaskMgrID, nTaskID));
}


void MrbMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result)
{
    //ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    ACE_OS::sleep(5);
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nCmdMsg = nCmdMsg;
    //¸ù¾ÝMrbCmdÅÐ¶Ï
    m_protoMsg.Header.nRecvProc = 0;

    MyProtoMsg *pInMsg = new MyProtoMsg;
    *pInMsg = m_protoMsg;
    g_pMsgQueue.push(pInMsg);
    g_mMsgCond.signal();
    
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::CallMethod>>nTaskMgrID:%d, nTaskID:%d\n", m_protoMsg.Header.nTaskMgrID, m_protoMsg.Header.nTaskID));
    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(m_protoMsg.Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(m_protoMsg.Header.nTaskID);
    MyProtoMsg *pOutMsg = pTask->WaitSignal();
    pOutMsg->Header.display();
}

Json::Value& MrbMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}




