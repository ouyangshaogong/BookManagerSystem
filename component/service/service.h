#ifndef __SERVICE__
#define __SERVICE__

class Service
{
public:
    virtual Initialize() = 0;
    virtual Finalize() = 0;
};

#endif