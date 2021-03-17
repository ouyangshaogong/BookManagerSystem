#ifndef __DATA_PROXY__
#define __DATA_PROXY__

#include "proxy.h"
#include "usermodel.h"

class DataProxy: public Proxy
{
public:
    DataProxy():Proxy("DataProxy"){};

    void AddLevel(int nLevel);
    int AddUser(UserModel userModel);
    int DeleteUser(int userid);
    int ModifyUser(int userid, string address);
    int QueryUser(string strAuther);

    void AddBook();
    void DeleteBook();
    void ModifyBook();
    void QueryBook();

private:
    UserModel m_userModel;
};

#endif
