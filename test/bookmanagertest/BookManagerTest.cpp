#include "common.h"
#include "BookManagerService.h"
#include <assert.h>

BookManagerService* pBookMgrService = NULL;

void TestAddBook(BookManagerService* pBookMgrService)
{
    //Test add book
    int count = 10;
    for (size_t i = 1; i <= count; i++)
    {
        TblBookInfo bookInfo;
        bookInfo.SetBookID(i);
        bookInfo.SetClassID(i);
        bookInfo.SetAuther("Bob");
        bookInfo.SetIntroduction("Introduction");
        bookInfo.SetISBN("ISBN");
        bookInfo.SetLanguage("CN");
        bookInfo.SetName("The Greate Gatsby");
        bookInfo.SetNumber(10);
        bookInfo.SetPrice(50);
        bookInfo.SetPubDate("19901020");
        bookInfo.SetPublish("New York");

        assert(pBookMgrService->AddBook(bookInfo) == OK);
    }
    cout << "TestAddBook Execute Success!" << endl;
}

void TestDeleteByBookID(BookManagerService* pBookMgrService)
{
    //Test DeleteBookByBookID
    string strBookID = "1";
    assert(pBookMgrService->DeleteBookByBookID(strBookID) == OK);
    cout << "TestDeleteByBookID Execute Success!" << endl;
}

void TestQueryBookByBookID(BookManagerService* pBookMgrService)
{
    //Test QueryBookByBookName
    int nBookID = 6;
    TblBookInfo bookInfo;
    bookInfo.SetAuther("Gasby");
    assert(pBookMgrService->QueryBookByBookID(nBookID, bookInfo) == OK);
    cout << "TestQueryBookByBookName Execute Success!" << endl;
}

void TestDeleteAllBook(BookManagerService* pBookMgrService)
{
    //Test TestDeleteAllBook
    assert(pBookMgrService->DeleteBookAllBook() == OK);
    cout << "TestDeleteAllBook Execute Success!" << endl;
}


void TestUpdateBookInfoByBookID(BookManagerService* pBookMgrService)
{
    //Test TestDeleteAllBook

    int nBookID = 5;
    TblBookInfo bookInfo;
    assert(pBookMgrService->UpdateBookInfoByBookID(nBookID, bookInfo) == OK);
    cout << "TestUpdateBookInfoByField Execute Success!" << endl;
}

int main()
{
    pBookMgrService = BookManagerService::Instance();
 
    TestDeleteAllBook(pBookMgrService);
    TestAddBook(pBookMgrService);
    TestDeleteByBookID(pBookMgrService);
    TestQueryBookByBookID(pBookMgrService);
    TestUpdateBookInfoByBookID(pBookMgrService);

    return 0;
}