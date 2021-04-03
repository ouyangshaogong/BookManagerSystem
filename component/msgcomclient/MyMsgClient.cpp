#include "MyMsgClient.h"


#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

MyClientSockHandle::MyClientSockHandle()
:m_remoteAddr(5000, "127.0.0.1")
{

}

MyClientSockHandle::~MyClientSockHandle()
{

}


MyMsgClient::MyMsgClient()
    :m_nMsgID(1)
{
    m_sockHandle.connect_to_server();
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
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::SetMsgValue>>nTaskMgrID:%d, nTaskID:%d\n", nTaskMgrID, nTaskID));
}


int MyMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result)
{
    //ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    ACE_OS::sleep(5);
    m_protoMsg.Header.nMsgID = m_nMsgID++;
    m_protoMsg.Header.nCmdMsg = nCmdMsg;
    //¸ù¾ÝMrbCmdÅÐ¶Ï
    m_protoMsg.Header.nRecvProc = 0;

    MyProtoMsg *pInMsg = new MyProtoMsg;
    *pInMsg = m_protoMsg;

    uint8_t *pData = NULL;
    uint32_t length = 0;
    //pData = m_msgQueue.encode(pInMsg, length);
    
    uint8_t buf[2048] = {0};
    uint32_t retLength = 0;

    MyProtoMsg *pOutMsg = new MyProtoMsg;
    m_sockHandle.send_to_server(pData, length, pOutMsg, buf, 2048);
    
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MrbMsgClient::CallMethod>>nTaskMgrID:%d, nTaskID:%d\n", m_protoMsg.Header.nTaskMgrID, m_protoMsg.Header.nTaskID));
    return 0;

}

Json::Value& MyMsgClient::CallMethod(int nCmdMsg, const Json::Value &parameter)
{

}




