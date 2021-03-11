#include "BookManagerService.h"

pthread_mutex_t BookManagerService::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
BookManagerService* BookManagerService::m_instance = NULL;

BookManagerService::BookManagerService()
{
    m_pBookInfoImpl = new BookInfoDaoImpl();
}

BookManagerService::~BookManagerService()
{
    if (m_pBookInfoImpl == NULL)
    {
        delete m_pBookInfoImpl;
        m_pBookInfoImpl = NULL;
    }
}

BookManagerService* BookManagerService::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance == NULL)
        {
            m_instance = new BookManagerService();           
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }

    return m_instance;
}

void BookManagerService::DestoryInstance()
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

int BookManagerService::AddBook(TblBookInfo &bookInfo)
{
    try
    {
        if (OK != m_pBookInfoImpl->AddBook(bookInfo))
        {   
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
    
}

int BookManagerService::DeleteBookAllBook()
{
    try
    {
        if (OK != m_pBookInfoImpl->DeleteBookAllBook())
        {   
            cout << "BookManagerService::DeleteBookAllBook>>DeleteBook FAIL!" << endl;
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
}

int BookManagerService::DeleteBookByBookID(const string &strBookID)
{
    try
    {
        string strFieldName = "book_id";
        if (OK != m_pBookInfoImpl->DeleteBookByField(strFieldName, strBookID))
        {   
            cout << "BookManagerService::DeleteBookByBookID>>DeleteBook FAIL!" << endl;
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
}

int BookManagerService::UpdateBookInfoByBookID(const int nBookID, TblBookInfo &bookInfo)
{
    try
    {      
        TblBookInfo tmpBook;
        if (OK != m_pBookInfoImpl->QueryBookByBookID(nBookID, tmpBook))
        {
            return FAIL;
        }

        
        if (OK != m_pBookInfoImpl->UpdateBookInfoByBookID(nBookID, bookInfo))
        {
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }
    
    return OK;
}

int BookManagerService::QueryBookByBookID(const int nBookID, TblBookInfo &bookInfo)
{
    try
    {      
        if (OK != m_pBookInfoImpl->QueryBookByBookID(nBookID, bookInfo))
        {
            return FAIL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }
    
    return OK;
}