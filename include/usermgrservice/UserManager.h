#ifndef __USER_MANAGE__
#define __USER_MANAGE__

#include "UserInfoDaoImpl.h"
#include <pthread.h>

class UserManager
{

public:
    UserManager();
    virtual ~UserManager();
    
    int AddUser(TblUserInfo &bookInfo);
    int DeleteUserByUserID(const string &strUserID);
    int DeleteAllUser();

    //not update user_id and reader_id
    int UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond);
    int UpdateUserInfoByUserID(const int nUserID, TblUserInfo &userInfo);

    //query condition just name and sex
    int QueryUserByField(const FieldCond &fieldCond, list<TblUserInfo> &listBookInfo);
    int QueryUserByUserID(const string &strUSerID, TblUserInfo &userInfo);
    

private:
    UserInfoDaoImpl* m_pUserInfoImpl;
};

#endif //__USER_MANAGE__