#include "iMapMsgService.h"

int iMapMsgService::open(void)
{
    //注册读就绪回调函数
    return this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
}

ACE_SOCK_Stream& iMapMsgService::peer()
{
    return this->m_sockStream;
}

ACE_HANDLE iMapMsgService::get_handle(void) const
{ 
    return this->m_sockStream.get_handle();
}

int iMapMsgService::handle_input(ACE_HANDLE fd)
{
    while (true)
    {
        //定义一个消息
        iMapCmdMsg *pCmdMsg = new iMapCmdMsg;

        //从内核缓存区读取消息头
        char buf[2048] = { 0 };
        int revLength = peer().recv_n(buf, pCmdMsg->GetMsgHeaderLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>HeaderLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息头
        string strMsgHeader(buf, revLength);
        pCmdMsg->deserializeHeader(strMsgHeader);
        pCmdMsg->SetMsgType(RESPONSE_MSG_TYPE);

        //从内核缓存区读取消息体
        ACE_OS::memset(buf, 0, 2048);
        revLength = 0;
        revLength = peer().recv_n(buf, pCmdMsg->GetMsgBodyLength());
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>BodyLength:%d\n", revLength));
        if (revLength <= 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>recv fail!\n"));
            return -1;
        }

        //序列化消息体
        string strMsgBody(buf, revLength + 1);
        pCmdMsg->deserializeBody(strMsgBody);

        delete pCmdMsg;
        pCmdMsg = NULL;

        //原样发送回去
        string strMsg = strMsgHeader + strMsgBody;
        int nSend = peer().send_n(strMsg.c_str(), strMsg.size());
        if (nSend < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>send fail!\n"));
            return -1;
        }
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>nSend:%d\n", nSend));
    }

    

    ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::handle_input>>send success!\n"));

    return 0;
}

// 释放相应资源
int iMapMsgService::handle_close(ACE_HANDLE, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    mask = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, mask);
    this->m_sockStream.close();
    delete this;    //socket出错时，将自动删除该客户端，释放相应资源
    return 0;
}