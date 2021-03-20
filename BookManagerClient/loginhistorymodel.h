#ifndef LOGINHISTORYMODEL_H
#define LOGINHISTORYMODEL_H

#include "common.h"

class LoginHistoryModel
{
public:
    LoginHistoryModel(){};

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

    void SetContinueTime(string strContinueTime);
    string GetContinueTime();

private:
    string m_strAccount;
    string m_strIP;
    string m_strPort;
    string m_strBeginTime;
    string m_strEndTime;
    string m_strContinueTime;
};

#endif // LOGINHISTORYMODEL_H
