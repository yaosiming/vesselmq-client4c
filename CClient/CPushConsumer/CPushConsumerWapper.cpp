//
// Created by root on 16-1-18.
//

#include <AllocateMessageQueueStrategy.h>
#include <ConsumeType.h>
#include <MessageListener.h>
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageExt.h"
#include "../common/Struct_MessageQueues.h"
#include "Tool.h"
#include "../common/MapData.h"
#include "../common/Struct_ConsumeConcurrentlyContext.h"
#include <iostream>
#include <set>
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


void pushconsumer_subscribe(char* topic, char* subExpression);
void pushconsumer_unsubscribe(char* topic);

void pushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt*));

void pushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)(Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context));


void pushconsumer_setClientIP(char* clientIP);
void pushconsumer_setInstanceName(char* instanceName);
void pushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
void pushconsumer_setPollNameServerInterval(int pollNameServerInterval);
void pushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
void pushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);

std::set<MessageQueue>* pushconsumer_fetchSubscribeMessageQueues(char* topic);
void pushconsumer_updateCorePoolSize(int corePoolSize);


#ifdef __cplusplus
extern "C"{
#endif


void mpushconsumer_init(char* consumerName){
    pushconsumer_init(consumerName);

}

void mpushconsumer_setNameServerAddr(char *nameServerAddr) {
    pushconsumer_setNameServerAddr(nameServerAddr);
}

void mpushconsumer_start() {
    pushconsumer_start();

}

void mpushconsumer_shutdown() {
    pushconsumer_shutdown();
}

void mpushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue) {
    pushconsumer_setAllocateMessageQueueStrategy(strategyStatue);
}

void mpushconsumer_setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan) {
    pushconsumer_setConsumeConcurrentlyMaxSpan(consumeConcurrentlyMaxSpan);
}

void mpushconsumer_setConsumeFromWhere(ConsumeFromWhere consumeFromWhere) {
    pushconsumer_setConsumeFromWhere(consumeFromWhere);
}

void mpushconsumer_setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize) {
    pushconsumer_setConsumeMessageBatchMaxSize(consumeMessageBatchMaxSize);
}

void mpushconsumer_setConsumeThreadMax(int consumeThreadMax) {
    pushconsumer_setConsumeThreadMax(consumeThreadMax);
}

void mpushconsumer_setConsumeThreadMin(int consumeThreadMin) {
    pushconsumer_setConsumeThreadMin(consumeThreadMin);
}

void mpushconsumer_setMessageListener(int (*fp)(Struct_MessageExt*)) {
    pushconsumer_setMessageListener(fp);
}

void mpushconsumer_setMessageModel(MessageModel messageModel) {
    pushconsumer_setMessageModel(messageModel);
}

void mpushconsumer_setPullBatchSize(int pullBatchSize) {
    pushconsumer_setPullBatchSize(pullBatchSize);
}

void mpushconsumer_setPullInterval(long pullInterval) {
    pushconsumer_setPullInterval(pullInterval);
}

void mpushconsumer_setPullThresholdForQueue(int pullThresholdForQueue) {
    pushconsumer_setPullThresholdForQueue(pullThresholdForQueue);
}
//
//void mpushconsumer_setSubscription(const std::map<char *, char *> &subscription) {
//
//}

void mpushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt*)) {
    pushconsumer_registerMessageListener(fp);
}
void mpushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)( Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context)) {
    pushconsumer_registerMessageListener2(fp);
}
void mpushconsumer_subscribe(char *topic, char *subExpression) {
    pushconsumer_subscribe(topic,subExpression);
}

void mpushconsumer_unsubscribe(char *topic) {
    pushconsumer_unsubscribe(topic);
}
void mpushconsumer_setClientIP(char* clientIP){
    pushconsumer_setClientIP(clientIP);
}

void mpushconsumer_setInstanceName(char *instanceName) {
    pushconsumer_setInstanceName(instanceName);
}

void mpushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads) {
    pushconsumer_setClientCallbackExecutorThreads(clientCallbackExecutorThreads);
}

void mpushconsumer_setPollNameServerInterval(int pollNameServerInterval) {
    pushconsumer_setPollNameServerInterval(pollNameServerInterval);
}

void mpushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval) {
    pushconsumer_setHeartbeatBrokerInterval(heartbeatBrokerInterval);
}

void mpushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval) {
    pushconsumer_setPersistConsumerOffsetInterval(persistConsumerOffsetInterval);
}
int mpushconsumer_fetchSubscribeMessageQueues(char* topic,SMessageQueues** head){

    std::set<MessageQueue>* message = pushconsumer_fetchSubscribeMessageQueues(topic);
    std::set<MessageQueue>::iterator it = message->begin();
    int len = message->size();
    Tool tool;
    SMessageQueues* ss = new SMessageQueues[len];
    for (int i=0;it!=message->end();it++,i++){
        MessageQueue queue = *it;
        ss[i] = {tool.StringToChar(queue.getTopic()),tool.StringToChar(queue.getBrokerName()),queue.getQueueId()};
    }
    *head = ss;
    return len;
}

void mpushconsumer_setSubscription(int len,SubscriptionData *subscription){
    std::map<std::string, std::string> map_subscription ;
    for(int i=0;i<len;i++){
        //std::cout<<"topic:"<<subscription[i].str1<<",subExpress:"<<subscription[i].str2<<std::endl;
        map_subscription.insert(std::pair<std::string,std::string>(subscription[i].str1,subscription[i].str2));
    }
    pushconsumer_setSubscription(map_subscription);
}

void mpushconsumer_updateCorePoolSize(int corePoolSize){
    pushconsumer_updateCorePoolSize(corePoolSize);
}
#ifdef __cplusplus
};
#endif