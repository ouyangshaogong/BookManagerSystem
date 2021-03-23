#include "lendlistmodel.h"

LendListModel::LendListModel()
{

}

void LendListModel::SetSerNum(int nSerNum)
{
    m_nSerNum = nSerNum;
}

int LendListModel::GetSerNum()
{
    return m_nSerNum;
}

void LendListModel::SetUserID(int nUserID)
{
    m_nUserID = nUserID;
}

int LendListModel::GetUserID()
{
    return m_nUserID;
}

void LendListModel::SetBookID(int nBookID)
{
    m_nBookID = nBookID;
}

int LendListModel::GetBookID()
{
    return m_nBookID;
}

void LendListModel::SetLendDate(string strLendDate)
{
    m_strLendDate = strLendDate;
}

string LendListModel::GetLendDate()
{
    return m_strLendDate;
}

void LendListModel::SetBackDate(string strBackDate)
{
    m_strBackDate = strBackDate;
}

string LendListModel::GetBackDate()
{
    return m_strBackDate;
}

void LendListModel::SetLendState(int nLendState)
{
    m_nLendState = nLendState;
}

int LendListModel::GetLendState()
{
    return m_nLendState;
}
