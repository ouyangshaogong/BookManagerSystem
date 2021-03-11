#include "common.h"
#include "UserManagerService.h"
#include <assert.h>

UserManagerService* pUserMgrService = NULL;

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
    int nUserID = 1;
    assert(pUserMgrService->DeleteUserByUserID(nUserID) == OK);
    cout << "TestDeleteByBookID Execute Success!" << endl;
}

void TestQueryUserByUserName(UserManagerService* pUserMgrService)
{
    //Test QueryBookByBookName
    int nUserID = 2;
    TblUserInfo userInfo;
    userInfo.SetUserName("Bob");
    assert(pUserMgrService->QueryUserByUserID(nUserID, userInfo) == OK);
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
    int nUserID = 3;
    TblUserInfo userInfo;
    userInfo.SetPhone("18229658596");
    userInfo.SetUserName("James");
    userInfo.SetSex("man");
    userInfo.SetBirth("19901020");
    assert(pUserMgrService->UpdateUserInfoByUserID(nUserID, userInfo) == OK);
    cout << "TestUpdateBookInfoByField Execute Success!" << endl;
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

    return 0;
}