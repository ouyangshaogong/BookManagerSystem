#ifndef __USER_INFO_DAO__
#define __USER_INFO_DAO__

#include "TblUserInfo.h"
#include "SQLException.h"

class UserInfoDao
{

public:
    virtual int AddUser(TblUserInfo &userInfo) throw (SQLException) = 0;
    virtual int DeleteUserByUserID(const string &fieldName, const string &fieldValue) throw (SQLException) = 0;
    virtual int DeleteAllUser() throw (SQLException) = 0;
    virtual int UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException) = 0;
    virtual int QueryUserByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException) = 0;
};

#endif