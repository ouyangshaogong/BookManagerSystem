#include "MyMsgServerTask.h"



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
        
        if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>(REQUEST_MSG_TYPE)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pMsg->Header.nSendProc, pMsg->Header.nRecvProc, pMsg->Header.nCmdCode));
            MyProtoMsg *pInMsg = pMsg;
            MyProtoMsg *pOutMsg = pMsg;
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>pInMsg:%d, pOutMsg:%d, pMsg:%d\n", pInMsg, pOutMsg, pMsg));
            process(pMsg->Header.nCmdCode, pInMsg->Body, pOutMsg->Body);
            pOutMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
            //处理完以后，会产生一个消息响应，发送到网络
            m_pMsgServer->push(pOutMsg);
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

int MyMsgServerTask::CreateDynamicTask(MyMsgClient *pMrbMsgClient)
{
    ACE_Thread_Manager::instance()->spawn_n(m_nThreadNum, (ACE_THR_FUNC)MyMsgServerTask::DynamicTask, pMrbMsgClient);
    return 0;
}

ACE_THR_FUNC MyMsgServerTask::DynamicTask(void* arg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServerTask::DynamicTask>>\n"));
    MyMsgClient *pMrbMsgClient = (MyMsgClient*)arg;
    
    //Json::Value InParam;
   // InParam["test"] = "test";

    //Json::Value OutParam;
    //pMrbMsgClient->CallMethod(1, InParam, OutParam);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MsgClientTask::DynamicTask>>CallMethod\n"));
    //delete pMrbMsgClient;
}


void MyMsgServerTask::process(int nCmdMsg, Json::Value &InBody, Json::Value &OutBody)
{

}

void MyMsgServerTask::SendMsgToTask(MyProtoMsg *pMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgServerTask::SendMsgToTask>>\n"));
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