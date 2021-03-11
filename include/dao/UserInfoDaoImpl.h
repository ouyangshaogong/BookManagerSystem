#ifndef __USER_INFO_DAO_IMPL__
#define __USER_INFO_DAO_IMPL__

#include "UserInfoDao.h"
#include "TblUserInfo.h"
#include "SQLConnection.h"
#include "common.h"

class UserInfoDaoImpl: public UserInfoDao
{
public:

    UserInfoDaoImpl();
    virtual ~UserInfoDaoImpl(){}

    virtual int AddUser(TblUserInfo &userInfo) throw (SQLException);
    virtual int DeleteUserByUserID(const string &strUSerID) throw (SQLException);
    virtual int DeleteUserByField(const FieldCond &fieldCond) throw (SQLException);
    virtual int DeleteAllUser() throw (SQLException);
    virtual int UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException);
    virtual int QueryUserByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException);

private:
    MYSQL *m_pMySQLConn;

};

#endif