#ifndef __DATA_MODEL__
#define __DATA_MODEL__

#include "common.h"

class UserModel
{
public:
    UserModel(int nUserID,
    int nReaderID,
    string strPhone,
    string strName,
    string strSex,
    string strBirth,
    string strAddress,
    int nUserType);

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
