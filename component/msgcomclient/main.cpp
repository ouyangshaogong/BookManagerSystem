#include "iMapMsgHandle.h"
#include "ace/OS.h"
#include "ace/ACE.h"
#include "ace/Init_ACE.h"

using namespace std;

const int CMD_MSG_SERVICE_REGISTER = 1;

ACE_THR_FUNC_RETURN Work(void *arg)
{
    ACE_OS::sleep(5);
    iMapMsgHandle *pCmdHandle = (iMapMsgHandle*)arg;
    int i = 0;
    for (; i < 5; i++)
    {
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

        if (i == 0)
        {
            pCmdMsg->SetMrbCmdMsg(CMD_MSG_SERVICE_REGISTER);
            pCmdMsg->SetSendProc(SEND_PROC_ID);
            pCmdMsg->SetRecvProc(0);
        }
        else
        {
            pCmdMsg->SetMrbCmdMsg(i + 1);
            pCmdMsg->SetSendProc(SEND_PROC_ID);
            pCmdMsg->SetRecvProc(RECV_PROC_ID);
        }

        pCmdMsg->SetMsgID(i + 1);
        pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);

        string str("test");
        pCmdMsg->SetBody(str);
        pCmdMsg->SetMsgLength(sizeof(iMapCmdMsg) + pCmdMsg->GetBody().length());
        pCmdMsg->display("display");
        pCmdHandle->SendCmdMsgToQueue(pCmdMsg);
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
