#include "MyMsgQueue.h"

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

MyMsgQueue::MyMsgQueue()
:m_mMsgMutex(), m_mMsgCond(m_mMsgMutex)
{

}

uint8_t* MyMsgQueue::encode(MyProtoMsg* pMsg, uint32_t& length)
{
    uint8_t* pData = NULL; 
    Json::FastWriter fwriter; 

                            
    string bodyStr = fwriter.write(pMsg->Body);


    length = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->Header.nMsgLength = length; 
                         
    pData = new uint8_t[length];

    headEncode(pData, pMsg);
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData; 
}

//Э��ͷ��װ����
void MyMsgQueue::headEncode(uint8_t* pData, MyProtoMsg* pMsg)
{
 
    *pData = MY_PROTO_MAGIC;
    ++pData; 


    *pData = 1;
    ++pData; 

    *(uint16_t*)pData = pMsg->Header.nSendProc;
    pData += 2; 

    *(uint16_t*)pData = pMsg->Header.nRecvProc;
    pData += 2;
    
    *(uint32_t*)pData = pMsg->Header.nTaskMgrID;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnCmdMsg
    
    *(uint32_t*)pData = pMsg->Header.nTaskID;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnCmdMsg
    
    *(uint32_t*)pData = pMsg->Header.nMsgID;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnCmdMsg

    *(uint32_t*)pData = pMsg->Header.nCmdMsg;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnMsgType

    *(uint32_t*)pData = pMsg->Header.nMsgType;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnMsgRet

    *(uint32_t*)pData = pMsg->Header.nMsgRet;
    pData += 4; //��ǰ�ƶ������ֽڣ���������ϢnMsgLength

    //����Э��ͷ�����ֶ�
    *(uint32_t*)pData = pMsg->Header.nMsgLength;
}

void MyMsgQueue::init()
{
    m_mCurParserStatus = ON_PARSER_INIT;
}

void MyMsgQueue::clear()
{
    MyProtoMsg* pMsg = NULL;
    while (!m_mMsgQ.empty())
    {
        pMsg = m_mMsgQ.front();
        delete pMsg;
        m_mMsgQ.pop();
    }
}

bool MyMsgQueue::empty()
{
    return m_mMsgQ.empty();
}

void MyMsgQueue::pop()
{
    m_mMsgQ.pop();
}

void MyMsgQueue::push(MyProtoMsg *pMsg)
{
    m_mMsgQ.push(pMsg);
    m_mMsgCond.signal();
}


MyProtoMsg* MyMsgQueue::front()
{
    return m_mMsgQ.front();
}

void MyMsgQueue::HandleRequestMessage(MyProtoMsg* pMsg)
{
    //send to task
}

bool MyMsgQueue::GetMessage(MyProtoMsg* pMsg)
{
    while (true)
    {
        if(!empty())
        {
            pMsg = front();
            if(pMsg->Header.nMsgType == END_MSG_TYPE)
            {
                pop();
                break;
            }

            pop();
            return true;
        }
        else
        {
            m_mMsgCond.wait();
        }
        
    }
    
    return false;
}

void MyMsgQueue::DispatchMessage(MyProtoMsg* pMsg)
{
    if (pMsg->Header.nMsgType == REQUEST_MSG_TYPE)
    {
        HandleRequestMessage(pMsg);
    }
    else if(pMsg->Header.nMsgType == RESPONSE_MSG_TYPE)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)TaskMgrApp::StartMsgLoop>>MsgType Is Error!\n"));
        SendCmdMsgToServer(pMsg);
    }
}

