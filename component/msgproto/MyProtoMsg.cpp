#include "MyProtoMsg.h"

uint8_t* MyMsgQueue::encode(MyProtoMsg* pMsg, uint32_t& length)
{
    uint8_t* pData = NULL; //���ڿ����µĿռ䣬��ű���������
    Json::FastWriter fwriter; //��ȡJson::Value���ݣ�ת��Ϊ����д���ļ����ַ���

                              //Э��Json�����л�
    string bodyStr = fwriter.write(pMsg->Body);

    //������Ϣ���л��Ժ���³���
    length = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->Header.nMsgLength = length; //һ�����Э��ͷ��ʱ�����õ�
                          //����һ���µĿռ䣬���ڱ�����Ϣ��������Բ��ã�ֱ��ʹ��ԭ���ռ�Ҳ���ԣ�
    pData = new uint8_t[length];
    //����Э��ͷ
    headEncode(pData, pMsg); //�����ڲ�û��ͨ������ָ���޸�pData�����ݣ��޸ĵ�����ʱ���ݴ��Э����
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData; //������Ϣ�ײ���ַ
}

//Э��ͷ��װ����
void MyMsgQueue::headEncode(uint8_t* pData, MyProtoMsg* pMsg)
{
    //����Э��ͷħ����
    *pData = MY_PROTO_MAGIC;
    ++pData; //��ǰ�ƶ�һ���ֽ�λ�õ��汾

    //����Э��ͷ�汾
    *pData = 1;
    ++pData; //��ǰ�ƶ�һ���ֽ�λ�ã������ͽ���ID��16λ��С��

    *(uint16_t*)pData = pMsg->Header.nSendProc;
    pData += 2; //��ǰ�ƶ������ֽڣ������ս���ID

    *(uint16_t*)pData = pMsg->Header.nRecvProc;
    pData += 2; //��ǰ�ƶ������ֽڣ�����ϢID

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


MyProtoMsg* MyMsgQueue::front()
{
    return m_mMsgQ.front();
}

void MyMsgQueue::push(MyProtoMsg *pMsg)
{
    m_mMsgQ.push(pMsg);
}

bool MyMsgQueue::parser(void* data, size_t len)
{
    if (len <= 0)
        return false;

    uint32_t curLen = 0; //���ڱ���δ�����������ֽ������ȣ��Ƕ�vector)
    uint32_t parserLen = 0; //����vector���Ѿ���������ɵ��ֽ�����һ���������vector������
    uint8_t* curData = NULL; //ָ��data,��ǰδ�����������ֽ���

    curData = (uint8_t*)data;

    //����ǰҪ�����������ֽ���д�뵽vector��    
    while (len--)
    {
        m_mCurReserved.push_back(*curData);
        ++curData;
    }

    curLen = m_mCurReserved.size();
    curData = (uint8_t*)&m_mCurReserved[0]; //��ȡ�����׵�ַ

    //ֻҪ����δ�����������ֽ������ͳ�������
    while (curLen > 0)
    {
        bool parserBreak = false;

        //����ͷ�� ע�⣺��ʶ�����ã�������û����ȫ�ﵽ����ȴ���һ�ν��������Ժ��������ͷ��
        if (ON_PARSER_INIT == m_mCurParserStatus ||
            ON_PARSER_BODY == m_mCurParserStatus) //���Խ���ͷ������
        {
            if (!parserHead(&curData, curLen, parserLen, parserBreak))
                return false;
            if (parserBreak)
                break; //�˳�ѭ�����ȴ���һ�����ݵ��һ�����ͷ��
        }

        //�������Э��ͷ����ʼ����Э����
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

    return true;
}

bool MyMsgQueue::parserHead(uint8_t** curData, uint32_t& curLen, uint32_t& parserLen, bool& parserBreak)
{
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; //��������û��ͷ������û�취��������������
        return true; //�������ݻ������õģ�����û�з��ֳ�������true���ȴ�һ�����ݵ��ˣ��ٽ���ͷ�������ڱ�־û�䣬һ�ỹ�ǽ���ͷ��
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