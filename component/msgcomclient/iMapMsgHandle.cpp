#include "iMapMsgHandle.h"


iMapMsgHandle *iMapMsgHandle::m_instance = NULL;
ACE_Thread_Mutex iMapMsgHandle::m_mutex;

#define MAX_HIGHT_WATER 10000

iMapMsgHandle::iMapMsgHandle():m_bRunning(true)
{
    m_protoDecode.init();
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
    //�����߳�
    activate();
    //������Ϣ���е��������
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

        uint8_t *pData = (uint8_t*)pMsgBlock->base();
        int nLength = pMsgBlock->length();

        if (!m_protoDecode.parser(pData, nLength))
        {
            cout << "parser msg failed!" << endl;
        }
        else
        {
            cout << "parser msg successful!" << endl;
        }

        MyProtoMsg* pMsg = NULL;
        while (!m_protoDecode.empty())
        {
            pMsg = m_protoDecode.front();
            
            if (pMsg->Header.nSendProc == SEND_PROC_ID) //��������Լ��Ľ���
            {
                ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::svc>>(MY)nSendProcID:%d, nRecvProcID:%d, nMrbMsg:%d\n", pMsg->Header.nSendProc, pMsg->Header.nRecvProc, pMsg->Header.nCmdMsg));
                if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE) //��������Լ�������
                {
                    SendCmdMsgToServer(pMsg);
                }
                else if (pMsg->Header.nMsgType == RESPONSE_MSG_TYPE) //���˶��ҵ���Ӧ
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
                if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE) //������˵�����
                {
                    process(pInMsg, pOutMsg);
                    //�������Ժ󣬻����һ����Ϣ��Ӧ�����͵�����
                    SendCmdMsgToServer(pOutMsg);
                }
            }

            m_protoDecode.pop();
        }

        

        //�ͷ�block
        pMsgBlock->release();
        pMsgBlock = NULL;

    }

    return 0;
}


void iMapMsgHandle::process(MyProtoMsg *pInMsg, MyProtoMsg *pOutMsg)
{
    string strOutParam;
    //service->process(pInCmdMsg->GetMrbCmdMsg(), pInCmdMsg->GetBody(), strOutParam);
    //����һϵ�г���
    pOutMsg->Header.nMsgType = RESPONSE_MSG_TYPE;
}

void iMapMsgHandle::SendCmdMsgToServer(uint8_t* pData, int nLength)
{
    m_pConnectorHandle->SendCmdMsgToServer(pData, nLength);
}

void iMapMsgHandle::SendCmdMsgToServer(MyProtoMsg *pMsg)
{
    uint32_t nLength = 0;
    uint8_t* pData = NULL;
    pData = m_protoEncode.encode(pMsg, nLength);
    m_pConnectorHandle->SendCmdMsgToServer(pData, nLength);
}

void iMapMsgHandle::SendCmdMsgToQueue(uint8_t* pData, int nLength)
{
    ACE_Message_Block*  mb = new ACE_Message_Block(nLength, ACE_Message_Block::MB_DATA);
    mb->copy((char*)pData, nLength);
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
