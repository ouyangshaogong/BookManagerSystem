#ifndef READERCARDMODEL_H
#define READERCARDMODEL_H

#include "common.h"

class ReaderCardModel
{
public:
    ReaderCardModel();

    void SetReaderID(int nReaderID);
    int GetReaderID();

    void SetAccount(string strAccount);
    string GetAccount();

    void SetPasswd(string strPasswd);
    string GetPasswd();

    void SetMoney(int nMoney);
    int GetMoney();

    void SetCardType(int nCardType);
    int GetCardType();

private:
    int m_nReaderID;
    string m_strAccount;
    string m_strPasswd;
    int m_nMoney;
    int m_nCardType;
};

#endif // READERCARDMODEL_H
