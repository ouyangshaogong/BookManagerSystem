#include "myapplication.h"
#include "datacommonfunc.h"

void MyApplication::StartApp(void *pApp)
{
    DataCommonFunc::Instance()->RegisterCommand(CMD_MSG_DATA_COMMAND, (void*)(new DataController()));

    DataCommonFunc::Instance()->RegisterView((MainWindow*)pApp);

    DataCommonFunc::Instance()->RegisterProxy(new DataProxy());
}
