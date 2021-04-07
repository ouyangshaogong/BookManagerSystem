#include "MyMsgClient.h"


#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300


MyMsgClient::MyMsgClient()
    :m_nMsgID(1), m_sockHandle(5000, "127.0.0.1")
{
    m_sockHandle.ConnectToServer(m_strIP, m_nPort);
    m_pMsgServer = MyMsgServer::Instance();
}

MyMsgClient::~MyMsgClient()
{

}


void MyMsgClient::SetMsgValue(int nSendProc, int nTaskMgrID, int nTaskID)
{
    //ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nMsgType = REQUEST_MSG_TYPE;
    m_protoMsg.Header.nSendProc = nSendProc;
    m_protoMsg.Header.nTaskMgrID = nTaskMgrID;
    m_protoMsg.Header.nTaskID = nTaskID;
    m_protoMsg.Header.nClientIP = m_pMsgServer->StringIPToUint(m_strIP);
    m_protoMsg.Header.nClientPort = m_nPort;
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::SetMsgValue>>nTaskMgrID:%d, nTaskID:%d\n", nTaskMgrID, nTaskID));
}


int MyMsgClient::CallMethod(int nCmdCode, const Json::Value &parameter, Json::Value& result)
{
    //ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    ACE_OS::sleep(5);
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nServerIP = m_pMsgServer->StringIPToUint("127.0.0.1");
    m_protoMsg.Header.nServerPort = 5001;
    m_protoMsg.Header.nCmdCode = nCmdCode;
    //¸ù¾ÝMrbCmdÅÐ¶Ï
    m_protoMsg.Header.nRecvProc = 0;
    m_protoMsg.Body["test"] = "test";

    MyProtoMsg *pInMsg = new MyProtoMsg;
    *pInMsg = m_protoMsg;

    uint8_t *pData = NULL;
    uint32_t length = 0;
    pData = m_pMsgServer->encode(pInMsg, length);
    m_sockHandle.SendToServer(pData, length);

    MyProtoMsg *pOutMsg = new MyProtoMsg;
    const int BUFFER_MAX = 2048;
    uint8_t buf[BUFFER_MAX] = {0};
    //è¯»å–Header
    int recvCnt = m_sockHandle.RecvFromServer(buf, m_pMsgServer->GetHeaderLength());
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::CallMethod>>recvCnt:%d\n", recvCnt));
    m_pMsgServer->parserHead(pOutMsg, buf, recvCnt);
    
    //è¯»å–body
    memset(buf, 0, BUFFER_MAX);
    length = pOutMsg->Header.nMsgLength - m_pMsgServer->GetHeaderLength();
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::CallMethod>>length:%d, nMsgLength:%d\n", length, pOutMsg->Header.nMsgLength));
    recvCnt = m_sockHandle.RecvFromServer(buf, length);
    m_pMsgServer->parserBody(pOutMsg, buf, recvCnt);

    pOutMsg->Header.display();
    
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::CallMethod>>nTaskMgrID:%d, nTaskID:%d\n", m_protoMsg.Header.nTaskMgrID, m_protoMsg.Header.nTaskID));
    return 0;

}

Json::Value& MyMsgClient::CallMethod(int nCmdCode, const Json::Value &parameter)
{

}




