#include "MsgClientTask.h"


MsgClientTask::MsgClientTask()
    :m_tCallMutex(), m_tCondMsg(m_tCallMutex), m_nMsgID(1)
{
}


MsgClientTask::~MsgClientTask()
{
}

void MsgClientTask::process(int nCmdMsg, Json::Value InBody, Json::Value OutBody)
{

}

void MsgClientTask::SendMsgToTask(MyProtoMsg *pMsg)
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

void MsgClientTask::SendSignal(MyProtoMsg *pMsg)
{
    m_pMsg = pMsg;
    m_tCallMutex.signal();
}

MyProtoMsg *MsgClientTask::WaitSignal()
{
    m_tCallMutex.wait();
    return m_pMsg;
}
