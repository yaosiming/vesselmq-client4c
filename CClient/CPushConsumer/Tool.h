//
// Created by root on 16-1-18.
//

#ifndef ROCKETMQ_TOOL_H
#define ROCKETMQ_TOOL_H


#include <MessageExt.h>
#include "../common/Struct_MessageExt.h"

class Tool {
public:
    Struct_MessageExt ClassToStruct(MessageExt* ms);
    std::string socketAddress2String(sockaddr addr);
    char* StringToChar(std::string str1);
    char* ConstCharToChar(const char* body,int len);

    };


#endif //ROCKETMQ_TOOL_H
