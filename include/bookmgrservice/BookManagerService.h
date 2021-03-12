#ifndef __BOOK_MANAGER_SERVICE__
#define __BOOK_MANAGER_SERVICE__

#include "BookInfoDaoImpl.h"
#include "LendListDaoImpl.h"
#include <pthread.h>

class BookManagerService
{

public:
    static BookManagerService* Instance();
    void DestoryInstance();

    int AddBook(TblBookInfo &bookInfo);
    int DeleteBookByBookID(const int nBookID);
    int DeleteBookAllBook();

    //not update book_id and class_id
    int UpdateBookInfoByBookID(const int nBookID, TblBookInfo &bookInfo);

    //query condition just bookname and auther
    int QueryBookByBookID(const int nBookID, TblBookInfo &bookInfo);


    int LendBook(const int nUserID, const int nBookID, const string &lendDate);
    int BackBook(const int nUserID, const int nBookID, const string &backDate);
    int DeleteLendByUserIDAndBookID(const int nUserID, const int nBookID);
    int DeleteAllLend();
    
    virtual ~BookManagerService();
private:
    BookManagerService();

private:
    static BookManagerService* m_instance;
    static pthread_mutex_t m_Mutex;
    BookInfoDaoImpl* m_pBookInfoImpl;
    LendListDaoImpl* m_pLendListImpl;
};

#endif //__BOOK_MANAGER_SERVICE__