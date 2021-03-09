#ifndef __TABLE_READER_CARD__
#define __TABLE_READER_CARD__

#include "common.h"

class TableReaderCard
{

public:
    void SetReaderID(int nReaderID);
    int GetReaderID();

    void SetUserName(string strUserName);
    string GetUserName();

    void SetPasswd(string strPasswd);
    string GetPasswd();

private:
    int m_nReaderID;
    string m_strUserName;
    string m_strPasswd;
};

#endif