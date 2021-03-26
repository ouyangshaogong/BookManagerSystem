#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__


#include <string>
#include "serialize.h"
#include "ace/Log_Msg.h"

using namespace std;

#define REQUEST_MSG_TYPE 0
#define RESPONSE_MSG_TYPE 1
#define END_MSG_TYPE 100


class iMapCmdMsg //: public Serializable
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

    void SetMsgBodyLength(int nLength);
    int GetMsgBodyLength();

    int GetMsgHeaderLength();

    void SetBody(string strBody);
    string GetBody();

    virtual std::string serializeHeader()
    {
        OutStream os;
        os << m_nMagicNum << m_nVersion << m_nMsgID << m_nMrbCmdMsg << m_nMsgType << m_nMsgBodyLength;
        return os.str();
    }

    virtual int deserializeHeader(std::string &str)
    {
        InStream is(str);
        is >> m_nMagicNum >> m_nVersion >> m_nMsgID >> m_nMrbCmdMsg >> m_nMsgType >> m_nMsgBodyLength;
        return is.size();
    }

    virtual std::string serializeBody()
    {
        OutStream os;
        os << m_strBody;
        return os.str();
    }

    virtual int deserializeBody(std::string &str)
    {
        InStream is(str);
        is >> m_strBody;
        return is.size();
    }

    void display()
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapCmdMsg::display>>m_nMsgID:%d, m_nMsgType:%d, m_nMsgBodyLength:%d, m_strBody:%s\n", m_nMsgID, m_nMsgType, m_nMsgBodyLength, m_strBody.c_str()));
    }

private:
    int m_nMagicNum;
    int m_nVersion;
    int m_nMsgID;
    int m_nMrbCmdMsg;
    int m_nMsgType;
    int m_nMsgHeaderLength;
    int m_nMsgBodyLength;
    string m_strBody;
};

#endif
