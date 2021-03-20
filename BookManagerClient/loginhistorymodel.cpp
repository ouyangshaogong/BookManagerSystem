#include "loginhistorymodel.h"

void LoginHistoryModel::SetAccount(string strAccount)
{
    m_strAccount = strAccount;
}

string LoginHistoryModel::GetAccount()
{
    return m_strAccount;
}

void LoginHistoryModel::SetIP(string strIP)
{
    m_strIP = strIP;
}

string LoginHistoryModel::GetIP()
{
    return m_strIP;
}

void LoginHistoryModel::SetPort(string strPort)
{
    m_strPort = strPort;
}

string LoginHistoryModel::GetPort()
{
    return m_strPort;
}

void LoginHistoryModel::SetBeginTime(string strBeginTime)
{
    m_strBeginTime = strBeginTime;
}

string LoginHistoryModel::GetBeginTime()
{
    return m_strBeginTime;
}

void LoginHistoryModel::SetEndTime(string strEndTime)
{
    m_strEndTime = strEndTime;
}

string LoginHistoryModel::GetEndTime()
{
    return m_strEndTime;
}

void LoginHistoryModel::SetContinueTime(string strContinueTime)
{
    m_strContinueTime = strContinueTime;
}

string LoginHistoryModel::GetContinueTime()
{
    return m_strContinueTime;
}

