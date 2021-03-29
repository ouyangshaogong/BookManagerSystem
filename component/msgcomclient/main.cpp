#include "iMapMsgHandle.h"
#include "ace/OS.h"
#include "ace/ACE.h"
#include "ace/Init_ACE.h"

using namespace std;


ACE_THR_FUNC_RETURN Work(void *arg)
{
    ACE_OS::sleep(5);
    iMapMsgHandle *pCmdHandle = (iMapMsgHandle*)arg;
    MyProtoEncode protoEncode;
    int i = 0;
    for (; i < 2; i++)
    {
        uint32_t length = 0;
        uint8_t* pData = NULL;
        MyProtoMsg *pMsg = new MyProtoMsg;

        if (i == 0)
        {
            pMsg->Header.nCmdMsg = CMD_MSG_SERVICE_REGISTER;
            pMsg->Header.nSendProc = SEND_PROC_ID;
            pMsg->Header.nRecvProc = 0;
        }
        else
        {
            pMsg->Header.nCmdMsg = i + 1;
            pMsg->Header.nSendProc = SEND_PROC_ID;
            pMsg->Header.nRecvProc = RECV_PROC_ID;
        }

        pMsg->Header.nMsgID = i + 1;
        pMsg->Header.nMsgType = REQUEST_MSG_TYPE;
        pMsg->Body["string"] = "string";
        pData = protoEncode.encode(pMsg, length);
        pCmdHandle->SendCmdMsgToQueue(pData, length);
        ACE_OS::sleep(1);
    }
}



int ACE_TMAIN(int argc, char* argv[])
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)Message Communicate Client Start.......\n"));
    //���ԭ���ı�־������������������ļ���ͬʱҲ����console�������
    //ACE_LOG_MSG->clr_flags(ACE_Log_Msg::STDERR);
    //ACE_LOG_MSG->set_flags(ACE_Log_Msg::OSTREAM);
    //�����ļ������������ļ����
    const char * filename = "iMapMsgClient.log";
    ofstream out(filename, ios::out | ios::trunc);
    //ios::out��д�ķ�ʽ�򿪣�ios::trunc����ļ�;
    //ACE_LOG_MSG->msg_ostream(&out);
    
    iMapMsgHandle *pCmdHandle = iMapMsgHandle::Instance();
    iMapConnectorHandle m_connectorHandle(pCmdHandle);

    m_connectorHandle.open();
    pCmdHandle->open(&m_connectorHandle);

    //������Ϣѭ���߳�,����һ����Ϣͨ�ſͻ�����Ϣѭ��
    ACE_Thread_Manager::instance()->spawn_n(1, Work, pCmdHandle);

    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }

    //�ȴ��߳��˳�
    ACE_Thread_Manager::instance()->wait();
    ACE_DEBUG((LM_DEBUG, "(%P|%t|)Message Communicate Client End.......\n"));
    return 0;
}
