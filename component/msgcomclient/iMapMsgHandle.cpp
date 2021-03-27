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
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>nLength:%d, MsgType:%d\n", nLength, pCmdMsg->GetMsgID()));
        if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE)
        {
            SendCmdMsgToServer(pCmdMsg);
        }
        else if (pCmdMsg->GetMsgType() == RESPONSE_MSG_TYPE)
        {
            SendCmdMsgToQueue(pCmdMsg);
        }
        else
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>MsgType Is Error!\n"));
        }

        //释放block
        pMsgBlock->release();
        pMsgBlock = NULL;

    }

    return 0;
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
