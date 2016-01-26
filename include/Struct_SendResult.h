//
// Created by root on 16-1-15.
//

#ifndef ROCKETMQ_STRUCTRESULT_H
#define ROCKETMQ_STRUCTRESULT_H

#include <MessageQueue.h>
#include <SendResult.h>
// producer send message result
struct structResult{
    SendStatus m_sendStatus;
    std::string m_msgId;
    std::string m_topic;
    std::string m_brokerName;
    int m_queueId;
    long long m_queueOffset;
};

#endif //ROCKETMQ_STRUCTRESULT_H
