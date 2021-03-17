#include "dataproxy.h"
#include "datacommonfunc.h"

void DataProxy::AddLevel(int nLevel)
{
    int level = 0;
    level += nLevel;
    NotifyMsg notifyRet;
    notifyRet.nMsg = MSG_ADDLEVEL;
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyRet);
}

int DataProxy::AddUser(UserModel userModel)
{
    int nRet = 0;

    qDebug() << userModel.GetUserName().c_str();
    qDebug() << userModel.GetSex().c_str();
    qDebug() << userModel.GetBirth().c_str();
    qDebug() << userModel.GetAddress().c_str();
    qDebug() << userModel.GetPhone().c_str();
    qDebug() << QString::number(userModel.GetUserType());

    return nRet;
}

int DataProxy::DeleteUser(int userid)
{
    int nRet = 0;
    qDebug() << "DataProxy::DeleteUser" << QString::number(userid);
    return nRet;
}

int DataProxy::ModifyUser(int userid, string address)
{
    int nRet = 0;
    qDebug() << "DataProxy::ModifyUser" << QString::number(userid);
    qDebug() << "DataProxy::ModifyUser" << address.c_str();

    return nRet;
}

int DataProxy::QueryUser(string strAuther)
{
    int nRet = 0;
    qDebug() << "DataProxy::QueryUser" << strAuther.c_str();
    return nRet;
}

void DataProxy::AddBook()
{
    string str("AddBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::DeleteBook()
{
    string str("DeleteBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::ModifyBook()
{
    string str("ModifyBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

void DataProxy::QueryBook()
{
    string str("QueryBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(notify);
}

