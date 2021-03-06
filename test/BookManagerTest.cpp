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
        bookInfo.SetSerNum(5000);

        assert(pBookMgrService->AddBook(bookInfo) == OK);
    }
}

void TestDeleteByBookID(BookManagerService* pBookMgrService)
{
    //Test DeleteBookByBookID
    string strBookID = "1";
    assert(pBookMgrService->DeleteBookByBookID(strBookID) == OK);
}

void TestQueryBookByBookName(BookManagerService* pBookMgrService)
{
    //Test QueryBookByBookName
    string strBookName = "The Greate Gatsby";
    list<TblBookInfo> listBookInfo;
    assert(pBookMgrService->QueryBookByName(strBookName, listBookInfo) == OK);
}


int main()
{
    pBookMgrService = BookManagerService::Instance();
 
    TestAddBook(pBookMgrService);
    TestDeleteByBookID(pBookMgrService);
    TestQueryBookByBookName(pBookMgrService);

    return 0;
}