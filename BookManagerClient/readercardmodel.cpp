#include "readercardmodel.h"

ReaderCardModel::ReaderCardModel()
{

}


void ReaderCardModel::SetReaderID(int nReaderID)
{
    m_nReaderID = nReaderID;
}

int ReaderCardModel::GetReaderID()
{
    return m_nReaderID;
}

void ReaderCardModel::SetAccount(string strAccount)
{
    m_strAccount = strAccount;
}

string ReaderCardModel::GetAccount()
{
    return m_strAccount;
}


void ReaderCardModel::SetPasswd(string strPasswd)
{
    m_strPasswd = strPasswd;
}

string ReaderCardModel::GetPasswd()
{
    return m_strPasswd;
}

void ReaderCardModel::SetMoney(int nMoney)
{
    m_nMoney = nMoney;
}

int ReaderCardModel::GetMoney()
{
    return m_nMoney;
}

void ReaderCardModel::SetCardType(int nCardType)
{
    m_nCardType = nCardType;
}

int ReaderCardModel::GetCardType()
{
    return m_nCardType;
}
