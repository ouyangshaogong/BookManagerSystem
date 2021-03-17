#include "datacontroller.h"
#include "dataproxy.h"
#include "datacommonfunc.h"
#include "usermodel.h"
#include <QtDebug>
#include <QString>

//封装参数递归终止函数
void PackageParamController(map<string, void*> &mapParam)
{
}
//封装参数展开函数
template <class T, class ...Args>
void PackageParamController(map<string, void*> &mapParam, T head, Args... rest)
{
    T *t = new T;
    *t = head;
    mapParam.insert(map<string, void*>::value_type(typeid(head).name(), (void*)t));
    PackageParamController(mapParam, rest...);
}

//解析参数递归终止函数
void ParseParamController(map<string, void*> &mapParam)
{
    mapParam.clear();
    qDebug() << "g_strMapVoid.size:" << mapParam.size();
}

//解析参数展开函数
template <class T, class ...Args>
void ParseParamController(map<string, void*> &mapParam, T &head, Args&... rest)
{
    map<string, void*>::iterator iter = mapParam.find(typeid(T).name());
    if (iter != mapParam.end())
    {
        head = *((T*)iter->second);
    }

    T *t = (T*)iter->second;
    delete t;
    ParseParamController(mapParam, rest...);
}

void DataController::handleEvent(NotifyMsg notifyIn)
{
    qDebug() << "DataController::handleEvent>>" << notifyIn.nMsg << QString::number(notifyIn.GetMapParam().size());

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
            int nRet = dataProxy->DeleteUser(userid);
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
        case MSG_QUERYUSER:
        {
            string strAuther;
            ParseParamController(notifyIn.GetMapParam(), strAuther);
            int nRet = dataProxy->QueryUser(strAuther);
            notifyOut.nMsg = MSG_QUERYUSER;
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
        default:
            break;
    }

    qDebug() << "DataController::handleEvent>>" << notifyOut.nMsg << QString::number(notifyOut.GetMapParam().size());
    DataCommonFunc::Instance()->SendNotifyCationToView(notifyOut);
}
