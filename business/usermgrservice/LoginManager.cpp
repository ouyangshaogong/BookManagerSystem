#include "LoginManager.h"

LoginManager::LoginManager()
{
    m_pReaderCardImpl = new ReaderCardDaoImpl();
}

LoginManager::~LoginManager()
{
    if (m_pReaderCardImpl != NULL)
    {
        delete m_pReaderCardImpl;
        m_pReaderCardImpl = NULL;
    }
}

int LoginManager::Login(const string &strUserName, const string &strPasswd)
{
    try
    {
        TableReaderCard readerCard;
        if (OK != m_pReaderCardImpl->QueryReaderCardByUserName(strUserName, readerCard))
        {
            cout << "LoginManager::Login>>QueryReaderCardByUserName FAIL!" << endl;
            return FAIL;
        }

        if (strPasswd != readerCard.GetPasswd())
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