#ifndef __USER_MANAGER_SERVICE__
#define __USER_MANAGER_SERVICE__

#include "UserManager.h"
#include "ReaderCardManager.h"
#include "LoginManager.h"
#include <pthread.h>
#include "IDMaker.h"
#include "CardUserNameMaker.h"


#define USERADMIN 0
#define USERREADER 1

class UserManagerService
{

public:
    static UserManagerService* Instance();
    void DestoryInstance();

    int AddUser(TblUserInfo &bookInfo);
    int DeleteUserByUserID(const int nUserID);
    int DeleteAllUser();

    //not update user_id and reader_id
    int UpdateUserInfoByUserID(const int nUserID, TblUserInfo &userInfo);

    //query condition just name and sex
    int QueryUserByUserID(const int &nUserID, TblUserInfo &bookInfo);

    //query condition just name and sex
    int QueryReaderCardByReaderID(const int nReaderID, TableReaderCard &readerCard);

    int UpdateUserPasswd(const string &strUserName, const string &strPasswd);

    int Login(const string &strUserName, const string &strPasswd);

    virtual ~UserManagerService();
private:
    UserManagerService();

private:
    static UserManagerService* m_instance;
    static pthread_mutex_t m_Mutex;
    UserManager* m_pUserMgr;
    ReaderCardManager *m_pReaderCard;
    LoginManager *m_pLoginMgr;

    IDMaker m_nUserMaker;
    IDMaker m_nReaderCardMaker;
    CardUserNameMaker m_strUserNameMaker;
};

#endif //__USER_MANAGER_SERVICE__