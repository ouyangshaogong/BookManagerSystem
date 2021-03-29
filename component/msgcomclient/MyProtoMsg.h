#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__

#include "commonace.h"
#include "json/json.h"
using namespace std;

const uint8_t MY_PROTO_MAGIC = 2; //Э��ħ����ͨ��ħ�����м򵥶Ա�У�飬Ҳ������֮ǰѧ��CRCУ���滻
const uint32_t MY_PROTO_MAX_SIZE = 5 * 1024 * 1024; //10MЭ�����������
const uint32_t MY_PROTO_HEAD_SIZE = 26; //Э��ͷ��С

typedef enum MyProtoParserStatus //Э�������״̬
{
    ON_PARSER_INIT = 0, //��ʼ״̬
    ON_PARSER_HEAD = 1, //����ͷ��
    ON_PARSER_BODY = 2, //��������
}MyProtoParserStatus;

struct MyProtoHeader
{
    uint8_t nMagic;
    uint8_t nVersion;
    uint16_t nSendProc;
    uint16_t nRecvProc;
    uint32_t nMsgID;
    uint32_t nCmdMsg;
    uint32_t nMsgType;
    
    uint32_t nMsgRet;
    //��Ϣͷ����Ϣ���ܳ���
    uint32_t nMsgLength;

    MyProtoHeader()
    {
        nMagic = 0;
        nVersion = 0;
        nSendProc = 0;
        nRecvProc = 0;
        nMsgID = 0;
        nCmdMsg = 0;
        nMsgType = 0;
        nMsgRet = 0;
        nMsgLength = 0;
    }

    void display()
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)MyProtoMsg>>nMagic:%d, nVersion:%d, nSendProc:%d, nRecvProc:%d, nMsgID:%d, nCmdMsg:%d, nMsgType:%d, nMsgRet:%d, nMsgLength:%d\n",
            nMagic, nVersion, nSendProc, nRecvProc, nMsgID, nCmdMsg, nMsgType, nMsgRet, nMsgLength));
    }
};

struct MyProtoMsg
{
    MyProtoHeader Header;
    Json::Value Body;
};

//Э���װ��
class MyProtoEncode
{
public:
    //Э����Ϣ���װ�����������pMsg����ֻ�в������ݣ�����JsonЭ���壬����ţ����Ƕ���Ϣ�������޸ĳ�����Ϣ����ʱ��Ҫ���±���Э��
    uint8_t* encode(MyProtoMsg* pMsg, uint32_t& len); //���س�����Ϣ�����ں���socket��������
private:
    //Э��ͷ��װ����
    void headEncode(uint8_t* pData, MyProtoMsg* pMsg);
};

//Э�������
class MyProtoDecode
{
private:
    MyProtoMsg m_mCurMsg; //��ǰ�����е�Э����Ϣ��
    queue<MyProtoMsg*> m_mMsgQ; //�����õ�Э����Ϣ����
    vector<uint8_t> m_mCurReserved; //δ�����������ֽ��������Ի�������û�н��������ݣ����ֽڣ�
    MyProtoParserStatus m_mCurParserStatus; //��ǰ���ܷ�����״̬
public:
    void init(); //��ʼ��Э�����״̬
    void clear(); //��ս����õ���Ϣ����
    bool empty(); //�жϽ����õ���Ϣ�����Ƿ�Ϊ��
    void pop();  //����һ����Ϣ

    MyProtoMsg* front(); //��ȡһ�������õ���Ϣ
    bool parser(void* data, size_t len); //�������ֽ����н�������Э����Ϣ��len�������е��ֽ������ȣ�ͨ��socket���Ի�ȡ
private:
    bool parserHead(uint8_t** curData, uint32_t& curLen,
        uint32_t& parserLen, bool& parserBreak); //���ڽ�����Ϣͷ
    bool parserBody(uint8_t** curData, uint32_t& curLen,
        uint32_t& parserLen, bool& parserBreak); //���ڽ�����Ϣ��
};

#endif
