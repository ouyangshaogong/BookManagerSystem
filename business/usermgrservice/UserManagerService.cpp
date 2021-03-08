#include "UserManagerService.h"

pthread_mutex_t UserManagerService::m_Mutex = PTHREAD_MUTEX_INITIALIZER;
UserManagerService* UserManagerService::m_instance = NULL;

UserManagerService::UserManagerService()
{
    m_pUserInfoImpl = new UserInfoDaoImpl();
}

UserManagerService::~UserManagerService()
{
    if (m_pUserInfoImpl == NULL)
    {
        delete m_pUserInfoImpl;
        m_pUserInfoImpl = NULL;
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
        if (OK != m_pUserInfoImpl->AddUser(userInfo))
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
        if (OK != m_pUserInfoImpl->DeleteAllUser())
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

int UserManagerService::DeleteUserByUserID(const string &strUserID)
{
    try
    {
        string strFieldName = "book_id";
        if (OK != m_pUserInfoImpl->DeleteUserByUserID(strFieldName, strUserID))
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

int UserManagerService::UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond)
{
    try
    {
        if (OK != m_pUserInfoImpl->UpdateUserInfoByField(setFieldCond, fieldCond))
        {   
            cout << "BookManagerService::UpdateBookInfoByField>>UpdateBookInfo FAIL!" << endl;
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



int UserManagerService::QueryUserByField(const FieldCond &fieldCond, list<TblUserInfo> &listUserInfo)
{
    try
    {
        list<vector<string> > listVecBookInfo;
        if (OK != m_pUserInfoImpl->QueryUserByField(fieldCond, listVecBookInfo))
        {   
            return FAIL;
        }

        list<vector<string> >::iterator iter = listVecBookInfo.begin();
        for (; iter != listVecBookInfo.end(); iter++)
        {
            bool bBookFlag = false;
            TblUserInfo userInfo;
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
                userInfo.SetUserID(atoi((*iter)[0].c_str()));
                userInfo.SetReaderID(atoi((*iter)[1].c_str()));
                userInfo.SetPhone((*iter)[2]);
                userInfo.SetUserName((*iter)[3]);
                userInfo.SetSex((*iter)[4]);
                userInfo.SetBirth((*iter)[5]);
                userInfo.SetAddress((*iter)[6]);
                userInfo.SetUserType(atoi((*iter)[8].c_str()));

                listUserInfo.push_back(userInfo);
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