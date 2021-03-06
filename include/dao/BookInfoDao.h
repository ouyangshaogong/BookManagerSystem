#ifndef __BOOK_INFO_DAO__
#define __BOOK_INFO_DAO__

#include "TblBookInfo.h"
#include "SQLException.h"

class BookInfoDao
{

public:
    virtual int AddBook(TblBookInfo &bookInfo) throw (SQLException);
    virtual int DeleteBook(const string &fieldName, const string &fieldValue) throw (SQLException);
    virtual int UpdateBook(const string &fieldName, const string &fieldValue, TblBookInfo &bookInfo) throw (SQLException);
    virtual int QueryBook(const string &fieldName, const string &fieldValue, list<vector<string> > &listBookInfo) throw (SQLException);
};

#endif