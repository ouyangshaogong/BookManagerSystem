#ifndef __USER_MANAGER_SERVICE__
#define __USER_MANAGER_SERVICE__

#include "UserInfoDaoImpl.h"
#include <pthread.h>

class UserManagerService
{

public:
    static UserManagerService* Instance();
    void DestoryInstance();

    int AddUser(TblUserInfo &bookInfo);
    int DeleteUserByUserID(const string &strUserID);
    int DeleteAllUser();

    //not update user_id and reader_id
    int UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond);

    //query condition just name and sex
    int QueryUserByField(const FieldCond &fieldCond, list<TblUserInfo> &listBookInfo);

    virtual ~UserManagerService();
private:
    UserManagerService();

private:
    static UserManagerService* m_instance;
    static pthread_mutex_t m_Mutex;
    UserInfoDaoImpl* m_pUserInfoImpl;
};

#endif //__USER_MANAGER_SERVICE__