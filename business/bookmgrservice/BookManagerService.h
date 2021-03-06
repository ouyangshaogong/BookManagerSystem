#ifndef __BOOK_MANAGER_SERVICE__
#define __BOOK_MANAGER_SERVICE__

#include "BookInfoDaoImpl.h"
#include <pthread.h>

class BookManagerService
{

public:
    static BookManagerService* Instance();
    void DestoryInstance();

    int AddBook(TblBookInfo &bookInfo);
    int DeleteBookByBookID(const string &strBookID);
    int UpdateBook();
    int QueryBookByName(const string &strBookName, list<TblBookInfo> &listBookInfo);

    virtual ~BookManagerService();
private:
    BookManagerService();

private:
    static BookManagerService* m_instance;
    static pthread_mutex_t m_Mutex;
    BookInfoDaoImpl* m_pBookInfoImpl;
};

#endif //__BOOK_MANAGER_SERVICE__