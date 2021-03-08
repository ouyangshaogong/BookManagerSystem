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

int BookManagerService::UpdateBook()
{

}



int BookManagerService::QueryBookByName(const string &strBookName, list<TblBookInfo> &listBookInfo)
{
    try
    {
        string strFieldName = "name";
        list<vector<string> > listVecBookInfo;
        if (OK != m_pBookInfoImpl->QueryBook(strFieldName, strBookName, listVecBookInfo))
        {   
            return FAIL;
        }

        list<vector<string> >::iterator iter = listVecBookInfo.begin();
        for (; iter != listVecBookInfo.end(); iter++)
        {
            bool bBookFlag = false;
            TblBookInfo bookInfo;
            for(int i = 0; i < (*iter).size(); i++)
            {
                if ((*iter)[i] == strBookName)
                {
                    bBookFlag = true;
                    break;
                }
            }

            if (bBookFlag)
            {
                bookInfo.SetBookID(atoi((*iter)[0].c_str()));
                bookInfo.SetClassID(atoi((*iter)[1].c_str()));
                bookInfo.SetName((*iter)[2]);
                bookInfo.SetAuther((*iter)[3]);
                bookInfo.SetPublish((*iter)[4]);
                bookInfo.SetISBN((*iter)[5]);
                bookInfo.SetIntroduction((*iter)[6]);
                bookInfo.SetLanguage((*iter)[7]);
                bookInfo.SetPrice(atoi((*iter)[8].c_str()));
                bookInfo.SetPubDate((*iter)[9]);
                bookInfo.SetNumber(atoi((*iter)[10].c_str()));

                listBookInfo.push_back(bookInfo);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }

    return OK;
}