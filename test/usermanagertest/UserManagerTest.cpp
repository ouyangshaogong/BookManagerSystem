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

int main()
{
    pUserMgrService = UserManagerService::Instance();
 
    TestDeleteAllUser(pUserMgrService);
    TestAddUser(pUserMgrService);
    TestDeleteByUserID(pUserMgrService);
    TestQueryUserByUserName(pUserMgrService);
    TestUpdateUserInfoByField(pUserMgrService);

    return 0;
}