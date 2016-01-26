//
// Created by root on 16-1-18.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include "Tool.h"
Struct_MessageExt Tool::ClassToStruct(MessageExt* ms){
    Struct_MessageExt ext ;

//    ext->m_bodyCRC = ms->getBodyCRC();
//
//    ext->m_bornTimestamp = ms->getBornTimestamp();
//    ext->m_queueOffset = ms->getQueueOffset();
//    ext->m_commitLogOffset = ms->getCommitLogOffset();
//    ext->m_storeTimestamp = ms->getStoreTimestamp();
//    ext->m_preparedTransactionOffset = ms->getPreparedTransactionOffset();
//    ext->m_queueId = ms->getQueueOffset();
//    ext->m_sysFlag = ms->getSysFlag();
//    ext->m_reconsumeTimes =ms->getReconsumeTimes();
//    ext->m_storeHost =  StringToChar(socketAddress2String(ms->getStoreHost()));
//    ext->m_msgId =  StringToChar(ms->getMsgId());
//    ext->m_topic = StringToChar(ms->getTopic());
//    ext->m_bornHost = StringToChar(socketAddress2String(ms->getBornHost()));

    ext.m_bodyCRC = ms->getBodyCRC();

    ext.m_bornTimestamp = ms->getBornTimestamp();
    ext.m_queueOffset = ms->getQueueOffset();
    ext.m_commitLogOffset = ms->getCommitLogOffset();
    ext.m_storeTimestamp = ms->getStoreTimestamp();
    ext.m_preparedTransactionOffset = ms->getPreparedTransactionOffset();
    ext.m_queueId = ms->getQueueOffset();
    ext.m_sysFlag = ms->getSysFlag();
    ext.m_reconsumeTimes =ms->getReconsumeTimes();
    ext.m_storeHost =  StringToChar(socketAddress2String(ms->getStoreHost()));
    ext.m_msgId =  StringToChar(ms->getMsgId());
    ext.m_topic = StringToChar(ms->getTopic());
    ext.m_bornHost = StringToChar(socketAddress2String(ms->getBornHost()));
    ext.m_body = ConstCharToChar(ms->getBody(),ms->getBodyLen());
    ext.m_body_len = ms->getBodyLen();

//    std::cout<<ext.m_bodyCRC <<":"<< ms->getBodyCRC()<<std::endl;
//    std::cout<<ext.m_bornHost <<":"<< socketAddress2String(ms->getBornHost()).c_str()<<std::endl;
//    std::cout<<ext.m_bornTimestamp <<":"<< ms->getBornTimestamp()<<std::endl;
//    std::cout<<ext.m_queueOffset <<":"<< ms->getQueueOffset()<<std::endl;
//    std::cout<<ext.m_commitLogOffset <<":"<< ms->getCommitLogOffset()<<std::endl;
//    std::cout<<ext.m_storeTimestamp <<":"<< ms->getStoreTimestamp()<<std::endl;
//    std::cout<<ext.m_preparedTransactionOffset <<":"<< ms->getPreparedTransactionOffset()<<std::endl;
//    std::cout<<ext.m_queueId <<":"<< ms->getQueueOffset()<<std::endl;
//    std::cout<<ext.m_sysFlag <<":"<< ms->getSysFlag()<<std::endl;
//    std::cout<<ext.m_reconsumeTimes <<":"<< ms->getReconsumeTimes()<<std::endl;
//    std::cout<<ext.m_storeHost <<":"<<  socketAddress2String(ms->getStoreHost()).c_str()<<std::endl;
//    std::cout<<ext.m_msgId <<":"<<  ms->getMsgId().c_str()<<std::endl;
//    std::cout<<ext.m_topic <<":"<< ms->getTopic().c_str()<<std::endl;
    return ext;
}
char* Tool::StringToChar(std::string str1){
    const char* temp = str1.c_str();
    char* buf = new char[strlen(temp)+1];
    strcpy(buf,temp);
    return buf;
}
std::string Tool::socketAddress2String(sockaddr addr)
{
    sockaddr_in in;
    memcpy(&in,&addr,sizeof(sockaddr));

    return inet_ntoa(in.sin_addr);
}

char *Tool::ConstCharToChar(const char *body,int len) {
    char *buf = (char *) malloc(sizeof(char) * len);
    //strcpy(buf,body);
    memccpy(buf,body,0,len);
    return buf;
}
