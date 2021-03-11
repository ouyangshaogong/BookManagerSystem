#include "ReaderCardManager.h"

ReaderCardManager::ReaderCardManager()
{
    m_pReaderCardImpl = new ReaderCardDaoImpl();
}

ReaderCardManager::~ReaderCardManager()
{
    if (m_pReaderCardImpl == NULL)
    {
        delete m_pReaderCardImpl;
        m_pReaderCardImpl = NULL;
    }
}

int ReaderCardManager::AddReaderCard(TableReaderCard &readerCard)
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

int ReaderCardManager::DeleteAllReaderCard()
{
    try
    {
        if (OK != m_pReaderCardImpl->DeleteAllReaderCard())
        {   
            cout << "ReaderCardManager::DeleteAllReaderCard>>FAIL!" << endl;
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

int ReaderCardManager::DeleteReaderCardByReaderID(const string &strReaderID)
{
    try
    {
        if (OK != m_pReaderCardImpl->DeleteReaderCardByReaderID(strReaderID))
        {   
            cout << "ReaderCardManager::DeleteReaderCardByReaderID>>DeleteBook FAIL!" << endl;
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

int ReaderCardManager::UpdateReaderCardPasswd(const string &strUserName, const string &strPasswd)
{
    try
    {
        FieldCond fieldCond;
        fieldCond.fieldName = "username";
        fieldCond.fieldValue = strUserName;

        FieldCond setFieldCond;
        setFieldCond.fieldName = "password";
        setFieldCond.fieldValue = strPasswd;
        if (OK != UpdateReaderCardByField(setFieldCond, fieldCond))
        {   
            cout << "ReaderCardManager::UpdateReaderCardPasswd>>UpdateBookInfo FAIL!" << endl;
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

int ReaderCardManager::UpdateReaderCardByField(const FieldCond &setFieldCond, const FieldCond &fieldCond)
{
    try
    {
        if (OK != m_pReaderCardImpl->UpdateReaderCard(setFieldCond, fieldCond))
        {   
            cout << "ReaderCardManager::UpdateReaderCardByField>>UpdateBookInfo FAIL!" << endl;
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

int ReaderCardManager::QueryReaderCardByReaderID(const string &strReaderID, TableReaderCard &readerCard)
{
    try
    {
        list<TableReaderCard> listReaderCard;

        FieldCond fieldCond;
        fieldCond.fieldName = "reader_id";
        fieldCond.fieldValue = strReaderID;
        if (OK != QueryReaderCardByField(fieldCond, listReaderCard))
        {
            return FAIL;
        }

        readerCard = (*listReaderCard.begin());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return FAIL;
    }
    
    return OK;
}

int ReaderCardManager::QueryReaderCardByField(const FieldCond &fieldCond, list<TableReaderCard> &listReaderCard)
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