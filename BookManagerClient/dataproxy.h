#ifndef __DATA_PROXY__
#define __DATA_PROXY__

#include "proxy.h"
#include "usermodel.h"
#include "bookmodel.h"


class DataProxy: public Proxy
{
public:
    DataProxy():Proxy("DataProxy"){};
    ~DataProxy();
    void AddLevel(int nLevel);
    int AddUser(UserModel userModel);
    int DeleteUser(int userid);
    int ModifyUser(int userid, string address);
    int ModifyPasswd(string strOldPasswd, string strNewPasswd, string strRepeatPasswd);
    int QueryAllUser(set<UserModel> &userModel);

    void AddBook();
    void DeleteBook();
    void ModifyBook();
    void QueryBook();
    int QueryAllBook(set<BookModel> &setBookModel);
private:
    UserModel m_userModel;
    BookModel m_bookModel;
};

#endif
