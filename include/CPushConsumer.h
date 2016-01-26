//
// Created by root on 16-1-18.
//

#ifndef ROCKETMQ_CPUSHCONSUMER_H
#define ROCKETMQ_CPUSHCONSUMER_H

#include "../../include/AllocateMessageQueueStrategy.h"
#include "../../include/ConsumeType.h"
#include "../../include/MessageListener.h"
#include <list>
#include <string>

//消费者初始化
void pushconsumer_init( char* consumerName);

//set NameServer Addr
void pushconsumer_setNameServerAddr( char* nameServerAddr);

//start consumer
void pushconsumer_start();

//shutdown consumer
void pushconsumer_shutdown();

//设置Rebalance算法实现策略
void pushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue);
//设置单队列并行消费匀速的最大跨度
void pushconsumer_setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan);
//Consumer启动后，默认从什么位置开始消费
void pushconsumer_setConsumeFromWhere(ConsumeFromWhere consumeFromWhere);
//批量消费，一次消费多少条信息
void pushconsumer_setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize);
//消费线程池数量最大值
void pushconsumer_setConsumeThreadMax(int consumeThreadMax);
//消费线程池数量最小值
void pushconsumer_setConsumeThreadMin(int consumeThreadMin);
//设置消息监听器
void pushconsumer_setMessageListener(int (*fp)(Struct_MessageExt*));
//设置消息模型，支持两种，集群消费和广播消费
void pushconsumer_setMessageModel(MessageModel messageModel) ;
//拉消息间隔，由于时长轮询，所以为0,但是如果应用为了流控，也可以设置大于0的值，单位毫秒
void pushconsumer_setPullBatchSize(int pullBatchSize);
//批量拉消息，一次最多拉多少条
void pushconsumer_setPullInterval(long pullInterval);
//拉消息本地缓存队列缓存消息最大数
void pushconsumer_setPullThresholdForQueue(int pullThresholdForQueue);
//订阅消息
void pushconsumer_setSubscription(std::map<std::string, std::string>& subscription);

void pushconsumer_updateCorePoolSize(int corePoolSize);
std::set<MessageQueue>* pushconsumer_fetchSubscribeMessageQueues(char* topic);

void pushconsumer_subscribe(char* topic, char* subExpression);
void pushconsumer_unsubscribe(char* topic);

void pushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt*));

void pushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)(struct Struct_MessageExt** ext,int len,CConsumerConcurrentlyContext context));

void pushconsumer_setClientIP(char* clientIP);
void pushconsumer_setInstanceName(char* instanceName);
void pushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
void pushconsumer_setPollNameServerInterval(int pollNameServerInterval);
void pushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
void pushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);

#endif //ROCKETMQ_CPUSHCONSUMER_H
