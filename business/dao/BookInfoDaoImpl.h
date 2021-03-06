#ifndef __BOOK_INFO_DAO_IMPL__
#define __BOOK_INFO_DAO_IMPL__

#include "BookInfoDao.h"
#include "TblBookInfo.h"
#include "SQLConnection.h"
#include "common.h"

class BookInfoDaoImpl: public BookInfoDao
{

public:
    BookInfoDaoImpl();
    virtual int AddBook(TblBookInfo &bookInfo) throw (SQLException);
    virtual int DeleteBook(const string &fieldName, const string &fieldValue) throw (SQLException);
    virtual int UpdateBook(const string &fieldName, const string &fieldValue, TblBookInfo &bookInfo) throw (SQLException);
    virtual int QueryBook(const string &fieldName, const string &fieldValue, list<vector<string> > &listBookInfo) throw (SQLException);

private:
    MYSQL *m_pMySQLConn;
};

#endif