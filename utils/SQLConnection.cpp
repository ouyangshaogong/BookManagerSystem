#include "SQLConnection.h"

pthread_mutex_t SQLConnection::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
SQLConnection* SQLConnection::m_instance = NULL;

SQLConnection::SQLConnection()
{
    m_connection = new MYSQL;
    InitMySQL();
    ConnectMySQL();
}

SQLConnection::~SQLConnection()
{
    CloseMySQL();
    if (m_connection != NULL)
    {
        delete m_connection;
    }
}

SQLConnection* SQLConnection::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance == NULL)
        {
            m_instance = new SQLConnection();           
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }

    return m_instance;
}

void SQLConnection::DestoryInstance()
{
    if (m_instance != NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance != NULL)
        {
            delete m_instance;
		    m_instance = NULL;
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }
    
}

MYSQL* SQLConnection::GetConnection()
{
    return m_connection;
}

bool SQLConnection::ExecuteSQL(const string &strSQL)
{
    int nRet = mysql_real_query(m_connection, strSQL.c_str(), strSQL.length());
    if (nRet != 0)
    {
        cout << mysql_error(m_connection) << endl;
        return false;
    }
   
    return true;
}

void SQLConnection::InitMySQL()
{
    mysql_init(m_connection);
}




int SQLConnection::ConnectMySQL()
{
    if(!mysql_real_connect(m_connection,"192.168.2.107","root","qazwsx","book_manager",3306,NULL,0))
    {
        printf("connect_mysql error:%s", mysql_error(m_connection));
        return FAIL;
    }

    return OK;
}

void SQLConnection::CloseMySQL()
{
    mysql_close(m_connection);
}

