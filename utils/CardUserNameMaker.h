#ifndef __CARD_USER_NAME_MAKER__
#define __CARD_USER_NAME_MAKER__

#include "common.h"
#include <pthread.h>

class CardUserNameMaker
{

public:
    CardUserNameMaker();
    ~CardUserNameMaker();

    string GenerateUserName();

private:
    int m_nUserName;
    pthread_mutex_t m_Mutex;
};

#endif