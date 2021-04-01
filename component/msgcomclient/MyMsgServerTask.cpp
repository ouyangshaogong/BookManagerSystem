#include "MyMsgServerTask.h"

const int CMD_MSG_SERVICE_REGISTER = 1;

const int SEND_PROC_ID = 51;
const int RECV_PROC_ID = 50;


MyMsgServerTask::MyMsgServerTask()
{

}

MyMsgServerTask::MyMsgServerTask(MyMsgServer *pMsgServer)
    :m_nMsgID(1), m_pMsgServer(pMsgServer)
{
    
}


MyMsgServerTask::~MyMsgServerTask()
{
}

int MyMsgServerTask::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServerTask::open>>\n"));
    activate(THR_NEW_LWP, m_nThreadNum);
    return 0;
}


int MyMsgServerTask::svc()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServerTask::svc>>\n"));
    ACE_Message_Block* pMsgBlock = NULL;
    while (true)
    {
        if (this->getq(pMsgBlock) == -1)
        {
            continue;
        }

        if (NULL == pMsgBlock)
        {
            continue;
        }

        if (pMsgBlock->msg_type() == ACE_Message_Block::MB_STOP)
        {
            pMsgBlock->release();
            break;
        }

        ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::svc>>msg_type\n"));
        MyProtoMsg *pMsg = (MyProtoMsg*)pMsgBlock->base();
        int nLength = pMsgBlock->length();
        if (pMsg->Header.nSendProc == SEND_PROC_ID) //如果是我自己的进程
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::svc>>(MY)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pMsg->Header.nSendProc, pMsg->Header.nRecvProc, pMsg->Header.nCmdMsg));
            if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE) //别人对我的响应
            {
                pMsg->Header.display();
                static int i = 1;
                ACE_DEBUG((LM_DEBUG, "(%P|%t)receive response success.%d\n", i++));
            }
        }
        else
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>(OTHER)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pMsg->Header.nSendProc, pMsg->Header.nRecvProc, pMsg->Header.nCmdMsg));
            MyProtoMsg *pInMsg = pMsg;
            MyProtoMsg *pOutMsg = pMsg;
            if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE) //如果别人的请求
            {
                process(pMsg->Header.nCmdMsg, pInMsg, pOutMsg);
                //处理完以后，会产生一个消息响应，发送到网络
                m_pMsgServer->push(pOutMsg);
            }
        }

        //ÊÍ·Åblock
        pMsgBlock->release();
        pMsgBlock = NULL;
    }
    return 0;
}


/*ACE_THR_FUNC Work(void *arg)
{
     ACE_DEBUG((LM_DEBUG, "(%P|%t)Work>>\n"));
     return 0;
}*/

int MyMsgServerTask::CreateDynamicTask(MrbMsgClient *pMrbMsgClient)
{
    ACE_Thread_Manager::instance()->spawn_n(m_nThreadNum, (ACE_THR_FUNC)MyMsgServerTask::DynamicTask, pMrbMsgClient);
    return 0;
}

ACE_THR_FUNC MyMsgServerTask::DynamicTask(void* arg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServerTask::DynamicTask>>\n"));
    MrbMsgClient *pMrbMsgClient = (MrbMsgClient*)arg;
    
    //Json::Value InParam;
   // InParam["test"] = "test";

    //Json::Value OutParam;
    //pMrbMsgClient->CallMethod(1, InParam, OutParam);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::DynamicTask>>CallMethod\n"));
    //delete pMrbMsgClient;
}


void MyMsgServerTask::process(int nCmdMsg, Json::Value InBody, Json::Value OutBody)
{

}

void MyMsgServerTask::SendMsgToTask(MyProtoMsg *pMsg)
{
    int nLength = pMsg->Header.nMsgLength;
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pMsg, nLength);
    if (!msg_queue_->is_full())
    {
        this->putq(mb);
    }
    else
    {
        mb->release();
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToQueue>>msg_queue is full!\n"));
    }
}