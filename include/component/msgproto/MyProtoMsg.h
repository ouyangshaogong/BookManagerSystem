#ifndef __MAP_CMD_MSG__
#define __MAP_CMD_MSG__

#include "commonace.h"
#include "json/json.h"

using namespace std;

const uint8_t MY_PROTO_MAGIC = 2;                   
const uint32_t MY_PROTO_MAX_SIZE = 5 * 1024 * 1024; 
const uint32_t MY_PROTO_HEAD_SIZE = 34;             

typedef enum MyProtoParserStatus 
{
    ON_PARSER_INIT = 0, 
    ON_PARSER_HEAD = 1,
    ON_PARSER_BODY = 2, 
} MyProtoParserStatus;

struct MyProtoHeader
{
    uint8_t nMagic;
    uint8_t nVersion;
    uint16_t nSendProc;
    uint16_t nRecvProc;
    uint32_t nTaskMgrID;
    uint32_t nTaskID;
    uint32_t nMsgID;
    uint32_t nCmdMsg;
    uint32_t nMsgType;

    uint32_t nMsgRet;
    uint32_t nMsgLength;

    MyProtoHeader()
    {
        nMagic = 0;
        nVersion = 0;
        nSendProc = 0;
        nRecvProc = 0;
        nTaskMgrID = 0;
        nTaskID = 0;
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


#endif
