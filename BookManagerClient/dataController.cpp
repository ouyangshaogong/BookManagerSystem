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
    qDebug() << "DataController::handleEvent>>BEGIN>>notifyIn.nMsg:" << notifyIn.nMsg << "notifyIn>>size:" << QString::number(notifyIn.GetMsgParam().size());

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
            ParseParamController(notifyIn.GetMsgParam(), userModel);
            int nRet = dataProxy->AddUser(userModel);
            notifyOut.nMsg = MSG_ADDUSER;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
            break;
        }
        case MSG_DELETEUSER:
        {
            int userid = 0;
            ParseParamController(notifyIn.GetMsgParam(), userid);
            int nRet = dataProxy->DeleteUserByUserID(userid);
            notifyOut.nMsg = MSG_DELETEUSER;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
            break;
        }
        case MSG_MODIFYUSER:
        {
            int userid = 0;
            string address;
            ParseParamController(notifyIn.GetMsgParam(), userid, address);
            int nRet = dataProxy->ModifyUser(userid, address);
            notifyOut.nMsg = MSG_MODIFYUSER;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
            break;
        }
        case MSG_MODIFYPASSWD:
        {
            QString strOldPasswd;
            QString strNewPasswd;
            QString strRepeatPasswd;
            ParseParamController(notifyIn.GetMsgParam(), strOldPasswd, strNewPasswd, strRepeatPasswd);
            int nRet = dataProxy->ModifyPasswd(strOldPasswd.toUtf8().data(), strNewPasswd.toUtf8().data(), strRepeatPasswd.toUtf8().data());
            notifyOut.nMsg = MSG_MODIFYPASSWD;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
            break;
        }
        case MSG_QUERYALLUSER:
        {
            set<UserModel> setUserData;
            int nRet = dataProxy->QueryAllUser(setUserData);
            notifyOut.nMsg = MSG_QUERYALLUSER;
            PackageParamController(notifyOut.GetMsgParam(), setUserData, nRet);
            break;
        }
        case MSG_ADDUSERTYPE:
        {
            int userType = 0;
            QString strText;
            ParseParamController(notifyIn.GetMsgParam(), userType, strText);
            int nRet = dataProxy->AddUserType(userType, strText.toUtf8().data());
            notifyOut.nMsg = MSG_ADDUSERTYPE;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
            break;
        }
        case MSG_LOGINHISTORY:
        {
            set<LoginHistoryModel> setLoginHistory;
            int nRet = dataProxy->QueryLoginHistory(setLoginHistory);
            notifyOut.nMsg = MSG_LOGINHISTORY;
            PackageParamController(notifyOut.GetMsgParam(), setLoginHistory, nRet);
            break;
        }
        case MSG_DELETELOGINHISTORY:
        {
            QString strAccount;
            ParseParamController(notifyIn.GetMsgParam(), strAccount);
            int nRet = dataProxy->DeleteLoginHistory(strAccount.toUtf8().data());
            notifyOut.nMsg = MSG_DELETELOGINHISTORY;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
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
            //int nAttr = 0;
            QString strText;
            int nRet = 0;
            ParseParamController(notifyIn.GetMsgParam(), bookid, nAttrType, strText);
            qDebug() << "bookid:" << bookid << "nAttrType:" << nAttrType;
            notifyOut.nMsg = MSG_MODIFYBOOK;
            PackageParamController(notifyOut.GetMsgParam(), nRet);
//            if (nAttrType == BOOK_ATTR_CLASS || nAttrType == BOOK_ATTR_NUMBER || nAttrType == BOOK_ATTR_PRICE)
//            {
//                //ParseParamController(notifyIn.GetMsgParam(), bookid, nAttrType, nAttr);
//                //nRet = dataProxy->ModifyBook(bookid, nAttrType, nAttr);
//            }
//            else
//            {

                //nRet = dataProxy->ModifyBook(bookid, nAttrType, strText.toUtf8().data());
            //}

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
            PackageParamController(notifyOut.GetMsgParam(), setBookData, nRet);
            break;
        }
        default:
            break;
    }

    qDebug() << "DataController::handleEvent>>END>>notifyOut.nMsg:" << notifyOut.nMsg << "notifyOut>>size:" << QString::number(notifyOut.GetMsgParam().size());
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyOut);
}
