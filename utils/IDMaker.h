#ifndef __ID_MAKER__
#define __ID_MAKER__

#include <pthread.h>

class IDMaker
{

public:
    IDMaker(int nID);
    ~IDMaker(){};

    void GetCurrentID(int nID);
    int GenerateID();

private:
    int m_nID;
    pthread_mutex_t m_Mutex;
};

#endif