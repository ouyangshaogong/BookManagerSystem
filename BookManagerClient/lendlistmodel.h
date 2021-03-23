#ifndef LENDLISTMODEL_H
#define LENDLISTMODEL_H

#include "common.h"

#define LendPreContract 0
#define LendBorrow 1

class LendListModel
{
public:
    LendListModel();

    void SetSerNum(int nSerNum);
    int GetSerNum();

    void SetUserID(int nUserID);
    int GetUserID();

    void SetBookID(int nBookID);
    int GetBookID();

    void SetLendDate(string strLendDate);
    string GetLendDate();

    void SetBackDate(string strBackDate);
    string GetBackDate();

    void SetLendState(int nLendState);
    int GetLendState();

    bool operator < (const LendListModel& lendData) const
    {
        return this->m_nSerNum < lendData.m_nSerNum;
    }

private:
    int m_nSerNum;
    int m_nUserID;
    int m_nBookID;
    string m_strLendDate;
    string m_strBackDate;
    int m_nLendState;
};

#endif // LENDLISTMODEL_H
