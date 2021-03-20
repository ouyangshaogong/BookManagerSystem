#include "loginhistorymodel.h"

void LoginHistoryModel::SetLoginID(int nLoginID)
{
    m_nLoginID = nLoginID;
}

int LoginHistoryModel::GetLoginID()
{
    return m_nLoginID;
}

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

void LoginHistoryModel::SetContinueTimeSec(string strContinueTimeSec)
{
    m_strContinueTimeSec = strContinueTimeSec;
}

void LoginHistoryModel::SetContinueTimeMin(string strContinueTimeSecMin)
{
    m_strContinueTimeMin = strContinueTimeSecMin;
}

void LoginHistoryModel::SetContinueTimeDay(string strContinueTimeDay)
{
    m_strContinueTimeDay = strContinueTimeDay;
}

void LoginHistoryModel::SetContinueTimeHour(string strContinueTimeHour)
{
    m_strContinueTimeHour = strContinueTimeHour;
}

string LoginHistoryModel::GetContinueTimeSec()
{
    return m_strContinueTimeSec;
}

string LoginHistoryModel::GetContinueTimeMin()
{
    return m_strContinueTimeMin;
}

string LoginHistoryModel::GetContinueTimeHour()
{
    return m_strContinueTimeHour;
}

string LoginHistoryModel::GetContinueTimeDay()
{
    return m_strContinueTimeDay;
}

void LoginHistoryModel::SetLoginType(int nLoginType)
{
    m_nLoginType = nLoginType;
}

int LoginHistoryModel::GetLoginType()
{
    return m_nLoginType;
}
