#ifndef LOGINHISTORYMODEL_H
#define LOGINHISTORYMODEL_H

#include "common.h"

class LoginHistoryModel
{
public:
    LoginHistoryModel(){};

    void SetLoginID(int nLoginID);
    int GetLoginID();

    void SetAccount(string strAccount);
    string GetAccount();

    void SetIP(string strIP);
    string GetIP();

    void SetPort(string strPort);
    string GetPort();

    void SetBeginTime(string strBeginTime);
    string GetBeginTime();

    void SetEndTime(string strEndTime);
    string GetEndTime();

    void SetContinueTimeSec(string strContinueTimeSec);
    string GetContinueTimeSec();

    void SetContinueTimeMin(string strContinueTimeMin);
    string GetContinueTimeMin();

    void SetContinueTimeHour(string strContinueTimeHour);
    string GetContinueTimeHour();

    void SetContinueTimeDay(string strContinueTimeDay);
    string GetContinueTimeDay();

    void SetLoginType(int nLoginType);
    int GetLoginType();

    bool operator < (const LoginHistoryModel& loginHistory) const
    {
        return this->m_nLoginID < loginHistory.m_nLoginID;
    }

private:
    int m_nLoginID;
    string m_strAccount;
    string m_strIP;
    string m_strPort;
    string m_strBeginTime;
    string m_strEndTime;
    string m_strContinueTimeSec;
    string m_strContinueTimeMin;
    string m_strContinueTimeHour;
    string m_strContinueTimeDay;
    int m_nLoginType;
};

#endif // LOGINHISTORYMODEL_H
