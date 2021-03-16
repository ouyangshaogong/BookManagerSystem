#include "MyApplication.h"
#include "commonfunc.h"

extern CommonFunc g_commonFunc;

void MyApplication::StartApp(void *pApp)
{
    CommonFunc::Instance()->RegisterCommand(CMD_MSG_DATA_COMMAND, (void*)(new DataController()));

    CommonFunc::Instance()->RegisterView(new DataView());

    CommonFunc::Instance()->RegisterProxy(new DataProxy());
}