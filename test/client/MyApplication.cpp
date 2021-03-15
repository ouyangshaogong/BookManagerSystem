#include "MyApplication.h"


void MyApplication::StartApp()
{
    Controller controller = new DataController();
    RegisterCommand(CMD_MSG_DATA_COMMAND, controller);

    RegisterView(new DataView());

    RegisterProxy(new DataProxy());
}