#ifndef __APPLICATION__
#define __APPLICATION__

#include "component.h"

class Application
{
public:
    virtual void StartApp(void *pApp) = 0;
};

#endif //__APPLICATION__