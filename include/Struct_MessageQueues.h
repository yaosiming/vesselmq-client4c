//
// Created by root on 16-1-19.
//

#ifndef ROCKETMQ_STRUCTMESSAGEQUEUES_H
#define ROCKETMQ_STRUCTMESSAGEQUEUES_H

//MessageQueues -> struct
struct SMessageQueues{
    char* m_topic;
    char* m_brokerName;
    int m_queueId;
};
#endif //ROCKETMQ_STRUCTMESSAGEQUEUES_H
