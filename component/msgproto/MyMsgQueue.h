#ifndef __MY_MSG_QUEUE__
#define __MY_MSG_QUEUE__

#include "MyProtoMsg.h"
#include "commonace.h"
#include "json/json.h"
#include "TaskMgrApp.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

class MyMsgQueue
{
public:
    
    virtual ~MyMsgQueue();
    static MyMsgQueue* Instance(TaskMgrApp *pTaskMgrApp);
    static MyMsgQueue* Instance();
    void init();  
    void clear(); 
    bool empty();
    void pop();

    void push(MyProtoMsg *);
    MyProtoMsg *front(); 

    void GetSockPeer(string strIP, ACE_SOCK_Stream *pPeer);
    void DeleteSockPeer(string strIP);

    bool GetMessage(MyProtoMsg* pMsg);
    virtual void DispatchMessage(MyProtoMsg* pMsg);
    
    

    bool parser(void *data, size_t len); 
    uint8_t *encode(MyProtoMsg *pMsg, uint32_t &len);
    void headEncode(uint8_t *pData, MyProtoMsg *pMsg);

    bool parserHead(uint8_t **curData, uint32_t &curLen,
                    uint32_t &parserLen, bool &parserBreak);
    bool parserBody(uint8_t **curData, uint32_t &curLen,
                    uint32_t &parserLen, bool &parserBreak);
    
private:
    MyMsgQueue(TaskMgrApp *pTaskMgrApp);
    MyMsgQueue();

private:
    
    MyProtoMsg m_mCurMsg;                   
    queue<MyProtoMsg *> m_mMsgQ;
    vector<uint8_t> m_mCurReserved;         
    MyProtoParserStatus m_mCurParserStatus;
    ACE_Thread_Mutex m_mMsgMutex;
    ACE_Condition<ACE_Thread_Mutex> m_mMsgCond;

    map<string, ACE_SOCK_Stream*> m_IPMapSockPeer;
    TaskMgrApp *m_pTaskMgrApp;

    static ACE_Thread_Mutex m_mutex;
    static MyMsgQueue *m_instance;
    
};

#endif