#ifndef __SQL_CONNECTION__
#define __SQL_CONNECTION__

#include "common.h"
#include <pthread.h>
#include <mysql/mysql.h>

using namespace std;

class SQLConnection
{
public:
    static SQLConnection* Instance();
    static void DestoryInstance();

    MYSQL* GetConnection();
    bool ExecuteSQL(const string &strSQL);
    
    virtual ~SQLConnection();
private:
    SQLConnection();

    void InitMySQL();
    int ConnectMySQL();
    void CloseMySQL();

private:
    static SQLConnection *m_instance;
    static pthread_mutex_t m_Mutex;
    MYSQL *m_connection;
};

#endif