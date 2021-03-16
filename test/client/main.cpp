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
            SendNotifyCationToController(CMD_MSG_DATA_COMMAND);
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
    myApp.StartApp();

    UserInputEvent();

    return 0;
}