bool MyMsgQueue::parser(void* data, size_t len)
{
    if (len <= 0)
        return false;

    uint32_t curLen = 0; 
    uint32_t parserLen = 0; 
    uint8_t* curData = NULL; 

    curData = (uint8_t*)data;

    while (len--)
    {
        m_mCurReserved.push_back(*curData);
        ++curData;
    }

    curLen = m_mCurReserved.size();
    curData = (uint8_t*)&m_mCurReserved[0];

    while (curLen > 0)
    {
        bool parserBreak = false;

  
        if (ON_PARSER_INIT == m_mCurParserStatus || ON_PARSER_BODY == m_mCurParserStatus) 
        {
            if (!parserHead(&curData, curLen, parserLen, parserBreak))
                return false;
            if (parserBreak)
                break; 
        }

        if (ON_PARSER_HEAD == m_mCurParserStatus)
        {
            if (!parserBody(&curData, curLen, parserLen, parserBreak))
                return false;
            if (parserBreak)
                break;
        }

        //����ɹ���������Ϣ���Ͱ���������Ϣ����
        if (ON_PARSER_BODY == m_mCurParserStatus)
        {
            MyProtoMsg* pMsg = NULL;
            pMsg = new MyProtoMsg;
            *pMsg = m_mCurMsg;
            m_mMsgQ.push(pMsg);
            ACE_DEBUG((LM_DEBUG, "(%P|%t|)MyProtoDecode::parser>>m_mMsgQ.size:%d\n", m_mMsgQ.size()));
        }

        if (parserLen > 0)
        {
            //ɾ���Ѿ��������������ֽ���
            m_mCurReserved.erase(m_mCurReserved.begin(), m_mCurReserved.begin() + parserLen);
        }
    }

    m_mMsgCond.signal();
    return true;
}

bool MyMsgQueue::parserHead(uint8_t** curData, uint32_t& curLen, uint32_t& parserLen, bool& parserBreak)
{
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; //��������û��ͷ������û�취��������������
        return true; //�������ݻ������õģ�����û�з��ֳ���������true���ȴ�һ�����ݵ��ˣ��ٽ���ͷ�������ڱ�־û�䣬һ�ỹ�ǽ���ͷ��
    }

    uint8_t* pData = *curData;

    //�������ֽ����У���������Э���ʽ���ݡ�������MyProtoMsg mCurMsg; //��ǰ�����е�Э����Ϣ��
    //��������ħ����
    m_mCurMsg.Header.nMagic = *pData;
    pData++;

    //�ж�У����Ϣ
    if (MY_PROTO_MAGIC != m_mCurMsg.Header.nMagic)
        return false; //���ݳ���

    //����������У��İ汾��
    m_mCurMsg.Header.nVersion = *pData;
    pData++;

    //�������ͽ��̺�
    m_mCurMsg.Header.nSendProc = *(uint16_t*)pData;
    pData += 2;

    //�������ս��̺�
    m_mCurMsg.Header.nRecvProc = *(uint16_t*)pData;
    pData += 2;

    m_mCurMsg.Header.nTaskMgrID = *(uint32_t*)pData;
    pData += 4;

    m_mCurMsg.Header.nTaskID = *(uint32_t*)pData;
    pData += 4;
    
    //����������ϢID
    m_mCurMsg.Header.nMsgID = *(uint32_t*)pData;
    pData += 4;

    //��������������
    m_mCurMsg.Header.nCmdMsg = *(uint32_t*)pData;
    pData += 4;

    //����������Ϣ����
    m_mCurMsg.Header.nMsgType = *(uint32_t*)pData;
    pData += 4;

    //����������Ϣ����ֵ
    m_mCurMsg.Header.nMsgRet = *(uint32_t*)pData;
    pData += 4;

    //����������Ϣ�峤��
    m_mCurMsg.Header.nMsgLength = *(uint32_t*)pData;

    //�ж����ݳ����Ƿ񳬹�ָ���Ĵ�С
    if (m_mCurMsg.Header.nMsgLength > MY_PROTO_MAX_SIZE)
        return false;

    //������ָ����ǰ�ƶ�����Ϣ��λ��,������Ϣͷ��С
    (*curData) += MY_PROTO_HEAD_SIZE;
    curLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    m_mCurParserStatus = ON_PARSER_HEAD;

    return true;
}

