#ifndef __TASK__
#define __TASK__

#include "commonace.h"
#include "MyProtoMsg.h"


class Task: public ACE_Task<ACE_MT_SYNCH>
{
public:
    Task();
    virtual ~Task();

    virtual int open(int nThreadNum);
    virtual int close();
    virtual int svc();

    virtual void process(MyProtoMsg *pInMsg, MyProtoMsg *pOutMsg);
private:
    MyProtoDecode m_protoDecode;
    MyProtoEncode m_protoEncode;
};

#endif
