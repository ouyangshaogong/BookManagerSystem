#include "common.h"
#include "UserManagerService.h"
#include "ReaderCardMgrService.h"
#include <assert.h>

UserManagerService* pUserMgrService = NULL;
ReaderCardMgrService* pReaderCardMgrService = NULL;

void TestAddUser(UserManagerService* pUserMgrService)
{
    //Test add book
    int count = 10;
    for (size_t i = 1; i <= count; i++)
    {
        TblUserInfo userInfo;
        userInfo.SetUserID(i);
        userInfo.SetReaderID(i);
        userInfo.SetPhone("18229658596");
        userInfo.SetUserName("James");
        userInfo.SetSex("man");
        userInfo.SetBirth("19901020");
        userInfo.SetAddress("New York");
        userInfo.SetUserType(1);

        assert(pUserMgrService->AddUser(userInfo) == OK);
    }
    cout << "TestAddUser Execute Success!" << endl;
}

void TestDeleteByUserID(UserManagerService* pUserMgrService)
{
    //Test DeleteBookByBookID
    string strUserID = "1";
    assert(pUserMgrService->DeleteUserByUserID(strUserID) == OK);
    cout << "TestDeleteByBookID Execute Success!" << endl;
}

void TestQueryUserByUserName(UserManagerService* pUserMgrService)
{
    //Test QueryBookByBookName
    FieldCond fieldCond;

    fieldCond.fieldName = "name";
    fieldCond.fieldValue = "The Greate Gatsby";

    list<TblUserInfo> listBookInfo;
    assert(pUserMgrService->QueryUserByField(fieldCond, listBookInfo) == OK);
    cout << "TestQueryBookByBookName Execute Success!" << endl;
}

void TestDeleteAllUser(UserManagerService* pUserMgrService)
{
    //Test TestDeleteAllBook
    assert(pUserMgrService->DeleteAllUser() == OK);
    cout << "TestDeleteAllBook Execute Success!" << endl;
}


void TestUpdateUserInfoByField(UserManagerService* pUserMgrService)
{
    //Test TestDeleteAllBook
    vector<FieldCond> vecFieldCond;
    FieldCond fieldCond;
    fieldCond.fieldName = "user_id";
    fieldCond.fieldValue = "2";

    FieldCond tmpFieldCond;
    tmpFieldCond.fieldName = "name";
    tmpFieldCond.fieldValue = "Bob";
    vecFieldCond.push_back(tmpFieldCond);

    tmpFieldCond.fieldName = "sex";
    tmpFieldCond.fieldValue = "woman";
    vecFieldCond.push_back(tmpFieldCond);

    assert(pUserMgrService->UpdateUserInfoByField(vecFieldCond, fieldCond) == OK);
    cout << "TestUpdateBookInfoByField Execute Success!" << endl;
}


void TestAddReaderCard(ReaderCardMgrService* pReaderCardMgrService)
{
    //Test add book
    int count = 10;
    for (size_t i = 1; i <= count; i++)
    {
        TableReaderCard readerCard;
        readerCard.SetReaderID(i);
        readerCard.SetUserName("user");
        readerCard.SetPasswd("123456");

        assert(pReaderCardMgrService->AddReaderCard(readerCard) == OK);
    }
    cout << "TestAddReaderCard Execute Success!" << endl;
}

void TestDeleteByReaderID(ReaderCardMgrService* pReaderCardMgrService)
{
    //Test TestDeleteByReaderID
    string strReaderID = "1";
    assert(pReaderCardMgrService->DeleteReaderCardByReaderID(strReaderID) == OK);
    cout << "TestDeleteByReaderID Execute Success!" << endl;
}

void TestQueryReaderCardByUserName(ReaderCardMgrService* pReaderCardMgrService)
{
    //Test TestQueryReaderCardByUserName
    FieldCond fieldCond;

    fieldCond.fieldName = "reader_id";
    fieldCond.fieldValue = "2";

    list<TableReaderCard> listReaderCard;
    assert(pReaderCardMgrService->QueryReaderCardByField(fieldCond, listReaderCard) == OK);
    cout << "TestQueryReaderCardByUserName Execute Success!" << endl;
}

void TestDeleteAllReaderCard(ReaderCardMgrService* pReaderCardMgrService)
{
    //Test TestDeleteAllReaderCard
    assert(pReaderCardMgrService->DeleteAllReaderCard() == OK);
    cout << "TestDeleteAllReaderCard Execute Success!" << endl;
}


void TestUpdateReaderCardByField(ReaderCardMgrService* pReaderCardMgrService)
{
    //Test TestUUpdateReaderCardByField
    FieldCond fieldCond;
    fieldCond.fieldName = "reader_id";
    fieldCond.fieldValue = "2";

    FieldCond setFieldCond;
    setFieldCond.fieldName = "UserName";
    setFieldCond.fieldValue = "Bob";


    assert(pReaderCardMgrService->UpdateReaderCardByField(setFieldCond, fieldCond) == OK);
    cout << "TestUUpdateReaderCardByField Execute Success!" << endl;
}

int main()
{
    cout << "------UserManagerService Test Begin------" << endl;
    pUserMgrService = UserManagerService::Instance();
 
    TestDeleteAllUser(pUserMgrService);
    TestAddUser(pUserMgrService);
    TestDeleteByUserID(pUserMgrService);
    TestQueryUserByUserName(pUserMgrService);
    TestUpdateUserInfoByField(pUserMgrService);
    cout << "------UserManagerService Test End------" << endl << endl;

    cout << "------ReaderCardMgrService Test Begin------" << endl;
    pReaderCardMgrService = ReaderCardMgrService::Instance();

    TestDeleteAllReaderCard(pReaderCardMgrService);
    TestAddReaderCard(pReaderCardMgrService);
    TestDeleteByReaderID(pReaderCardMgrService);
    TestQueryReaderCardByUserName(pReaderCardMgrService);
    TestUpdateReaderCardByField(pReaderCardMgrService);
    cout << "------ReaderCardMgrService Test End------" << endl << endl;

    return 0;
}