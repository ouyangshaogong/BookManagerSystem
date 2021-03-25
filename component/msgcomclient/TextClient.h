#ifndef __TEST_CLIENT__
#define __TEST_CLIENT__

#include "ace/Thread.h"
#include "ace/Synch.h"
#include "ace/Log_Msg.h"

class TestClient
{
public:
    TestClient();
    void work(void *arg);
};

#endif
