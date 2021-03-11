#include "CardUserNameMaker.h"

#define MAX_USERNAME 400000

CardUserNameMaker::CardUserNameMaker()
{
    m_nUserName = 0;
    m_Mutex = PTHREAD_MUTEX_INITIALIZER;
}

CardUserNameMaker::~CardUserNameMaker()
{

}

string CardUserNameMaker::GenerateUserName()
{
    pthread_mutex_lock(&m_Mutex);    // 加锁
    
    ++m_nUserName;
    if (m_nUserName == MAX_USERNAME)
    {
        m_nUserName = 1;
    }

    pthread_mutex_unlock(&m_Mutex);  // 解锁

    stringstream ss;
	ss << setw(6) << setfill('0') << m_nUserName ;
	string strTmp;
	ss >> strTmp;

    string strUserName("SX");
    strUserName += strTmp;
    
    return strUserName;
}