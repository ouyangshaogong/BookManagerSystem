#include "dataproxy.h"
#include "datacommonfunc.h"


void DataProxy::AddLevel(int nLevel)
{
    int level = 0;
    level += nLevel;
    NotifyMsg notifyRet;
    notifyRet.nMsg = MSG_ADDLEVEL;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notifyRet);
}

void DataProxy::AddUser(UserModel userModel)
{
    string str = userModel.GetUserName();
    NotifyMsg notifyRet;
    notifyRet.nMsg = MSG_ADDUSER;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notifyRet);
}

void DataProxy::DeleteUser()
{
    string str("DeleteUser");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::ModifyUser()
{
    string str("ModifyUser");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::QueryUser()
{
    string str("QueryUser");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::AddBook()
{
    string str("AddBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::DeleteBook()
{
    string str("DeleteBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::ModifyBook()
{
    string str("ModifyBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

void DataProxy::QueryBook()
{
    string str("QueryBook");
    NotifyMsg notify;
    DataCommonFunc::Instance()->SendNotifyCationToView(&notify);
}

