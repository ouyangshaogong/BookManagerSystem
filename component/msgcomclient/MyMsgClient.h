#ifndef __MRB_MSG_CLIENT__
#define __MRB_MSG_CLIENT__

#include "MyProtoMsg.h"
#include "commonace.h"
#include "MyMsgQueue.h"

class MyClientSockHandle
{
public:
    MyClientSockHandle ();
    
    ~MyClientSockHandle();

    int connect_to_server()
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) Starting connect to %s:%d\n", m_remoteAddr.get_host_name(), m_remoteAddr.get_port_number()));
        if (m_connector.connect (m_clientStream, m_remoteAddr) == -1)
        {
            ACE_DEBUG((LM_DEBUG,"(%P|%t) connection failed\n"));
        }
        else
        {
            ACE_DEBUG((LM_DEBUG,"(%P|%t) connected to %s\n", m_remoteAddr.get_host_name ()));
        }
        
        return 0;
    }

    int send_to_server(uint8_t *pData, uint32_t nLength, MyProtoMsg *pMsg, MyMsgQueue *pMsgQueue, uint8_t *buf, uint32_t max_length)
    {
        while (true)
        {
            int send_cnt = m_clientStream.send_n(pData, nLength);
            if (send_cnt < 0)
            {
                ACE_DEBUG((LM_DEBUG,"(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
                return -1;
            }

            if (send_cnt == 0)
            {
                ACE_DEBUG((LM_DEBUG,"(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
                m_clientStream.close();
                return 0;
            }

            if ((send_cnt > 0) && (send_cnt == nLength))
            {
                ACE_DEBUG((LM_DEBUG,"(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
                break;
            }
        }
        
        while(true)
        {
            ACE_Time_Value timeout(5);
            int recv_cnt = m_clientStream.recv(buf, max_length, &timeout);
            if (recv_cnt < 0)
            {
                ACE_DEBUG((LM_DEBUG,"(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
                return -1;
            }

            if (recv_cnt == 0)
            {
                ACE_DEBUG((LM_DEBUG,"(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
                m_clientStream.close();
                return 0;
            }

            MyProtoMsg *pMsg = NULL;
            while(!pMsgQueue->empty())
            {
                pMsg = pMsgQueue->front();
                pMsg->Header.display();
                pMsgQueue->pop();
                ACE_DEBUG((LM_DEBUG,"(%P|%t) recv_n success.recv_cnt:%d, errno:%d\n", recv_cnt, errno));
                return 0;
            }
        }
        

        
    }

    int close()
    {
        if (m_clientStream.close () == -1)
        {
            ACE_DEBUG((LM_ERROR,"(%P|%t) close\n"));
        }
        else
        {
            return 0;
        }
    }

private:
    ACE_SOCK_Stream m_clientStream;
    ACE_INET_Addr m_remoteAddr;
    ACE_SOCK_Connector m_connector;
    

};


class MyMsgClient
{
public:
    MyMsgClient();
    ~MyMsgClient();

    void SetMsgValue(int nSendProc, int nTaskMgrID, int nTaskID);

    int CallMethod(int nCmdMsg, const Json::Value &parameter, Json::Value& result);
    Json::Value& CallMethod(int nCmdMsg, const Json::Value &parameter);

private:
    int m_nMsgID;
    MyProtoMsg m_protoMsg;
    MyMsgQueue m_msgQueue;
    MyClientSockHandle m_sockHandle;
};

#endif
