#include "TableReaderCard.h"

void TableReaderCard::SetReaderID(int nReaderID)
{
    m_nReaderID = nReaderID;
}

int TableReaderCard::GetReaderID()
{
    return m_nReaderID;
}

void TableReaderCard::SetUserName(string strUserName)
{
    m_strUserName = strUserName;
}

string TableReaderCard::GetUserName()
{
    return m_strUserName;
}

void TableReaderCard::SetPasswd(string strPasswd)
{
    m_strPasswd = strPasswd;
}

string TableReaderCard::GetPasswd()
{
    return m_strPasswd;
}

