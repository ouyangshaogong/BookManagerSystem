#include "common.h"
#include "UserManagerService.h"
#include <assert.h>
#include "CardUserNameMaker.h"

UserManagerService* pUserMgrService = NULL;
CardUserNameMaker g_CardUserNameMaker;

void TestAddUser(UserManagerService* pUserMgrService)
{
    //Test add book
    int count = 10;
    for (size_t i = 1; i <= count; i++)
    {
        TblUserInfo userInfo;
        userInfo.SetPhone("18229658596");
        userInfo.SetUserName(g_CardUserNameMaker.GenerateUserName());
        userInfo.SetSex("man");
        userInfo.SetBirth("19901020");
        userInfo.SetAddress("New York");
        userInfo.SetUserType(USERADMIN);

        assert(pUserMgrService->AddUser(userInfo) == OK);
    }
    cout << "TestAddUser Execute Success!" << endl;
}

void TestDeleteByUserID(UserManagerService* pUserMgrService)
{
    //Test DeleteBookByBookID
    int nUserID = 1;
    assert(pUserMgrService->DeleteUserByUserID(nUserID) == OK);
    cout << "TestDeleteByBookID Execute Success!" << endl;
}

void TestQueryUserByUserID(UserManagerService* pUserMgrService)
{
    //Test TestQueryUserByUserID
    int nUserID = 2;
    TblUserInfo userInfo;
    assert(pUserMgrService->QueryUserByUserID(nUserID, userInfo) == OK);
    cout << "TestQueryUserByUserID Execute Success!" << endl;
}

void TestDeleteAllUser(UserManagerService* pUserMgrService)
{
    //Test TestDeleteAllBook
    assert(pUserMgrService->DeleteAllUser() == OK);
    cout << "TestDeleteAllBook Execute Success!" << endl;
}


void TestUpdateUserInfoByUserID(UserManagerService* pUserMgrService)
{
    //Test TestDeleteAllBook
    int nUserID = 3;
    TblUserInfo userInfo;
    userInfo.SetPhone("18229658596");
    userInfo.SetUserName("James");
    userInfo.SetSex("man");
    userInfo.SetBirth("19901020");
    assert(pUserMgrService->UpdateUserInfoByUserID(nUserID, userInfo) == OK);
    cout << "TestUpdateUserInfoByUserID Execute Success!" << endl;
}

void TestQueryReaderCardByReaderID(UserManagerService* pUserMgrService)
{
    int nReaderID = 3;
    TableReaderCard readerCard;
    assert(pUserMgrService->QueryReaderCardByReaderID(nReaderID, readerCard) == OK);
    cout << "TestQueryReaderCardByReaderID Execute Success!" << endl;
}

void TestUpdateUserPasswd(UserManagerService* pUserMgrService)
{
    string strUserName = "SX000004";
    string strPasswd = "654321";
    assert(pUserMgrService->UpdateUserPasswd(strUserName, strPasswd) == OK);
    cout << "TestUpdateUserPasswd Execute Success!" << endl;
}

void TestLogin(UserManagerService* pUserMgrService)
{
    string strUserName = "James";
    string strPasswd = "123456";
    assert(pUserMgrService->Login(strUserName, strPasswd) == OK);
    cout << "TestLogin Execute Success!" << endl;
}

int main()
{
    cout << "------UserManagerService Test Begin------" << endl;
    pUserMgrService = UserManagerService::Instance();
 
    TestDeleteAllUser(pUserMgrService);
    TestAddUser(pUserMgrService);
    TestDeleteByUserID(pUserMgrService);
    TestUpdateUserInfoByUserID(pUserMgrService);
    TestUpdateUserInfoByUserID(pUserMgrService);
    TestQueryReaderCardByReaderID(pUserMgrService);
    TestUpdateUserPasswd(pUserMgrService);
    TestLogin(pUserMgrService);
    cout << "------UserManagerService Test End------" << endl << endl;

    return 0;
}