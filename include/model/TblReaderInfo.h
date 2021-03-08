#ifndef __TABLE_READER_INFO__
#define __TABLE_READER_INFO__

#include "common.h"

class TblReaderInfo
{

public:
    void SetUserID(int nUserID);
    int GetUserID();

    void SetReaderID(int nReaderID);
    int GetReaderID();

    void SetPhone(string strPhone);
    string GetPhone();

    void SetReaderName(string strName);
    string GetReaderName();

    void SetSex(string strName);
    string GetSex();

    void SetAddress(string strName);
    string GetAddress();

    void SetUserType(int nUserType);
    int GetUserType();

private:
    int m_nUserID;
    int m_nReaderID;
    string m_strPhone;
    string m_strName;
    string m_strSex;
    string m_strAddress;
    int m_nUserType;
};

#endif