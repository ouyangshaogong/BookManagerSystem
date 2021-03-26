#ifndef __MAP_MSG_SERVICE__
#define __MAP_MSG_SERVICE__

#include <ace/OS.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Log_Msg.h"

#include "iMapCmdMsg.h"

class iMapMsgService : public ACE_Event_Handler
{
public:
    ACE_SOCK_Stream &peer(void);

    int open(void);

    virtual ACE_HANDLE get_handle(void) const;

    virtual int handle_input(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

protected:
    
    ACE_SOCK_Stream m_sockStream;
};

class iMapMsgAcceptor : public ACE_Event_Handler
{
public:
    virtual ~iMapMsgAcceptor() { this->handle_close(ACE_INVALID_HANDLE, 0); }

    int open(const ACE_INET_Addr &listen_addr)
    {
        if (this->m_acceptor.open(listen_addr, 1) == -1)
        {
            ACE_OS::printf("open port fail");
            return -1;
        }
        //注册接受连接回调事件
        return this->reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
    }

    virtual ACE_HANDLE get_handle(void) const
    {
        return this->m_acceptor.get_handle();
    }

    virtual int handle_input(ACE_HANDLE fd)
    {
        iMapMsgService *client = new iMapMsgService();
        //auto_ptr<iMapMsgService> p(client);

        if (this->m_acceptor.accept(client->peer()) == -1)
        {
            ACE_OS::printf("accept client fail");
            return -1;
        }

        //p.release();
        client->reactor(this->reactor());
        if (client->open() == -1)
        {
            client->handle_close(ACE_INVALID_HANDLE, 0);
        }
            
        return 0;
    }

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
    {
        if (this->m_acceptor.get_handle() != ACE_INVALID_HANDLE)
        {
            ACE_Reactor_Mask m = ACE_Event_Handler::ACCEPT_MASK |
                ACE_Event_Handler::DONT_CALL;
            this->reactor()->remove_handler(this, m);
            this->m_acceptor.close();
        }
        return 0;
    }

protected:
    ACE_SOCK_Acceptor m_acceptor;
};

#endif
