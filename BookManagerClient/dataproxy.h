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
    DataProxy();
    ~DataProxy();

    void MakeUserData();
    void MakeBookData();

    void AddLevel(int nLevel);
    int AddUser(UserModel userModel);
    int DeleteUserByUserID(int userid);
    int ModifyUser(int userid, int nAttrType, string strText);
    int ModifyPasswd(string strOldPasswd, string strNewPasswd, string strRepeatPasswd);
    int QueryAllUser(set<UserModel> &userModel);
    int AddUserType(int userType, string strText);

    void AddBook();
    void DeleteBook();
    int ModifyBook(int bookid, int strModifyType, string strText);
    int ModifyBook(int bookid, int nModifyType, int nBookAttr);
    void QueryBook();
    int QueryAllBook(set<BookModel> &setBookModel);

    int QueryLoginHistory(set<LoginHistoryModel> & setLoginHisroty);
    int DeleteLoginHistory(string strAcount);
private:
    vector<BookModel> m_vecBookModel;
};

#endif
