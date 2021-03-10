#ifndef __TABLE_LEND_LIST__
#define __TABLE_LEND_LIST__

#include "common.h"

class TableLendList
{

public:
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

    void SetLendState(bool bLendState);
    bool GetLendState();

private:
    int m_nSerNum;
    int m_nUserID;
    int m_nBookID;
    string m_strLendDate;
    string m_strBackDate;
    bool m_bLendState;

};

#endif