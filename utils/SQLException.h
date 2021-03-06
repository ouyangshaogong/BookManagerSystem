#ifndef __SQL_EXCEPTION__
#define __SQL_EXCEPTION__

#include "common.h"

class SQLException: public exception
{
public:
    SQLException(string strException);
    virtual const char* what() const throw ();

private:
    string m_strException;
};


#endif