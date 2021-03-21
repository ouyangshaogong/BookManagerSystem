#ifndef __DATA_PROXY__
#define __DATA_PROXY__

#include "proxy.h"
#include "usermodel.h"
#include "bookmodel.h"
#include "loginhistorymodel.h"
#include <QDateTime>

class DataProxy: public Proxy
{
public:
    DataProxy():Proxy("DataProxy"){};
    ~DataProxy();
    void AddLevel(int nLevel);
    int AddUser(UserModel userModel);
    int DeleteUserByUserID(int userid);
    int ModifyUser(int userid, string address);
    int ModifyPasswd(string strOldPasswd, string strNewPasswd, string strRepeatPasswd);
    int QueryAllUser(set<UserModel> &userModel);
    int AddUserType(int userType, string strText);

    void AddBook();
    void DeleteBook();
    void ModifyBook();
    void QueryBook();
    int QueryAllBook(set<BookModel> &setBookModel);

    int QueryLoginHistory(set<LoginHistoryModel> & setLoginHisroty);
    int DeleteLoginHistory(string strAcount);
private:

};

#endif
