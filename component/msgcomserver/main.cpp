
#include "iMapMsgService.h"
#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"
#include "ace/Acceptor.h"

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)main>>server is start.....!\n"));
    //清除原来的标志，如果不清除在输出到文件到同时也会在console上输出。
    //ACE_LOG_MSG->clr_flags(ACE_Log_Msg::STDERR);
    //ACE_LOG_MSG->set_flags(ACE_Log_Msg::OSTREAM);
    //定义文件名，并设置文件句柄
    const char * filename = "iMapMsgService.log";
    ofstream out(filename, ios::out | ios::trunc);
    //ios::out以写的方式打开，ios::trunc清空文件;
    //ACE_LOG_MSG->msg_ostream(&out);

    ACE_INET_Addr addr(5000, "127.0.0.1");
    iMapMsgAcceptor acceptor;
    
    if (acceptor.open(addr, ACE_Reactor::instance()) == -1)
    {
        return 1;
    }

    ACE_Reactor::instance()->run_reactor_event_loop();

    //测试信息，这次能真正输出到文件。
    ACE_DEBUG((LM_DEBUG, "(%P|%t)main>>server is end.....!\n"));
    return 0;
}