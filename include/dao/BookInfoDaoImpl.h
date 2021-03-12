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
    virtual int DeleteBookByField(const string &fieldName, const string &fieldValue) throw (SQLException);
    virtual int DeleteBookByBookID(const string &strBookID) throw (SQLException);
    virtual int DeleteBookAllBook() throw (SQLException);
    virtual int UpdateBookInfoByField(const vector<FieldCond> &setFieldCond, const FieldCond &fieldCond) throw (SQLException);
    virtual int UpdateBookInfoByBookID(const int nBookID, TblBookInfo &bookInfo) throw (SQLException);
    virtual int QueryBookByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException);
    virtual int QueryBookByBookID(const int nBookID, TblBookInfo &bookInfo) throw (SQLException);

private:
    MYSQL *m_pMySQLConn;
};

#endif