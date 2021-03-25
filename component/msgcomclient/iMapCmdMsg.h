#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__


#include <string>
#include "serialize.h"

using namespace std;

#define REQUEST_MSG_TYPE 0
#define RESPONSE_MSG_TYPE 1
#define END_MSG_TYPE 100


class iMapCmdMsg: public Serializable
{
public:
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

    void SetMsgLength(int nLength);
    int GetMsgLength();

    void SetAttachMents(string strAttachments);
    string GetAttachMents();

    void SetBody(string strBody);
    void GetBody();

    virtual std::string serialize()
    {
        OutStream os;
        os << m_nMagicNum << m_nVersion << m_nMsgID << m_nMrbCmdMsg << m_nMsgType << m_nMsgLength << m_strAttachments << m_strBody;
        return os.str();
    }

    virtual int deserialize(std::string &str)
    {
        InStream is(str);
        is >> m_nMagicNum >> m_nVersion >> m_nMsgID >> m_nMrbCmdMsg >> m_nMsgType >> m_nMsgLength >> m_strAttachments >> m_strBody;
        return is.size();
    }

private:
    int m_nMagicNum;
    int m_nVersion;
    int m_nMsgID;
    int m_nMrbCmdMsg;
    int m_nMsgType;
    int m_nMsgLength;
    string m_strAttachments;
    string m_strBody;
};

#endif
