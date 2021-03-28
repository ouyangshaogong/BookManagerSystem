#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__

#include "serialize.h"
#include "commonace.h"

using namespace std;

#define REQUEST_MSG_TYPE 200
#define RESPONSE_MSG_TYPE 201
#define END_MSG_TYPE 300

const int SEND_PROC_ID = 50;
const int RECV_PROC_ID = 51;


class iMapCmdMsg
{
public:
    iMapCmdMsg();
    ~iMapCmdMsg();

    void SetMagicNum(int nMagicNum);
    int GetMagicNum();

    void SetVersion(int nVersion);
    int GetVersion();

    void SetMsgID(int nMrbCmdMsg);
    int GetMsgID();

    void SetMrbCmdMsg(int nMrbCmdMsg);
    int GetMrbCmdMsg();

    void SetMsgType(int nMsgType);
    int GetMsgType();

    void SetSendProc(int nSendProc);
    int GetSendProc();

    void SetRecvProc(int nRecvProc);
    int GetRecvProc();

    void SetMsgBodyLength(int nLength);
    int GetMsgBodyLength();

    void SetMsgHeaderLength(int nMsgHeaderLength);
    int GetMsgHeaderLength();

    void SetMsgLength(int nMsgLength);
    int GetMsgLength();

    void SetBody(string &strBody);
    string GetBody();

    std::string serializeHeader()
    {
        OutStream os;
        os << m_nMagicNum << m_nVersion << m_nMsgID << m_nMrbCmdMsg << m_nMsgType << m_nSendProc << m_nRecvProc << m_nMsgBodyLength << m_nMsgLength;
        m_nMsgHeaderLength = os.str().size();
        return os.str();
    }

    int deserializeHeader(std::string &str)
    {
        InStream is(str);
        is >> m_nMagicNum >> m_nVersion >> m_nMsgID >> m_nMrbCmdMsg >> m_nMsgType >> m_nSendProc >> m_nRecvProc >> m_nMsgBodyLength >> m_nMsgLength;
        return is.size();
    }

    std::string serializeBody()
    {
        OutStream os;
        os << *m_strBody;
        return os.str();
    }

    int deserializeBody(std::string &str)
    {
        InStream is(str);

        string strBody;
        is >> strBody;
        if (m_strBody == NULL)
        {
            m_strBody = new string(strBody);
        }

        return is.size();
    }

    void display(string strFunc)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)%s>>m_nMsgID:%d, m_nMsgType:%d, m_nMsgBodyLength:%d, m_nMrbCmdMsg:%d, m_nSendProc:%d, m_nRecvProc:%d, m_strBody:%s\n",
            strFunc.c_str(), m_nMsgID, m_nMsgType, m_nMsgBodyLength, m_nMrbCmdMsg, m_nSendProc, m_nRecvProc, m_strBody->c_str()));
    }

private:
    int m_nMagicNum;
    int m_nVersion;
    int m_nMsgID;
    int m_nMrbCmdMsg;
    int m_nMsgType;
    int m_nSendProc;
    int m_nRecvProc;
    //字符长度
    int m_nMsgLength;
    //序列化后的长度
    int m_nMsgHeaderLength;
    int m_nMsgBodyLength;
    string *m_strBody;
};

#endif
