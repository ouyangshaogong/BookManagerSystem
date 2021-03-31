#include "CmdMsgClient.h"

extern MyMsgQueue g_pMsgQueue;


CmdMsgClient::CmdMsgClient(int nSendProc, int nTaskMgrID, TaskID nTaskID)
    :m_nMsgID(1)
{
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nMsgType = REQUEST_MSG_TYPE;
    m_protoMsg.Header.nSendProc = nSendProc;
    m_protoMsg.Header.nTaskMgrID = nTaskMgrID;
    m_protoMsg.Header.nTaskID = nTaskID;
}

CmdMsgClient::~CmdMsgClient()
{

}


void CmdMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result)
{
    
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nCmdMsg = nCmdMsg;
    //¸ù¾ÝMrbCmdÅÐ¶Ï
    m_protoMsg.Header.nRecvProc = 0;

    MyProtoMsg *pInMsg = new MyProtoMsg;
    g_pMsgQueue.push(pMsg);

    
    TaskMgr *pTaskMgr = m_pClientTaskMgrApp->GetTaskMgr(pMsg->Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(pMsg->Header.nTaskID);
    MyProtoMsg *pOutMsg = pTask->WaitSignal();
    
}

Json::Value& CmdMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}