bool MyMsgQueue::parserBody(uint8_t** curData, uint32_t& curLen, uint32_t& parserLen, bool& parserBreak)
{
    uint32_t JsonSize = m_mCurMsg.Header.nMsgLength - MY_PROTO_HEAD_SIZE; //��Ϣ��Ĵ�С
    if (curLen < JsonSize)
    {
        parserBreak = true; //���ݻ�û����ȫ������ǻ�Ҫ�ȴ�һ�����ݵ��ˣ��ٽ�����Ϣ�塣���ڱ�־û�䣬һ�ỹ�ǽ�����Ϣ��
        return true;
    }

    Json::Reader reader; //Json������
    if (!reader.parse((char*)(*curData),
        (char*)((*curData) + JsonSize), m_mCurMsg.Body, false)) //false��ʾ����ע��
        return false; //�������ݵ�body��

                      //����ָ����ǰ�ƶ�
    (*curData) += JsonSize;
    curLen -= JsonSize;
    parserLen += JsonSize;
    m_mCurParserStatus = ON_PARSER_BODY;

    return true;
}

int MyMsgQueue::open()
{
    ACE_INET_Addr addr(PORT_NO, HOSTNAME);
    ACE_Time_Value timeout(5, 0);
    if (m_connector.connect(m_socketPeer, addr, &timeout) != 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::open>>connecetd fail\n"));
        return -1;
    }

    //ACE_Time_Value delayTime(5);
    //ACE_Time_Value interval(10);
    //ACE_Reactor::instance()->schedule_timer(this, 0, delayTime, delayTime);
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);
    //ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::WRITE_MASK);

    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapConnectorHandle::open>>connecetd entablish!\n"));
    return 0;
}

int MyMsgQueue::handle_timeout(const ACE_Time_Value &current_time, const void *act)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_timeout>>begin\n"));
    //static int i = 0;
    //iMapCmdMsg *pCmdMsg = new iMapCmdMsg;
    //pCmdMsg->SetMsgID(i + 1);
    //pCmdMsg->SetMsgType(REQUEST_MSG_TYPE);
    //pCmdMsg->SetBody("test");
    //cout << "iMapConnectorHandle::handle_timeout>>pCmdMsg:" << pCmdMsg << endl;
    //this->SendCmdMsgToQueue(pCmdMsg);
}

int MyMsgQueue::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //���ں˻�������ȡ��Ϣͷ
    uint8_t buf[BUFFER_MAX_LENGTH] = { 0 };
    while(true)
    {
        int recv_cnt = m_socketPeer.recv(buf, BUFFER_MAX_LENGTH);
        if (recv_cnt == 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
            return -1;
        }

        if (recv_cnt < 0)
        {
            ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
            break;
        }

        if (!parser(buf, recv_cnt))
        {
            cout << "parser msg failed!" << endl;
        }
        else
        {
            cout << "parser msg successful!" << endl;
        }
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::handle_input>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
    }
    

    
    return 0;
}

int MyMsgQueue::handle_close(ACE_HANDLE fd, ACE_Reactor_Mask mask)
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::handle_close>>\n"));
    ACE_Reactor::instance()->remove_handler(this, mask);
    m_socketPeer.close();
}


ACE_HANDLE MyMsgQueue::get_handle(void) const
{
    return m_socketPeer.get_handle();
}

void MyMsgQueue::SendCmdMsgToServer(MyProtoMsg *pMsg)
{
    uint8_t *pData = NULL;
    uint32_t nLength = 0;
    pData = encode(pMsg, nLength);

    int recv_cnt = this->m_socketPeer.send(pData, nLength);
    ACE_DEBUG((LM_DEBUG, "(%P|%t)MyMsgQueue::SendCmdMsgToServer>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
}