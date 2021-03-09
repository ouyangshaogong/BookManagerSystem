#ifndef __READER_CARD_DAO__
#define __READER_CARD_DAO__

#include "TableReaderCard.h"
#include "SQLException.h"
#include "SQLConnection.h"
#include "common.h"

class ReaderCardDao
{

public:
    virtual int AddReaderCard(TableReaderCard &readerCard) throw (SQLException) = 0;
    virtual int DeleteReaderCardByReaderID(const string &strReaderID) throw (SQLException) = 0;
    virtual int DeleteAllReaderCard() throw (SQLException) = 0;
    virtual int UpdateReaderCard(const FieldCond &setFieldCond, const FieldCond &fieldCond) throw (SQLException) = 0;
    virtual int QueryReaderCardByField(const FieldCond& fieldCond, list<vector<string> > &listBookInfo) throw (SQLException) = 0;
};

#endif