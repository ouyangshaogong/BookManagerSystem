#include "iMapMsgHandle.h"


iMapMsgHandle *iMapMsgHandle::m_instance = NULL;
ACE_Thread_Mutex iMapMsgHandle::m_mutex;

#define MAX_HIGHT_WATER 10000

iMapMsgHandle::iMapMsgHandle():m_bRunning(true)
{
}

iMapMsgHandle::~iMapMsgHandle()
{
    if (NULL != m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

iMapMsgHandle* iMapMsgHandle::Instance()
{
    if (NULL == m_instance)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
        if (NULL == m_instance)
        {
            m_instance = new iMapMsgHandle();
        }
    }

    return m_instance;
}

int iMapMsgHandle::open(iMapConnectorHandle *pConnectorHandle)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::open>>\n"));
    m_pConnectorHandle = pConnectorHandle;
    //启动线程
    activate();
    //设置消息队列的最大索引
    msg_queue_->high_water_mark(MAX_HIGHT_WATER);
    return 0;
}



int iMapMsgHandle::close(u_long)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::close\n"));
    return 0;
}



int iMapMsgHandle::svc(void)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>begin\n"));

    //ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
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
            m_bRunning = false;
            break;
        }

        iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)pMsgBlock->base();
        int nLength = pMsgBlock->length();
        if (pCmdMsg->GetSendProc() == SEND_PROC_ID) //如果是我自己的进程
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>(MY)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pCmdMsg->GetSendProc(), pCmdMsg->GetRecvProc(), pCmdMsg->GetMrbCmdMsg()));
            if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE) //如果是我自己的请求
            {
                SendCmdMsgToServer(pCmdMsg);
            }
            else if (pCmdMsg->GetMsgType() == RESPONSE_MSG_TYPE) //别人对我的响应
            {
                pCmdMsg->display("display");
            }
        }
        else
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>(OTHER)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pCmdMsg->GetSendProc(), pCmdMsg->GetRecvProc(), pCmdMsg->GetMrbCmdMsg()));
            iMapCmdMsg *pInCmdMsg = pCmdMsg;
            iMapCmdMsg *pOutCmdMsg = pCmdMsg;
            if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE) //如果别人的请求
            {
                process(pInCmdMsg, pOutCmdMsg);
                //处理完以后，会产生一个消息响应，发送到网络
                SendCmdMsgToServer(pOutCmdMsg);
            }
        }

        //释放block
        pMsgBlock->release();
        pMsgBlock = NULL;

    }

    return 0;
}


void iMapMsgHandle::process(iMapCmdMsg *pInCmdMsg, iMapCmdMsg *pOutCmdMsg)
{
    string strOutParam;
    //service->process(pInCmdMsg->GetMrbCmdMsg(), pInCmdMsg->GetBody(), strOutParam);
    //设置一系列出参
    pOutCmdMsg->SetMsgType(RESPONSE_MSG_TYPE);
}

void iMapMsgHandle::SendCmdMsgToServer(iMapCmdMsg *pCmdMsg)
{
    m_pConnectorHandle->SendCmdMsgToServer(pCmdMsg);
}

void iMapMsgHandle::SendCmdMsgToQueue(iMapCmdMsg *pCmdMsg)
{
    int nLength = pCmdMsg->GetMsgLength();
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pCmdMsg, nLength);
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
