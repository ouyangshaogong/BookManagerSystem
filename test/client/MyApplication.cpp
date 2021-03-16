#include "MyApplication.h"
#include "commonfunc.h"

void MyApplication::StartApp()
{
    RegisterCommand(CMD_MSG_DATA_COMMAND, (void*)(new DataController()));

    RegisterView(new DataView());

    RegisterProxy(new DataProxy());
}