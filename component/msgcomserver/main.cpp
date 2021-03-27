
#include "iMapMsgService.h"

int main()
{
    ACE_INET_Addr addr(5000, "127.0.0.1");
    iMapMsgAcceptor server;
    
    if (server.open(addr) == -1)
    {
        return -1;
    }

    ACE_Reactor::instance()->run_reactor_event_loop();

    return 0;
}