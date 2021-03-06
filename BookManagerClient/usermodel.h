#ifndef __DATA_MODEL__
#define __DATA_MODEL__

#include "common.h"

#define USER_ATTR_USERNAME 0
#define USER_ATTR_SEX 1
#define USER_ATTR_BIRTH 2
#define USER_ATTR_ADDRESS 3
#define USER_ATTR_PHONE 4

class UserModel
{
public:
    UserModel(){}

    void SetUserID(int nUserID);
    int GetUserID();

    void SetReaderID(int nReaderID);
    int GetReaderID();

    void SetPhone(string strPhone);
    string GetPhone();

    void SetUserName(string strName);
    string GetUserName();

    void SetSex(string strName);
    string GetSex();

    void SetAddress(string strName);
    string GetAddress();

    void SetBirth(string strName);
    string GetBirth();

    void SetUserType(int nUserType);
    int GetUserType();

    bool operator < (const UserModel& userData) const
    {
        return this->m_nUserID < userData.m_nUserID;
    }

private:
    int m_nUserID;
    int m_nReaderID;
    string m_strPhone;
    string m_strName;
    string m_strSex;
    string m_strBirth;
    string m_strAddress;
    int m_nUserType;
};

#endif
