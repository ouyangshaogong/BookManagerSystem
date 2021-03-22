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
    qDebug() << "DataController::handleEvent>>BEGIN>>notifyIn.nMsg:" << notifyIn.nMsg << "notifyIn>>size:";

    DataProxy *dataProxy = (DataProxy*)DataCommonFunc::Instance()->RetrieveProxy(notifyIn.strClassName);

    NotifyMsg notifyOut;
    switch(notifyIn.nMsg)
    {
        case MSG_ADDUSER:
        {
            UserModel userModel;
            ParseParamController(notifyIn, userModel);
            int nRet = dataProxy->AddUser(userModel);
            notifyOut.nMsg = MSG_ADDUSER;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_DELETEUSER:
        {
            int userid = 0;
            ParseParamController(notifyIn, userid);
            int nRet = dataProxy->DeleteUserByUserID(userid);
            notifyOut.nMsg = MSG_DELETEUSER;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_MODIFYUSER:
        {
            int userid = 0;
            int nAttrType = 0;
            QString strText;
            ParseParamController(notifyIn, userid, nAttrType, strText);
            int nRet = dataProxy->ModifyUser(userid, nAttrType, strText.toUtf8().data());
            notifyOut.nMsg = MSG_MODIFYUSER;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_MODIFYPASSWD:
        {
            QString strOldPasswd;
            QString strNewPasswd;
            QString strRepeatPasswd;
            ParseParamController(notifyIn, strOldPasswd, strNewPasswd, strRepeatPasswd);
            int nRet = dataProxy->ModifyPasswd(strOldPasswd.toUtf8().data(), strNewPasswd.toUtf8().data(), strRepeatPasswd.toUtf8().data());
            notifyOut.nMsg = MSG_MODIFYPASSWD;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_QUERYALLUSER:
        {
            set<UserModel> setUserData;
            int nRet = dataProxy->QueryAllUser(setUserData);
            notifyOut.nMsg = MSG_QUERYALLUSER;
            PackageParamController(notifyOut, setUserData, nRet);
            break;
        }
        case MSG_ADDUSERTYPE:
        {
            int userType = 0;
            QString strText;
            ParseParamController(notifyIn, userType, strText);
            int nRet = dataProxy->AddUserType(userType, strText.toUtf8().data());
            notifyOut.nMsg = MSG_ADDUSERTYPE;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_LOGINHISTORY:
        {
            set<LoginHistoryModel> setLoginHistory;
            int nRet = dataProxy->QueryLoginHistory(setLoginHistory);
            notifyOut.nMsg = MSG_LOGINHISTORY;
            PackageParamController(notifyOut, setLoginHistory, nRet);
            break;
        }
        case MSG_DELETELOGINHISTORY:
        {
            QString strAccount;
            ParseParamController(notifyIn, strAccount);
            int nRet = dataProxy->DeleteLoginHistory(strAccount.toUtf8().data());
            notifyOut.nMsg = MSG_DELETELOGINHISTORY;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_ADDBOOK:
            dataProxy->AddBook();
            break;
        case MSG_DELETEBOOK:
            dataProxy->DeleteBook();
            break;
        case MSG_MODIFYBOOK:
        {
            int bookid = 0;
            int nAttrType = 0;
            int nAttr = 0;
            QString strText;
            int nRet = 0;
            bool *IsIntAttr = (bool*)notifyIn.pExtra;
            if (*IsIntAttr)
            {
                ParseParamController(notifyIn, bookid, nAttrType, nAttr);
                nRet = dataProxy->ModifyBook(bookid, nAttrType, nAttr);
            }
            else
            {
                ParseParamController(notifyIn, bookid, nAttrType, strText);
                nRet = dataProxy->ModifyBook(bookid, nAttrType, strText.toUtf8().data());
            }
            delete IsIntAttr;

            qDebug() << "MSG_MODIFYBOOK>>bookid:" << bookid << "nAttrType:" << nAttrType;
            notifyOut.nMsg = MSG_MODIFYBOOK;
            PackageParamController(notifyOut, nRet);
            break;
        }
        case MSG_QUERYBOOK:
            dataProxy->QueryBook();
            break;
        case MSG_QUERYALLBOOK:
        {
            set<BookModel> setBookData;
            int nRet = dataProxy->QueryAllBook(setBookData);
            notifyOut.nMsg = MSG_QUERYALLBOOK;
            PackageParamController(notifyOut, setBookData, nRet);
            break;
        }
        case MSG_LOGINSYSTEM:
        {
            string strAccount;
            string strPasswd;
            int nCardType = 0;
            ParseParamController(notifyIn, strAccount, strPasswd);
            int nRet = dataProxy->Login(strAccount, strPasswd, nCardType);
            notifyOut.nMsg = MSG_LOGINSYSTEM;
            PackageParamController(notifyOut, nCardType, nRet);
            break;
        }
        default:
            break;
    }

    qDebug() << "DataController::handleEvent>>END>>notifyOut.nMsg:" << notifyOut.nMsg;
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyOut);
}
