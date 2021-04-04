#include "MyClientHandle.h"

MyClientHandle::MyClientHandle(int nPort, string strIP)
    :m_remoteAddr(nPort, strIP.c_str())
{

}

MyClientHandle::~MyClientHandle()
{

}


int MyClientHandle::ConnectToServer()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t) Starting connect to %s:%d\n", m_remoteAddr.get_host_name(), m_remoteAddr.get_port_number()));
    if (m_connector.connect(m_clientStream, m_remoteAddr) == -1)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) connection failed\n"));
        return -1;
    }
    else
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) connected to %s\n", m_remoteAddr.get_host_name()));
    }

    return 0;
}

int MyClientHandle::SendToServer(uint8_t *pData, uint32_t nLength)
{
    int send_cnt = m_clientStream.send_n(pData, nLength);
    if (send_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        return -1;
    }

    if (send_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        m_clientStream.close();
        return 0;
    }

    if (send_cnt > 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        return send_cnt;
    }

}

int MyClientHandle::RecvFromServer(uint8_t *buf, uint32_t max_length)
{
    int recv_cnt = m_clientStream.recv_n(buf, max_length);
    if (recv_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return -1;
    }

    if (recv_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        m_clientStream.close();
        return 0;
    }

    if (recv_cnt > 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return recv_cnt;
    }
}


int MyClientHandle::Close()
{
    if (m_clientStream.close() == -1)
    {
        ACE_DEBUG((LM_ERROR, "(%P|%t) close\n"));
    }
    else
    {
        return 0;
    }
}
