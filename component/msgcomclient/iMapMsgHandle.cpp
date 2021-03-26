#include "iMapMsgHandle.h"


iMapMsgHandle *iMapMsgHandle::m_instance = NULL;
ACE_Thread_Mutex iMapMsgHandle::m_mutex;

extern ACE_Thread_Mutex g_mqMutex;
extern iMapMsgQueue g_MQ;

iMapMsgHandle::iMapMsgHandle()
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

int iMapMsgHandle::open()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::open>>\n"));
    m_connectorHandle.open();
    activate();

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
    ACE_Message_Block *mb = 0;
    while (this->getq(mb) != -1)
    {
        if (mb->msg_type() == ACE_Message_Block::MB_HANGUP)
        {
            mb->release();
            break;
        }

        iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)mb->base();
        int nlength = mb->length();
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>nlength:%d, MsgType:%d, MsgID:%d\n", nlength, pCmdMsg->GetMsgType(), pCmdMsg->GetMsgID()));

        delete pCmdMsg;
        pCmdMsg = NULL;

        mb->release();
    }

    return 0;
}


ACE_THR_FUNC_RETURN iMapMsgHandle::StartMsgLoop()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::StartMsgLoop>>begin\n"));
    while (m_bRunning)
    {
        ACE_Guard<ACE_Thread_Mutex> guard(g_mqMutex);
        ACE_Message_Block* pMsgBlock = NULL;
        if (-1 == g_MQ.dequeue(pMsgBlock))
        {
            continue;
        }

        if (NULL == pMsgBlock)
        {
            continue;
        }

        iMapCmdMsg *pCmdMsg = (iMapCmdMsg*)pMsgBlock->base();
        cout << "iMapMsgHandle::StartMsgLoop>>pCmdMsg:" << pCmdMsg << endl;
        int nLength = pMsgBlock->length();
        if (pCmdMsg->GetMsgType() == REQUEST_MSG_TYPE)
        {
            SendExternalCmdMsg(pCmdMsg);
        }
        else if (pCmdMsg->GetMsgType() == RESPONSE_MSG_TYPE)
        {
            SendInternalCmdMsg(pCmdMsg);
        }
        else if (pCmdMsg->GetMsgType() == END_MSG_TYPE)
        {
            m_bRunning = false;
        }
        else
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::StartMsgLoop>>MsgType Is Error!\n"));
        }

        //ÊÍ·Åblock
        delete pMsgBlock;
        pMsgBlock = NULL;

        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::StartMsgLoop>>message_bytes:%d\n", g_MQ.message_bytes()));
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::StartMsgLoop>>message_length:%d\n", g_MQ.message_length()));

        ACE_OS::sleep(2);
    }

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::StartMsgLoop>>end\n"));
}

void iMapMsgHandle::SendExternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    m_connectorHandle.SendExternalCmdMsg(pCmdMsg);
}

void iMapMsgHandle::SendInternalCmdMsg(iMapCmdMsg *pCmdMsg)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendInternalCmdMsg>>begin\n"));
    int nLength = pCmdMsg->GetMsgHeaderLength() + pCmdMsg->GetBody().size();
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    this->putq(mb);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendInternalCmdMsg>>end\n"));
}
