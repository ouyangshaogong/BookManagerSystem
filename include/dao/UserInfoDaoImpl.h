#ifndef __USER_INFO_DAO_IMPL__
#define __USER_INFO_DAO_IMPL__

#include "UserInfoDao.h"


class UserInfoDaoImpl: public UserInfoDao
{
public:
    virtual int AddUser(TblUserInfo &userInfo) throw (SQLException);
    virtual int DeleteUserByUserID(const string &fieldName, const string &fieldValue) throw (SQLException);
    virtual int DeleteAllUser() throw (SQLException);
    virtual int UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException);
    virtual int QueryUserByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException);
};

#endif