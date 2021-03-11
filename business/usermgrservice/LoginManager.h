#ifndef __LOGIN_MANAGE__
#define __LOGIN_MANAGE__

#include "UserInfoDaoImpl.h"
#include "ReaderCardDaoImpl.h"
#include <pthread.h>

class LoginManager
{

public:
    LoginManager();
    virtual ~LoginManager();
    
    int Login(const string &strUserName, const string &strPasswd);
    

private:
    //UserInfoDaoImpl* m_pUserInfoImpl;
    ReaderCardDaoImpl *m_pReaderCardImpl;
};

#endif //__LOGIN_MANAGE__