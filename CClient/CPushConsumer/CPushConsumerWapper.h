//
// Created by root on 16-1-18.
//

#ifndef ROCKETMQ_CPUSHCONSUMERWAPPER_H
#define ROCKETMQ_CPUSHCONSUMERWAPPER_H


#include "../../include/AllocateMessageQueueStrategy.h"
#include "../../include/ConsumeType.h"
#include "../../include/MessageListener.h"
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageExt.h"
#include "../common/Struct_MessageQueues.h"
#include "../common/MapData.h"
#include "../common/Struct_ConsumeConcurrentlyContext.h"

#ifdef __cplusplus
extern "C"{
#endif

//消费者初始化
void mpushconsumer_init( char* consumerName);

//set NameServer Addr
void mpushconsumer_setNameServerAddr( char* nameServerAddr);

//start consumer
void mpushconsumer_start();

//shutdown consumer
void mpushconsumer_shutdown();

//设置Rebalance算法实现策略
void mpushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue);
//设置单队列并行消费匀速的最大跨度
void mpushconsumer_setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan);
//Consumer启动后，默认从什么位置开始消费
void mpushconsumer_setConsumeFromWhere(ConsumeFromWhere consumeFromWhere);
//批量消费，一次消费多少条信息
void mpushconsumer_setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize);
//消费线程池数量最大值
void mpushconsumer_setConsumeThreadMax(int consumeThreadMax);
//消费线程池数量最小值
void mpushconsumer_setConsumeThreadMin(int consumeThreadMin);
//设置消息监听器
void mpushconsumer_setMessageListener(int (*fp)(Struct_MessageExt*));
//设置消息模型，支持两种，集群消费和广播消费
void mpushconsumer_setMessageModel(MessageModel messageModel) ;
//拉消息间隔，由于时长轮询，所以为0,但是如果应用为了流控，也可以设置大于0的值，单位毫秒
void mpushconsumer_setPullBatchSize(int pullBatchSize);
//批量拉消息，一次最多拉多少条
void mpushconsumer_setPullInterval(long pullInterval);
//拉消息本地缓存队列缓存消息最大数
void mpushconsumer_setPullThresholdForQueue(int pullThresholdForQueue);
//订阅消息
//void mpushconsumer_setSubscription(const std::map<char*, char*>& subscription);

void mpushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt*));
//ConsumeConcurrentlyStatus CconsumeMessage(struct Struct_MessageExt** ext,int len,CConsumerConcurrentlyContext context)
void mpushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)( Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context));


void mpushconsumer_subscribe(char* topic, char* subExpression);
void mpushconsumer_unsubscribe(char* topic);

void mpushconsumer_setClientIP(char* clientIP);
void mpushconsumer_setInstanceName(char* instanceName);
void mpushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
void mpushconsumer_setPollNameServerInterval(int pollNameServerInterval);
void mpushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
void mpushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);

int mpushconsumer_fetchSubscribeMessageQueues(char* topic,SMessageQueues** head);

void mpushconsumer_setSubscription(int i,SubscriptionData *subscription);
void mpushconsumer_updateCorePoolSize(int corePoolSize);


#ifdef __cplusplus
};
#endif
#endif //ROCKETMQ_CPUSHCONSUMERWAPPER_H
