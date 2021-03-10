#ifndef __READER_CARD_MGR__SERVICE__
#define __READER_CARD_MGR__SERVICE__

#include "ReaderCardDaoImpl.h"
#include "TableReaderCard.h"
#include <pthread.h>

class ReaderCardMgrService
{

public:
    static ReaderCardMgrService* Instance();
    void DestoryInstance();

    int AddReaderCard(TableReaderCard &readerCardInfo);
    int DeleteReaderCardByReaderID(const string &strReaderID);
    int DeleteAllReaderCard();

    //not update user_id and reader_id
    int UpdateReaderCardByField(const FieldCond &setFieldCond, const FieldCond &fieldCond);

    //query condition just name and sex
    int QueryReaderCardByField(const FieldCond &fieldCond, list<TableReaderCard> &listBookInfo);

    virtual ~ReaderCardMgrService();
private:
    ReaderCardMgrService();

private:
    static ReaderCardMgrService* m_instance;
    static pthread_mutex_t m_Mutex;
    ReaderCardDaoImpl* m_pReaderCardImpl;
};

#endif //__READER_CARD_MGR__SERVICE__