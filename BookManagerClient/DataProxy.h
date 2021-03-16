#ifndef __DATA_PROXY__
#define __DATA_PROXY__

#include "proxy.h"
#include "usermodel.h"

class DataProxy: public Proxy
{
public:
    DataProxy():Proxy("DataProxy"){};

    void AddLevel(int nLevel);
    void AddUser();
    void DeleteUser();
    void ModifyUser();
    void QueryUser();

    void AddBook();
    void DeleteBook();
    void ModifyBook();
    void QueryBook();

private:

};

#endif
