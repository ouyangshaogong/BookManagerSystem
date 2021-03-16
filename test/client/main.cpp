#include "MyApplication.h"
#include "commonfunc.h"
//extern void SendNotifyCationToView(int nMsg, void *pCommonData);

void UserInputEvent()
{
    //send controller
    while(1)
    {
        string str;
        cin >> str;
        if (str == "TEST" || str == "CMD"
        || str == "MSG" || str == "USER")
        {
            CommonFunc::Instance()->SendNotifyCationToController(CMD_MSG_DATA_COMMAND);
        }
        else
        {
            cout << "you input error!" << endl;
        }
    }
    
}




int main()
{
    MyApplication myApp;

    void *p = NULL;
    myApp.StartApp(p);

    UserInputEvent();

    return 0;
}