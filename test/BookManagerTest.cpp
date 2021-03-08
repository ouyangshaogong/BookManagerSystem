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

void TestQueryBookByBookName(BookManagerService* pBookMgrService)
{
    //Test QueryBookByBookName
    FieldCond fieldCond;

    fieldCond.fieldName = "name";
    fieldCond.fieldValue = "The Greate Gatsby";

    list<TblBookInfo> listBookInfo;
    assert(pBookMgrService->QueryBookByField(fieldCond, listBookInfo) == OK);
    cout << "TestQueryBookByBookName Execute Success!" << endl;
}

void TestDeleteAllBook(BookManagerService* pBookMgrService)
{
    //Test TestDeleteAllBook
    assert(pBookMgrService->DeleteBookAllBook() == OK);
    cout << "TestDeleteAllBook Execute Success!" << endl;
}


void TestUpdateBookInfoByField(BookManagerService* pBookMgrService)
{
    //Test TestDeleteAllBook
    vector<FieldCond> vecFieldCond;
    FieldCond fieldCond;
    fieldCond.fieldName = "book_id";
    fieldCond.fieldValue = "2";

    FieldCond tmpFieldCond;
    tmpFieldCond.fieldName = "publish";
    tmpFieldCond.fieldValue = "shanghai";
    vecFieldCond.push_back(tmpFieldCond);

    tmpFieldCond.fieldName = "author";
    tmpFieldCond.fieldValue = "James";
    vecFieldCond.push_back(tmpFieldCond);

    assert(pBookMgrService->UpdateBookInfoByField(vecFieldCond, fieldCond) == OK);
    cout << "TestUpdateBookInfoByField Execute Success!" << endl;
}

int main()
{
    pBookMgrService = BookManagerService::Instance();
 
    TestDeleteAllBook(pBookMgrService);
    TestAddBook(pBookMgrService);
    TestDeleteByBookID(pBookMgrService);
    TestQueryBookByBookName(pBookMgrService);
    TestUpdateBookInfoByField(pBookMgrService);

    return 0;
}