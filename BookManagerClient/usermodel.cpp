#include "usermodel.h"

UserModel::UserModel(int nUserID,
                     int nReaderID,
                     string strPhone,
                     string strName,
                     string strSex,
                     string strBirth,
                     string strAddress,
                     int nUserType)
{
    m_nUserID = nUserID;
    m_nReaderID = nReaderID;
    m_strPhone = strPhone;
    m_strName = strName;
    m_strSex = strSex;
    m_strBirth = strBirth;
    m_strAddress = strAddress;
    m_nUserType = nUserType;
}
void UserModel::SetUserID(int nUserID)
{
    m_nUserID = nUserID;
}

int UserModel::GetUserID()
{
    return m_nUserID;
}

void UserModel::SetReaderID(int nReaderID)
{
    m_nReaderID = nReaderID;
}

int UserModel::GetReaderID()
{
    return m_nReaderID;
}

void UserModel::SetPhone(string strPhone)
{
    m_strPhone = strPhone;
}

string UserModel::GetPhone()
{
    return m_strPhone;
}

void UserModel::SetUserName(string strName)
{
    m_strName = strName;
}

string UserModel::GetUserName()
{
    return m_strName;
}

void UserModel::SetAddress(string strAddress)
{
    m_strAddress = strAddress;
}

string UserModel::GetAddress()
{
    return m_strAddress;
}

void UserModel::SetSex(string strSex)
{
    m_strSex = strSex;
}

string UserModel::GetSex()
{
    return m_strSex;
}

void UserModel::SetUserType(int nUserType)
{
    m_nUserType = nUserType;
}

int UserModel::GetUserType()
{
    return m_nUserType;
}


void UserModel::SetBirth(string strBirth)
{
    m_strBirth = strBirth;
}

string UserModel::GetBirth()
{
    return m_strBirth;
}
