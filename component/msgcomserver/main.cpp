
#include "iMapMsgService.h"

int main()
{
    ACE_INET_Addr addr(5000, "127.0.0.1");
    iMapMsgAcceptor server;
    server.reactor(ACE_Reactor::instance());
    server.open(addr);

    while (true)
    {
        ACE_Reactor::instance()->handle_events();
    }

    return 0;
}