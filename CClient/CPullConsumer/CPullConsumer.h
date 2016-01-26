//
// Created by root on 16-1-19.
//

#ifndef ROCKETMQ_CPULLCONSUMER_H
#define ROCKETMQ_CPULLCONSUMER_H

#include <ConsumeType.h>
#include <MessageQueue.h>
#include <PullResult.h>
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageExt.h"

//消费者初始化
void pullconsumer_init( char* consumerName);
//set NameServer Addr
void pullconsumer_setNameServerAddr( char* nameServerAddr);
//start consumer
void pullconsumer_start();
//shutdown consumer
void pullconsumer_shutdown();

void pullconsumer_setClientIP(char* clientIP);
void pullconsumer_setInstanceName(char* instanceName);
void pullconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
void pullconsumer_setPollNameServerInterval(int pollNameServerInterval);
void pullconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
void pullconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);



void pullconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue);
void pullconsumer_setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis);

void pullconsumer_setConsumerGroup(char* consumerGroup);

void pullconsumer_setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis);

void pullconsumer_setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend);

void pullconsumer_setMessageModel(MessageModel messageModel);

//void setMessageQueueListener(int (*fp)(Struct_MessageExt*));

void pullconsumer_setRegisterTopics( std::set<std::string> registerTopics);


std::set<MessageQueue>* pullconsumer_fetchSubscribeMessageQueues(char* topic);

PullResult* pullconsumer_pullBlockIfNotFound(MessageQueue& mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*));



#endif //ROCKETMQ_CPULLCONSUMER_H
