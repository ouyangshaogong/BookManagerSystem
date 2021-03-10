#include "ReaderCardMgrService.h"

pthread_mutex_t ReaderCardMgrService::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
ReaderCardMgrService* ReaderCardMgrService::m_instance = NULL;

ReaderCardMgrService::ReaderCardMgrService()
{
    m_pReaderCardImpl = new ReaderCardDaoImpl();
}

ReaderCardMgrService::~ReaderCardMgrService()
{
    if (m_pReaderCardImpl == NULL)
    {
        delete m_pReaderCardImpl;
        m_pReaderCardImpl = NULL;
    }
}

ReaderCardMgrService* ReaderCardMgrService::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance == NULL)
        {
            m_instance = new ReaderCardMgrService();           
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }

    return m_instance;
}

void ReaderCardMgrService::DestoryInstance()
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

int ReaderCardMgrService::AddReaderCard(TableReaderCard &readerCard)
{
    try
    {
        if (OK != m_pReaderCardImpl->AddReaderCard(readerCard))
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

int ReaderCardMgrService::DeleteAllReaderCard()
{
    try
    {
        if (OK != m_pReaderCardImpl->DeleteAllReaderCard())
        {   
            cout << "ReaderCardMgrService::DeleteAllReaderCard>>FAIL!" << endl;
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

int ReaderCardMgrService::DeleteReaderCardByReaderID(const string &strReaderID)
{
    try
    {
        if (OK != m_pReaderCardImpl->DeleteReaderCardByReaderID(strReaderID))
        {   
            cout << "ReaderCardMgrService::DeleteReaderCardByReaderID>>DeleteBook FAIL!" << endl;
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

int ReaderCardMgrService::UpdateReaderCardByField(const FieldCond &setFieldCond, const FieldCond &fieldCond)
{
    try
    {
        if (OK != m_pReaderCardImpl->UpdateReaderCard(setFieldCond, fieldCond))
        {   
            cout << "ReaderCardMgrService::UpdateReaderCardByField>>UpdateBookInfo FAIL!" << endl;
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



int ReaderCardMgrService::QueryReaderCardByField(const FieldCond &fieldCond, list<TableReaderCard> &listReaderCard)
{
    try
    {
        list<vector<string> > listVecBookInfo;
        if (OK != m_pReaderCardImpl->QueryReaderCardByField(fieldCond, listVecBookInfo))
        {   
            return FAIL;
        }

        list<vector<string> >::iterator iter = listVecBookInfo.begin();
        for (; iter != listVecBookInfo.end(); iter++)
        {
            bool bBookFlag = false;
            TableReaderCard readerCard;
            for(int i = 0; i < (*iter).size(); i++)
            {
                if ((*iter)[i] == fieldCond.fieldValue)
                {
                    bBookFlag = true;
                    break;
                }
            }

            if (bBookFlag)
            {
                readerCard.SetReaderID(atoi((*iter)[0].c_str()));
                readerCard.SetUserName((*iter)[1]);
                readerCard.SetPasswd((*iter)[2]);

                listReaderCard.push_back(readerCard);
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