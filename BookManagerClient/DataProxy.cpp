#include "DataProxy.h"
#include "datacommonfunc.h"


void DataProxy::AddLevel(int nLevel)
{
    int level = 0;
    level += nLevel;
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_ADDLEVEL, &level);
}

void DataProxy::AddUser()
{
    string str("AddUser");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_ADDUSER, &str);
}

void DataProxy::DeleteUser()
{
    string str("DeleteUser");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_DELETEUSER, &str);
}

void DataProxy::ModifyUser()
{
    string str("ModifyUser");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_MODIFYUSER, &str);
}

void DataProxy::QueryUser()
{
    string str("QueryUser");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_QUERYUSER, &str);
}

void DataProxy::AddBook()
{
    string str("AddBook");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_ADDBOOK, &str);
}

void DataProxy::DeleteBook()
{
    string str("DeleteBook");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_DELETEBOOK, &str);
}

void DataProxy::ModifyBook()
{
    string str("ModifyBook");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_MODIFYBOOK, &str);
}

void DataProxy::QueryBook()
{
    string str("QueryBook");
    DataCommonFunc::Instance()->SendNotifyCationToView(MSG_QUERYBOOK, &str);
}

