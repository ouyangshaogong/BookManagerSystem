#ifndef __READER_CARD_MGR__SERVICE__
#define __READER_CARD_MGR__SERVICE__

#include "ReaderCardDaoImpl.h"
#include "TableReaderCard.h"
#include <pthread.h>

class ReaderCardManager
{

public:
        
    ReaderCardManager();
    ~ReaderCardManager();

    int AddReaderCard(TableReaderCard &readerCardInfo);
    int DeleteReaderCardByReaderID(const string &strReaderID);
    int DeleteAllReaderCard();

    //not update user_id and reader_id
    int UpdateReaderCardByField(const FieldCond &setFieldCond, const FieldCond &fieldCond);
    int UpdateReaderCardPasswd(const string &strReaderID, const string &strPasswd);
    //query condition just name and sex
    int QueryReaderCardByField(const FieldCond &fieldCond, list<TableReaderCard> &listBookInfo);
    int QueryReaderCardByReaderID(const string &strReaderID, TableReaderCard &readerCard);


private:
    ReaderCardDaoImpl* m_pReaderCardImpl;
};

#endif //__READER_CARD_MGR__SERVICE__