#include "datacontroller.h"
#include "dataproxy.h"
#include "datacommonfunc.h"
#include "usermodel.h"


void DataController::handleEvent(NotifyMsg notify)
{
    DataProxy *dataProxy = (DataProxy*)DataCommonFunc::Instance()->RetrieveProxy(notify.strClassName);

    switch(notify.nMsg)
    {
        case MSG_ADDLEVEL:
            dataProxy->AddLevel(50);
            break;
        case MSG_ADDUSER:
        {
            UserModel *userModel = (UserModel*)notify.pCommonData;
            dataProxy->AddUser(*userModel);
            break;
        }
        case MSG_DELETEUSER:
            dataProxy->DeleteUser();
            break;
        case MSG_MODIFYUSER:
            dataProxy->ModifyUser();
            break;
        case MSG_QUERYUSER:
            dataProxy->QueryUser();
            break;
        case MSG_ADDBOOK:
            dataProxy->AddBook();
            break;
        case MSG_DELETEBOOK:
            dataProxy->DeleteBook();
            break;
        case MSG_MODIFYBOOK:
            dataProxy->ModifyBook();
            break;
        case MSG_QUERYBOOK:
            dataProxy->QueryBook();
            break;
        default:
            break;

    }




}
