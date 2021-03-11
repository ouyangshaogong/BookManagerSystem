#include "UserManagerService.h"

#define DEFAULT_PASSWD "123456"

pthread_mutex_t UserManagerService::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
UserManagerService* UserManagerService::m_instance = NULL;

UserManagerService::UserManagerService()
:m_nUserMaker(0), m_nReaderCardMaker(0)
{
    m_pUserMgr = new UserManager();
    m_pReaderCard = new ReaderCardManager();
}

UserManagerService::~UserManagerService()
{
    if (m_pUserMgr != NULL)
    {
        delete m_pUserMgr;
        m_pUserMgr = NULL;
    }

    if (m_pReaderCard != NULL)
    {
        delete m_pReaderCard;
        m_pReaderCard = NULL;
    }
}

UserManagerService* UserManagerService::Instance()
{
    if (m_instance == NULL)
    {
        pthread_mutex_lock(&m_Mutex);    // 加锁

        if (m_instance == NULL)
        {
            m_instance = new UserManagerService();           
        }

        pthread_mutex_unlock(&m_Mutex);  // 解锁
    }

    return m_instance;
}

void UserManagerService::DestoryInstance()
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

int UserManagerService::AddUser(TblUserInfo &userInfo)
{
    try
    {
        int nUserID = m_nUserMaker.GenerateID();
        int nReaderCard = m_nReaderCardMaker.GenerateID();
        userInfo.SetUserID(nUserID);
        userInfo.SetReaderID(nReaderCard);
        if (OK != m_pUserMgr->AddUser(userInfo))
        {   
            return FAIL;
        }

        TableReaderCard readerCard;
        readerCard.SetReaderID(nReaderCard);
        readerCard.SetUserName(userInfo.GetUserName());
        readerCard.SetPasswd(DEFAULT_PASSWD);
        if (OK != m_pReaderCard->AddReaderCard(readerCard))
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

int UserManagerService::DeleteAllUser()
{
    try
    {
        if (OK != m_pReaderCard->DeleteAllReaderCard())
        {   
            cout << "UserManagerService::DeleteAllReaderCard>>FAIL!" << endl;
            return FAIL;
        }

        if (OK != m_pUserMgr->DeleteAllUser())
        {   
            cout << "UserManagerService::DeleteAllUser>>FAIL!" << endl;
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

int UserManagerService::DeleteUserByUserID(const int nUserID)
{
    try
    {
        TblUserInfo userInfo;
        string strUserID = to_string(nUserID);
        if (OK != m_pUserMgr->QueryUserByUserID(strUserID, userInfo))
        {   
            return FAIL;
        }

        string strReaderID = to_string(userInfo.GetReaderID());
        if (OK != m_pReaderCard->DeleteReaderCardByReaderID(strReaderID))
        {   
            cout << "UserManagerService::DeleteReaderCardByReaderID>>DeleteBook FAIL!" << endl;
            return FAIL;
        }

        if (OK != m_pUserMgr->DeleteUserByUserID(strUserID))
        {   
            cout << "UserManagerService::DeleteBookByBookID>>DeleteBook FAIL!" << endl;
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

int UserManagerService::UpdateUserInfoByUserID(const int nUserID, TblUserInfo &userInfo)
{
    try
    {  
        TblUserInfo tmpUserInfo;
        if (OK != QueryUserByUserID(nUserID, tmpUserInfo))
        {
            return FAIL;
        }

        tmpUserInfo.SetPhone(userInfo.GetPhone());
        tmpUserInfo.SetUserName(userInfo.GetUserName());
        tmpUserInfo.SetSex(userInfo.GetSex());
        tmpUserInfo.SetBirth(userInfo.GetBirth());
        tmpUserInfo.SetAddress(userInfo.GetAddress());
        tmpUserInfo.SetUserType(userInfo.GetUserType());
        if (OK != m_pUserMgr->UpdateUserInfoByUserID(nUserID, tmpUserInfo))
        {   
            cout << "UserManagerService::UpdateUserInfoByField>>UpdateBookInfo FAIL!" << endl;
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



int UserManagerService::QueryUserByUserID(const int &nUserID, TblUserInfo &bookInfo)
{
    try
    {
        string strUserID = to_string(nUserID);
        if (OK != m_pUserMgr->QueryUserByUserID(strUserID, bookInfo))
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

int UserManagerService::QueryReaderCardByReaderID(const string &strReaderID, TableReaderCard readerCard)
{
    try
    {
        if (OK != m_pReaderCard->QueryReaderCardByReaderID(strReaderID, readerCard))
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

int UserManagerService::UpdateUserPasswd(const string &strReaderID, const string &strPasswd)
{
    try
    {
        if (OK != m_pReaderCard->UpdateReaderCardPasswd(strReaderID, strPasswd))
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