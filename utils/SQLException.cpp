#include "SQLException.h"

SQLException::SQLException(string strException)
{
    m_strException = strException;
}

const char* SQLException::what() const throw ()
{
    cout << "SQLException: "<< m_strException << endl;
    return this->m_strException.c_str();
}

