#include "TableLendList.h"

void TableLendList::SetSerNum(int nSerNum)
{
    m_nSerNum = nSerNum;
}

int TableLendList::GetSerNum()
{
    return m_nSerNum;
}

void TableLendList::SetUserID(int nUserID)
{
    m_nUserID = nUserID;
}

int TableLendList::GetUserID()
{
    return m_nUserID;
}

void TableLendList::SetBookID(int nBookID)
{
    m_nBookID = nBookID;
}

int TableLendList::GetBookID()
{
    return m_nBookID;
}

void TableLendList::SetLendDate(string strLendDate)
{
    m_strLendDate = strLendDate;
}

string TableLendList::GetLendDate()
{
    return m_strLendDate;
}

void TableLendList::SetBackDate(string strBackDate)
{
    m_strBackDate = strBackDate;
}

string TableLendList::GetBackDate()
{
    return m_strBackDate;
}

void TableLendList::SetLendState(bool bLendState)
{
    m_bLendState = bLendState;
}

bool TableLendList::GetLendState()
{
    return m_bLendState;
}