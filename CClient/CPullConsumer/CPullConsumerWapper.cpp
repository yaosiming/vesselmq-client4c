//
// Created by root on 16-1-19.
//

#include <ConsumeType.h>
#include <MessageQueue.h>
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageQueues.h"
#include "../CPushConsumer/Tool.h"
#include "../common/MapData.h"
#include "../common/Struct_PullResult.h"
#include <iostream>
#include <map>
#include <set>
#include <PullResult.h>

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

//void setRegisterTopics( std::set<std::string> registerTopics);


std::set<MessageQueue>* pullconsumer_fetchSubscribeMessageQueues(char* topic);
void pullconsumer_setRegisterTopics( std::set<std::string> registerTopics);

PullResult* pullconsumer_pullBlockIfNotFound(MessageQueue& mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*));

#ifdef __cplusplus
extern "C"{
#endif

void mpullconsumer_init(char* consumerName){
    pullconsumer_init(consumerName);
}

void mpullconsumer_setNameServerAddr(char *nameServerAddr) {
    pullconsumer_setNameServerAddr(nameServerAddr);
}

void mpullconsumer_start() {
    pullconsumer_start();
}

void mpullconsumer_shutdown() {
    pullconsumer_shutdown();
}

void mpullconsumer_setClientIP(char *clientIP) {
    pullconsumer_setClientIP(clientIP);
}

void mpullconsumer_setInstanceName(char *instanceName) {
    pullconsumer_setInstanceName(instanceName);
}

void mpullconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads) {
    pullconsumer_setClientCallbackExecutorThreads(clientCallbackExecutorThreads);
}

void mpullconsumer_setPollNameServerInterval(int pollNameServerInterval) {
    pullconsumer_setPollNameServerInterval(pollNameServerInterval);
}

void mpullconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval) {
    pullconsumer_setHeartbeatBrokerInterval(heartbeatBrokerInterval);
}

void mpullconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval) {
    pullconsumer_setPersistConsumerOffsetInterval(persistConsumerOffsetInterval);
}

void mpullconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue) {
    pullconsumer_setAllocateMessageQueueStrategy(strategyStatue);
}

void mpullconsumer_setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis) {
    pullconsumer_setBrokerSuspendMaxTimeMillis(brokerSuspendMaxTimeMillis);
}

void mpullconsumer_setConsumerGroup(char *consumerGroup) {
    pullconsumer_setConsumerGroup(consumerGroup);
}

void mpullconsumer_setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis) {
    pullconsumer_setConsumerPullTimeoutMillis(consumerPullTimeoutMillis);
}

void mpullconsumer_setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend) {
    pullconsumer_setConsumerTimeoutMillisWhenSuspend(consumerTimeoutMillisWhenSuspend);
}

void mpullconsumer_setMessageModel(MessageModel messageModel) {
    pullconsumer_setMessageModel(messageModel);
}

int mpullconsumer_fetchSubscribeMessageQueues(char* topic,SMessageQueues** head){

    std::set<MessageQueue>* message = pullconsumer_fetchSubscribeMessageQueues(topic);
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
void mpullconsumer_setRegisterTopics( int len, MString* topics){
    std::set<std::string> registerTopics;
    for(int i=0;i<len;i++){
        registerTopics.insert(topics[i].str1);
    }
    pullconsumer_setRegisterTopics(registerTopics);
}

SPullresult* mpullconsumer_pullBlockIfNotFound(SMessageQueues mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*)){
//  MessageQueue(const std::string& topic, const std::string& brokerName, int queueId);
    Tool tool;
    //Struct to Class
    MessageQueue* messageQueue = new MessageQueue(mq.m_topic,mq.m_brokerName,mq.m_queueId);
    messageQueue->setTopic(mq.m_topic);
    messageQueue->setBrokerName(mq.m_brokerName);
    messageQueue->setQueueId(mq.m_queueId);
    PullResult *result =  pullconsumer_pullBlockIfNotFound(*messageQueue,subExpression,offset,maxNums,fp);
    //std::cout<<"result->pullStatus::"<<result->pullStatus<<std::endl;
    if(result->pullStatus!=0){

        //PullResult to Struct_PullResult;
        SPullresult *sPullresult;
        sPullresult->pullStatus = result->pullStatus;
        sPullresult->nextBeginOffset = result->nextBeginOffset;
        sPullresult->maxOffset = result->maxOffset;
        sPullresult->minOffset = result->minOffset;
        std::list<MessageExt*> msgFoundList = result->msgFoundList;
        std::list<MessageExt*>::iterator it = msgFoundList.begin();

        int len = msgFoundList.size();
        Struct_MessageExt* SMsgFoundList = new Struct_MessageExt[len];

        for(int i=0;it!=msgFoundList.end();it++,i++){
            MessageExt* ext = *it;
            SMsgFoundList[i] = tool.ClassToStruct(ext);
        }
        sPullresult->len = len;

        sPullresult->msgFoundList = SMsgFoundList;
        return sPullresult;
    }
    return nullptr;
}


#ifdef __cplusplus
};
#endif


