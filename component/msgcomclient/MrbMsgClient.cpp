#include "MrbMsgClient.h"

extern MyMsgQueue g_pMsgQueue;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300


MrbMsgClient::MrbMsgClient()
    :m_nMsgID(1)
{
    
}

MrbMsgClient::~MrbMsgClient()
{

}


void MrbMsgClient::SetMsgValue(int nSendProc, int nTaskMgrID, TaskID nTaskID)
{
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nMsgType = REQUEST_MSG_TYPE;
    m_protoMsg.Header.nSendProc = nSendProc;
    m_protoMsg.Header.nTaskMgrID = nTaskMgrID;
    m_protoMsg.Header.nTaskID = nTaskID;
}


void MrbMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result)
{
    
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nCmdMsg = nCmdMsg;
    //¸ù¾ÝMrbCmdÅÐ¶Ï
    m_protoMsg.Header.nRecvProc = 0;

    MyProtoMsg *pInMsg = new MyProtoMsg;
    g_pMsgQueue.push(pInMsg);

    
    TaskMgr *pTaskMgr = m_pClientTaskMgrApp->GetTaskMgr(m_protoMsg.Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(m_protoMsg.Header.nTaskID);
    MyProtoMsg *pOutMsg = pTask->WaitSignal();
    
}

Json::Value& MrbMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}




