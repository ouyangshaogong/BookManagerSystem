#include "IDMaker.h"

#define MAX_ID 4294967290

IDMaker::IDMaker(int nID)
{
    m_nID = nID;
    m_Mutex = PTHREAD_MUTEX_INITIALIZER;
}

int IDMaker::GenerateID()
{
    pthread_mutex_lock(&m_Mutex);    // 加锁
    
    ++m_nID;
    if (m_nID == MAX_ID)
    {
        m_nID = 1;
    }

    pthread_mutex_unlock(&m_Mutex);  // 解锁

    return m_nID;
}