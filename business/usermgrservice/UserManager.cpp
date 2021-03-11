#include "UserManager.h"

UserManager::UserManager()
{
    m_pUserInfoImpl = new UserInfoDaoImpl();
}

UserManager::~UserManager()
{
    if (m_pUserInfoImpl == NULL)
    {
        delete m_pUserInfoImpl;
        m_pUserInfoImpl = NULL;
    }
}

int UserManager::AddUser(TblUserInfo &userInfo)
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

int UserManager::DeleteAllUser()
{
    try
    {
        if (OK != m_pUserInfoImpl->DeleteAllUser())
        {   
            cout << "UserManager::DeleteAllUser>>FAIL!" << endl;
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

int UserManager::DeleteUserByUserID(const string &strUserID)
{
    try
    {
        string strFieldName = "book_id";
        if (OK != m_pUserInfoImpl->DeleteUserByUserID(strUserID))
        {   
            cout << "UserManager::DeleteBookByBookID>>DeleteBook FAIL!" << endl;
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

int UserManager::UpdateUserInfoByUserID(const int nUserID, TblUserInfo &userInfo)
{
    try
    {
        FieldCond fieldCond;
        fieldCond.fieldName = "user_id";
        fieldCond.fieldValue = to_string(nUserID);

        vector<FieldCond> setFieldCond;
        FieldCond tmpFieldCond;
        tmpFieldCond.fieldName = "phone";
        tmpFieldCond.fieldValue = userInfo.GetPhone();
        setFieldCond.push_back(tmpFieldCond);

        tmpFieldCond.fieldName = "name";
        tmpFieldCond.fieldValue = userInfo.GetUserName();
        setFieldCond.push_back(tmpFieldCond);

        tmpFieldCond.fieldName = "sex";
        tmpFieldCond.fieldValue = userInfo.GetSex();
        setFieldCond.push_back(tmpFieldCond);
        tmpFieldCond.fieldName = "birth";
        tmpFieldCond.fieldValue = userInfo.GetBirth();
        setFieldCond.push_back(tmpFieldCond);

        tmpFieldCond.fieldName = "address";
        tmpFieldCond.fieldValue = userInfo.GetAddress();
        setFieldCond.push_back(tmpFieldCond);

        tmpFieldCond.fieldName = "user_type";
        tmpFieldCond.fieldValue = to_string(userInfo.GetUserType());
        setFieldCond.push_back(tmpFieldCond);

        if (OK != UpdateUserInfoByField(setFieldCond, fieldCond))
        {   
            cout << "UserManager::UpdateUserInfoByUserID>>UpdateBookInfo FAIL!" << endl;
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

int UserManager::UpdateUserInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond)
{
    try
    {
        if (OK != m_pUserInfoImpl->UpdateUserInfoByField(setFieldCond, fieldCond))
        {   
            cout << "UserManager::UpdateBookInfoByField>>UpdateBookInfo FAIL!" << endl;
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

int UserManager::QueryUserByUserID(const string &strUSerID, TblUserInfo &userInfo)
{
    list<TblUserInfo> listUserInfo;

    FieldCond fieldCond;
    fieldCond.fieldName = "user_id";
    fieldCond.fieldValue = strUSerID;
    if (OK != QueryUserByField(fieldCond, listUserInfo))
    {
        return FAIL;
    }

    userInfo.SetUserID((*listUserInfo.begin()).GetUserID());
    userInfo.SetReaderID((*listUserInfo.begin()).GetReaderID());
    userInfo.SetPhone((*listUserInfo.begin()).GetPhone());
    userInfo.SetUserName((*listUserInfo.begin()).GetUserName());
    userInfo.SetSex((*listUserInfo.begin()).GetSex());
    userInfo.SetBirth((*listUserInfo.begin()).GetBirth());
    userInfo.SetAddress((*listUserInfo.begin()).GetAddress());
    userInfo.SetUserType((*listUserInfo.begin()).GetUserType());

    return OK;
}

int UserManager::QueryUserByField(const FieldCond &fieldCond, list<TblUserInfo> &listUserInfo)
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
                userInfo.SetUserType(atoi((*iter)[7].c_str()));

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