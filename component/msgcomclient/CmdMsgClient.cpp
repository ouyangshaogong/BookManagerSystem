#include "CmdMsgClient.h"

CmdMsgClient::CmdMsgClient()
{

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

    uint32_t nLength = 0;
    uint8_t* pData = NULL;
    pData = m_protoEncode.encode(&m_protoMsg, nLength);
    m_pConnecotorHandle->SendCmdMsgToServer(pData, nLength);

    TaskMgr *pTaskMgr = m_pTaskMgrApp->GetTaskMgr(m_protoMsg.Header.nTaskMgrID);
    Task *pTask = pTaskMgr->GetTask(m_protoMsg.Header.nTaskID);
    pTask->WaitSignal();
    pTask->GetResultValue(result);
}

Json::Value& CmdMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}




