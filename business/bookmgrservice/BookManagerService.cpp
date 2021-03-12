#include "BookManagerService.h"

pthread_mutex_t BookManagerService::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
BookManagerService* BookManagerService::m_instance = NULL;

BookManagerService::BookManagerService()
{
    m_pBookInfoImpl = new BookInfoDaoImpl();
    m_pLendListImpl = new LendListDaoImpl();
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

int BookManagerService::DeleteBookByBookID(const int nBookID)
{
    try
    {
        string strFieldName = "book_id";
        string strBookID = to_string(nBookID);
        if (OK != m_pBookInfoImpl->DeleteBookByBookID(strBookID))
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

int BookManagerService::DeleteAllLend()
{
    try
    {      
        if (OK != m_pLendListImpl->DeleteAllLendData())
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

int BookManagerService::LendBook(const int nUserID, const int nBookID, const string &lendDate)
{
    try
    {
        TableLendList lendList;
        lendList.SetUserID(nUserID);
        lendList.SetBookID(nBookID);
        lendList.SetLendDate(lendDate);
        lendList.SetBackDate("19901110");
        lendList.SetLendState(LENDBOOK);
        if (OK != m_pLendListImpl->AddLendData(lendList))
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

int BookManagerService::BackBook(const int nUserID, const int nBookID, const string &backDate)
{
    try
    {
        string strUserID =  to_string(nUserID);
        string strBookID = to_string(nBookID);
        if (OK != m_pLendListImpl->UpdateBackDateByUserIDAndBookID(strUserID, strBookID, backDate))
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

int BookManagerService::DeleteLendByUserIDAndBookID(const int nUserID, const int nBookID)
{
    try
    {
        string strUserID = to_string(nUserID);
        string strBookID = to_string(nBookID);
        if (OK != m_pLendListImpl->DeleteLendByUserIDAndBookID(strUserID, strBookID))
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