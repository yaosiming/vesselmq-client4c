//
// Created by root on 16-1-19.
//

#ifndef ROCKETMQ_CPULLCONSUMERWAPPER_H
#define ROCKETMQ_CPULLCONSUMERWAPPER_H


#include <ConsumeType.h>
#include "../common/Struct_MessageQueues.h"
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/MapData.h"
#include "../common/Struct_MessageExt.h"
#include "../common/Struct_PullResult.h"

#ifdef __cplusplus
extern "C"{
#endif

//消费者初始化
void mpullconsumer_init( char* consumerName);
//set NameServer Addr
void mpullconsumer_setNameServerAddr( char* nameServerAddr);
//start consumer
void mpullconsumer_start();
//shutdown consumer
void mpullconsumer_shutdown();

void mpullconsumer_setClientIP(char* clientIP);
void mpullconsumer_setInstanceName(char* instanceName);
void mpullconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
void mpullconsumer_setPollNameServerInterval(int pollNameServerInterval);
void mpullconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
void mpullconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);



void mpullconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue);
void mpullconsumer_setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis);

void mpullconsumer_setConsumerGroup(char* consumerGroup);

void mpullconsumer_setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis);

void mpullconsumer_setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend);

void mpullconsumer_setMessageModel(MessageModel messageModel);

//void setMessageQueueListener(int (*fp)(Struct_MessageExt*));

void mpullconsumer_setRegisterTopics( int i, MString* topics);


int mpullconsumer_fetchSubscribeMessageQueues(char* topic,SMessageQueues** head);

SPullresult* mpullconsumer_pullBlockIfNotFound(SMessageQueues mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*));


#ifdef __cplusplus
};
#endif

#endif //ROCKETMQ_CPULLCONSUMERWAPPER_H
