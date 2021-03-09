#ifndef __READER_CARD_DAO_IMPL__
#define __READER_CARD_DAO_IMPL__

#include "ReaderCardDao.h"


class ReaderCardDaoImpl: public ReaderCardDao
{

public:

    ReaderCardDaoImpl();
    virtual ~ReaderCardDaoImpl(){}

    virtual int AddReaderCard(TableReaderCard &readerCard) throw (SQLException);
    virtual int DeleteReaderCardByReaderID(const string &strReaderID) throw (SQLException);
    virtual int DeleteAllReaderCard() throw (SQLException);
    virtual int UpdateReaderCard(const FieldCond &setFieldCond, const FieldCond &fieldCond) throw (SQLException);
    virtual int QueryReaderCardByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException);

private:
    MYSQL *m_pMySQLConn;
};

#endif