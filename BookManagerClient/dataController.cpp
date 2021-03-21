#include "datacontroller.h"
#include "dataproxy.h"
#include "datacommonfunc.h"
#include "usermodel.h"
#include <QtDebug>
#include <QString>

PACKAGEPARAMETER(Controller)
PARSEPARAMETER(Controller)

void DataController::handleEvent(NotifyMsg notifyIn)
{
    qDebug() << "DataController::handleEvent>>BEGIN>>notifyIn.nMsg:" << notifyIn.nMsg << "notifyIn>>size:" << QString::number(notifyIn.GetMapParam().size());

    DataProxy *dataProxy = (DataProxy*)DataCommonFunc::Instance()->RetrieveProxy(notifyIn.strClassName);

    NotifyMsg notifyOut;
    switch(notifyIn.nMsg)
    {
        case MSG_ADDLEVEL:
            dataProxy->AddLevel(50);
            break;
        case MSG_ADDUSER:
        {
            UserModel userModel;
            ParseParamController(notifyIn.GetMapParam(), userModel);
            int nRet = dataProxy->AddUser(userModel);
            notifyOut.nMsg = MSG_ADDUSER;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
        case MSG_DELETEUSER:
        {
            int userid = 0;
            ParseParamController(notifyIn.GetMapParam(), userid);
            int nRet = dataProxy->DeleteUserByUserID(userid);
            notifyOut.nMsg = MSG_DELETEUSER;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
        case MSG_MODIFYUSER:
        {
            int userid = 0;
            string address;
            ParseParamController(notifyIn.GetMapParam(), userid, address);
            int nRet = dataProxy->ModifyUser(userid, address);
            notifyOut.nMsg = MSG_MODIFYUSER;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
        case MSG_MODIFYPASSWD:
        {
            QString strOldPasswd;
            QString strNewPasswd;
            QString strRepeatPasswd;
            ParseParamController(notifyIn.GetMapParam(), strOldPasswd, strNewPasswd, strRepeatPasswd);
            int nRet = dataProxy->ModifyPasswd(strOldPasswd.toUtf8().data(), strNewPasswd.toUtf8().data(), strRepeatPasswd.toUtf8().data());
            notifyOut.nMsg = MSG_MODIFYPASSWD;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
        case MSG_QUERYALLUSER:
        {
            set<UserModel> setUserData;
            int nRet = dataProxy->QueryAllUser(setUserData);
            notifyOut.nMsg = MSG_QUERYALLUSER;
            PackageParamController(notifyOut.GetMapParam(), setUserData, nRet);
            break;
        }
        case MSG_ADDUSERTYPE:
        {
            int userType = 0;
            QString strText;
            ParseParamController(notifyIn.GetMapParam(), userType, strText);
            int nRet = dataProxy->AddUserType(userType, strText.toUtf8().data());
            notifyOut.nMsg = MSG_ADDUSERTYPE;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
        case MSG_LOGINHISTORY:
        {
            set<LoginHistoryModel> setLoginHistory;
            int nRet = dataProxy->QueryLoginHistory(setLoginHistory);
            notifyOut.nMsg = MSG_LOGINHISTORY;
            PackageParamController(notifyOut.GetMapParam(), setLoginHistory, nRet);
            break;
        }
        case MSG_DELETELOGINHISTORY:
        {
            QString strAccount;
            ParseParamController(notifyIn.GetMapParam(), strAccount);
            int nRet = dataProxy->DeleteLoginHistory(strAccount.toUtf8().data());
            notifyOut.nMsg = MSG_DELETELOGINHISTORY;
            PackageParamController(notifyOut.GetMapParam(), nRet);
            break;
        }
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
        case MSG_QUERYALLBOOK:
        {
            set<BookModel> setBookData;
            int nRet = dataProxy->QueryAllBook(setBookData);
            notifyOut.nMsg = MSG_QUERYALLBOOK;
            PackageParamController(notifyOut.GetMapParam(), setBookData, nRet);
            break;
        }
        default:
            break;
    }

    qDebug() << "DataController::handleEvent>>END>>notifyOut.nMsg:" << notifyOut.nMsg << "notifyOut>>size:" << QString::number(notifyOut.GetMapParam().size());
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyOut);
}
