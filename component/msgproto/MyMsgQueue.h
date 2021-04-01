#ifndef __MY_MSG_QUEUE__
#define __MY_MSG_QUEUE__

#include "MyProtoMsg.h"
#include "commonace.h"
#include "json/json.h"

#define PORT_NO 5000
#define HOSTNAME "127.0.0.1"

class MyMsgQueue: public ACE_Event_Handler
{
private:
    MyProtoMsg m_mCurMsg;                   
    queue<MyProtoMsg *> m_mMsgQ;
    vector<uint8_t> m_mCurReserved;         
    MyProtoParserStatus m_mCurParserStatus;
    ACE_Thread_Mutex m_mMsgMutex;
    ACE_Condition<ACE_Thread_Mutex> m_mMsgCond;

    ACE_SOCK_Connector m_connector;
    ACE_SOCK_Stream m_socketPeer;
public:
    MyMsgQueue();
    void init();  
    void clear(); 
    bool empty();
    void pop();

    void push(MyProtoMsg *);
    MyProtoMsg *front(); 

    bool GetMessage(MyProtoMsg* pMsg);
    void DispatchMessage(MyProtoMsg* pMsg);
    virtual void HandleRequestMessage(MyProtoMsg* pMsg);

    bool parser(void *data, size_t len); 
    uint8_t *encode(MyProtoMsg *pMsg, uint32_t &len);

    int open();

    int handle_input(ACE_HANDLE fd);

    int handle_timeout(const ACE_Time_Value &current_time, const void *act = 0);

    int handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask);

    ACE_HANDLE get_handle(void) const;

    void SendCmdMsgToServer(MyProtoMsg *pMsg);

private:
    bool parserHead(uint8_t **curData, uint32_t &curLen,
                    uint32_t &parserLen, bool &parserBreak); //���ڽ�����Ϣͷ
    bool parserBody(uint8_t **curData, uint32_t &curLen,
                    uint32_t &parserLen, bool &parserBreak); //���ڽ�����Ϣ��

    void headEncode(uint8_t *pData, MyProtoMsg *pMsg);
};

#endif