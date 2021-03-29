#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__

#include "commonace.h"
#include "json/json.h"
using namespace std;

const uint8_t MY_PROTO_MAGIC = 2; //协议魔数：通过魔数进行简单对比校验，也可以像之前学的CRC校验替换
const uint32_t MY_PROTO_MAX_SIZE = 5 * 1024 * 1024; //10M协议中数据最大
const uint32_t MY_PROTO_HEAD_SIZE = 26; //协议头大小

typedef enum MyProtoParserStatus //协议解析的状态
{
    ON_PARSER_INIT = 0, //初始状态
    ON_PARSER_HEAD = 1, //解析头部
    ON_PARSER_BODY = 2, //解析数据
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
    //消息头和消息体总长度
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

//协议封装类
class MyProtoEncode
{
public:
    //协议消息体封装函数：传入的pMsg里面只有部分数据，比如Json协议体，服务号，我们对消息编码后会修改长度信息，这时需要重新编码协议
    uint8_t* encode(MyProtoMsg* pMsg, uint32_t& len); //返回长度信息，用于后面socket发送数据
private:
    //协议头封装函数
    void headEncode(uint8_t* pData, MyProtoMsg* pMsg);
};

//协议解析类
class MyProtoDecode
{
private:
    MyProtoMsg m_mCurMsg; //当前解析中的协议消息体
    queue<MyProtoMsg*> m_mMsgQ; //解析好的协议消息队列
    vector<uint8_t> m_mCurReserved; //未解析的网络字节流，可以缓存所有没有解析的数据（按字节）
    MyProtoParserStatus m_mCurParserStatus; //当前接受方解析状态
public:
    void init(); //初始化协议解析状态
    void clear(); //清空解析好的消息队列
    bool empty(); //判断解析好的消息队列是否为空
    void pop();  //出队一个消息

    MyProtoMsg* front(); //获取一个解析好的消息
    bool parser(void* data, size_t len); //从网络字节流中解析出来协议消息，len是网络中的字节流长度，通过socket可以获取
private:
    bool parserHead(uint8_t** curData, uint32_t& curLen,
        uint32_t& parserLen, bool& parserBreak); //用于解析消息头
    bool parserBody(uint8_t** curData, uint32_t& curLen,
        uint32_t& parserLen, bool& parserBreak); //用于解析消息体
};

#endif
