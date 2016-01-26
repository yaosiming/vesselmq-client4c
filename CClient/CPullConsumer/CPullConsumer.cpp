//
// Created by root on 16-1-19.
//
#include <iostream>
#include <DefaultMQPullConsumer.h>
#include <consumer/AllocateMessageQueueStrategyInner.h>
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageExt.h"
#include "../CPushConsumer/Tool.h"

std::map<MessageQueue, long long> offsetTable;

void putMessageQueueOffset(const MessageQueue& mq, long long offset)
{
    offsetTable[mq]=offset;
}

long long getMessageQueueOffset(const MessageQueue& mq)
{
    std::map<MessageQueue, long long>::iterator it = offsetTable.find(mq);

    if (it != offsetTable.end())
    {
        return it->second;
    }

    return 0;
}

void PrintResult(PullResult& result,int (*fp)(Struct_MessageExt*))
{
//    std::cout<<"[pullStatus="<<result.pullStatus
//    <<"][nextBeginOffset="<<result.nextBeginOffset
//    <<"][minOffset="<<result.minOffset
//    <<"][maxOffset="<<result.maxOffset
//    <<"]"<<std::endl;

    std::list<MessageExt*>::iterator it = result.msgFoundList.begin();
    Tool tool;
    Struct_MessageExt ext;

    for (;it!=result.msgFoundList.end();it++)
    {
        MessageExt* me = *it;
//        std::string str;
//        str.assign(me->getBody(),me->getBodyLen());
//        std::cout<<str<<std::endl;
        //std::cout<<"result.nextBeginOffset:"<<result.nextBeginOffset<<std::endl;
        ext = tool.ClassToStruct(me);

    }
    (*fp)(&ext);
}
DefaultMQPullConsumer* consumer;

void pullconsumer_init(char *consumerName) {
    consumer = new DefaultMQPullConsumer(consumerName);
}

void pullconsumer_setNameServerAddr(char *nameServerAddr) {
    (*consumer).setNamesrvAddr(nameServerAddr);
}

void pullconsumer_start() {
    (*consumer).start();
}

void pullconsumer_shutdown() {
    (*consumer).shutdown();
    delete(consumer);
}

void pullconsumer_setClientIP(char *clientIP) {
    (*consumer).setClientIP(clientIP);
}

void pullconsumer_setInstanceName(char *instanceName) {
    (*consumer).setInstanceName(instanceName);
}

void pullconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads) {
    (*consumer).setClientCallbackExecutorThreads(clientCallbackExecutorThreads);
}

void pullconsumer_setPollNameServerInterval(int pollNameServerInterval) {
    (*consumer).setPollNameServerInterval(pollNameServerInterval);
}

void pullconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval) {
    (*consumer).setHeartbeatBrokerInterval(heartbeatBrokerInterval);
}

void pullconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval) {
    (*consumer).setPersistConsumerOffsetInterval(persistConsumerOffsetInterval);
}

void pullconsumer_setAllocateMessageQueueStrategy( AllocateMessageQueueStrategyStatue strategyStatue) {
    AllocateMessageQueueStrategy* strategy;

    switch (strategyStatue){
        case AllocateMessageQueueByConfig_Statue:
            //2 按照配置来分配队列
            strategy = new AllocateMessageQueueByConfig();
            break;
        case AllocateMessageQueueByMachineRoom_Statue:
            //3 按照机房来分配队列
            strategy = new AllocateMessageQueueByMachineRoom();
            break;
        default:
            //1 Consumer队列自动分配策略,平均分配队列算法
            strategy = new AllocateMessageQueueAveragely();
            break;
    }
    (*consumer).setAllocateMessageQueueStrategy(strategy);
}

void pullconsumer_setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis) {
    (*consumer).setBrokerSuspendMaxTimeMillis(brokerSuspendMaxTimeMillis);
}

void pullconsumer_setConsumerGroup(char *consumerGroup) {
    (*consumer).setConsumerGroup(consumerGroup);
}

void pullconsumer_setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis) {
    (*consumer).setConsumerPullTimeoutMillis(consumerPullTimeoutMillis);
}

void pullconsumer_setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend) {
    (*consumer).setConsumerTimeoutMillisWhenSuspend(consumerTimeoutMillisWhenSuspend);
}

void pullconsumer_setMessageModel(MessageModel messageModel) {
    (*consumer).setMessageModel(messageModel);
}

std::set<MessageQueue>* pullconsumer_fetchSubscribeMessageQueues(char* topic){
    return (*consumer).fetchSubscribeMessageQueues(topic);
}
void pullconsumer_setRegisterTopics( std::set<std::string> registerTopics){
    (*consumer).setRegisterTopics(registerTopics);
}

PullResult* pullconsumer_pullBlockIfNotFound(MessageQueue& mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*)){

    bool noNewMsg = false;
    PullResult* pullResult;
    while (!noNewMsg)
    {
        try
        {
            pullResult = (*consumer).pullBlockIfNotFound(mq,subExpression,getMessageQueueOffset(mq),maxNums);

            switch (pullResult->pullStatus)
            {
                case FOUND:
                        // TODO
                    PrintResult(*pullResult,fp);
                    putMessageQueueOffset(mq, pullResult->nextBeginOffset);
                    //(*consumer).updateConsumeOffset(mq,pullResult->nextBeginOffset);
                    break;
                case NO_MATCHED_MSG:
                    break;
                case NO_NEW_MSG:
                    noNewMsg = true;
                    break;
                case OFFSET_ILLEGAL:
                    break;
                default:
                    break;
            }

            delete pullResult;
        }
        catch (MQClientException& e)
        {
            std::cout<<e<<std::endl;
        }
    }

    return pullResult;
}


