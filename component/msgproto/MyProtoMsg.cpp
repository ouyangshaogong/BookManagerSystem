#include "MyProtoMsg.h"

uint8_t* MyMsgQueue::encode(MyProtoMsg* pMsg, uint32_t& length)
{
    uint8_t* pData = NULL; //用于开辟新的空间，存放编码后的数据
    Json::FastWriter fwriter; //读取Json::Value数据，转换为可以写入文件的字符串

                              //协议Json体序列化
    string bodyStr = fwriter.write(pMsg->Body);

    //计算消息序列化以后的新长度
    length = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->Header.nMsgLength = length; //一会编码协议头部时，会用到
                          //申请一块新的空间，用于保存消息（这里可以不用，直接使用原来空间也可以）
    pData = new uint8_t[length];
    //编码协议头
    headEncode(pData, pMsg); //函数内部没有通过二级指针修改pData的数据，修改的是临时数据打包协议体
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData; //返回消息首部地址
}

//协议头封装函数
void MyMsgQueue::headEncode(uint8_t* pData, MyProtoMsg* pMsg)
{
    //设置协议头魔术字
    *pData = MY_PROTO_MAGIC;
    ++pData; //向前移动一个字节位置到版本

    //设置协议头版本
    *pData = 1;
    ++pData; //向前移动一个字节位置，到发送进程ID（16位大小）

    *(uint16_t*)pData = pMsg->Header.nSendProc;
    pData += 2; //向前移动两个字节，到接收进程ID

    *(uint16_t*)pData = pMsg->Header.nRecvProc;
    pData += 2; //向前移动两个字节，到消息ID

    *(uint32_t*)pData = pMsg->Header.nMsgID;
    pData += 4; //向前移动两个字节，到命令消息nCmdMsg

    *(uint32_t*)pData = pMsg->Header.nCmdMsg;
    pData += 4; //向前移动两个字节，到命令消息nMsgType

    *(uint32_t*)pData = pMsg->Header.nMsgType;
    pData += 4; //向前移动两个字节，到命令消息nMsgRet

    *(uint32_t*)pData = pMsg->Header.nMsgRet;
    pData += 4; //向前移动两个字节，到命令消息nMsgLength

    //设置协议头长度字段
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

    uint32_t curLen = 0; //用于保存未解析的网络字节流长度（是对vector)
    uint32_t parserLen = 0; //保存vector中已经被解析完成的字节流，一会用于清除vector中数据
    uint8_t* curData = NULL; //指向data,当前未解析的网络字节流

    curData = (uint8_t*)data;

    //将当前要解析的网络字节流写入到vector中    
    while (len--)
    {
        m_mCurReserved.push_back(*curData);
        ++curData;
    }

    curLen = m_mCurReserved.size();
    curData = (uint8_t*)&m_mCurReserved[0]; //获取数据首地址

    //只要还有未解析的网络字节流，就持续解析
    while (curLen > 0)
    {
        bool parserBreak = false;

        //解析头部 注意：标识很有用，当数据没有完全达到，会等待下一次接受数据以后继续解析头部
        if (ON_PARSER_INIT == m_mCurParserStatus ||
            ON_PARSER_BODY == m_mCurParserStatus) //可以进行头部解析
        {
            if (!parserHead(&curData, curLen, parserLen, parserBreak))
                return false;
            if (parserBreak)
                break; //退出循环，等待下一次数据到达，一起解析头部
        }

        //解析完成协议头，开始解析协议体
        if (ON_PARSER_HEAD == m_mCurParserStatus)
        {
            if (!parserBody(&curData, curLen, parserLen, parserBreak))
                return false;
            if (parserBreak)
                break;
        }

        //如果成功解析了消息，就把他放入消息队列
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
            //删除已经被解析的网络字节流
            m_mCurReserved.erase(m_mCurReserved.begin(), m_mCurReserved.begin() + parserLen);
        }
    }

    return true;
}

bool MyMsgQueue::parserHead(uint8_t** curData, uint32_t& curLen, uint32_t& parserLen, bool& parserBreak)
{
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; //由于数据没有头部长，没办法解析，跳出即可
        return true; //但是数据还是有用的，我们没有发现出错，返回true。等待一会数据到了，再解析头部。由于标志没变，一会还是解析头部
    }

    uint8_t* pData = *curData;

    //从网络字节流中，解析出来协议格式数据。保存在MyProtoMsg mCurMsg; //当前解析中的协议消息体
    //解析出来魔术字
    m_mCurMsg.Header.nMagic = *pData;
    pData++;

    //判断校验信息
    if (MY_PROTO_MAGIC != m_mCurMsg.Header.nMagic)
        return false; //数据出错

    //解析出用于校验的版本号
    m_mCurMsg.Header.nVersion = *pData;
    pData++;

    //解析发送进程号
    m_mCurMsg.Header.nSendProc = *(uint16_t*)pData;
    pData += 2;

    //解析接收进程号
    m_mCurMsg.Header.nRecvProc = *(uint16_t*)pData;
    pData += 2;

    //解析接收消息ID
    m_mCurMsg.Header.nMsgID = *(uint32_t*)pData;
    pData += 4;

    //解析接收命令字
    m_mCurMsg.Header.nCmdMsg = *(uint32_t*)pData;
    pData += 4;

    //解析接收消息类型
    m_mCurMsg.Header.nMsgType = *(uint32_t*)pData;
    pData += 4;

    //解析接收消息返回值
    m_mCurMsg.Header.nMsgRet = *(uint32_t*)pData;
    pData += 4;

    //解析接收消息体长度
    m_mCurMsg.Header.nMsgLength = *(uint32_t*)pData;

    //判断数据长度是否超过指定的大小
    if (m_mCurMsg.Header.nMsgLength > MY_PROTO_MAX_SIZE)
        return false;

    //将解析指针向前移动到消息体位置,跳过消息头大小
    (*curData) += MY_PROTO_HEAD_SIZE;
    curLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    m_mCurParserStatus = ON_PARSER_HEAD;

    return true;
}

bool MyMsgQueue::parserBody(uint8_t** curData, uint32_t& curLen, uint32_t& parserLen, bool& parserBreak)
{
    uint32_t JsonSize = m_mCurMsg.Header.nMsgLength - MY_PROTO_HEAD_SIZE; //消息体的大小
    if (curLen < JsonSize)
    {
        parserBreak = true; //数据还没有完全到达，我们还要等待一会数据到了，再解析消息体。由于标志没变，一会还是解析消息体
        return true;
    }

    Json::Reader reader; //Json解析类
    if (!reader.parse((char*)(*curData),
        (char*)((*curData) + JsonSize), m_mCurMsg.Body, false)) //false表示丢弃注释
        return false; //解析数据到body中

                      //数据指针向前移动
    (*curData) += JsonSize;
    curLen -= JsonSize;
    parserLen += JsonSize;
    m_mCurParserStatus = ON_PARSER_BODY;

    return true;
}