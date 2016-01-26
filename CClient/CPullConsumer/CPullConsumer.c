//
// Created by root on 16-1-20.
//
#include <ConsumeType.h>
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/MapData.h"
#include "../common/Struct_MessageQueues.h"
#include "../common/Struct_PullResult.h"
#include "CPullConsumerWapper.h"
#include <stdio.h>
#include<string.h>
//消费者初始化
extern void mpullconsumer_init( char* consumerName);
//set NameServer Addr
extern void mpullconsumer_setNameServerAddr( char* nameServerAddr);
//start consumer
extern void mpullconsumer_start();
//shutdown consumer
extern void mpullconsumer_shutdown();
extern void mpullconsumer_setClientIP(char* clientIP);
extern void mpullconsumer_setInstanceName(char* instanceName);
extern void mpullconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
extern void mpullconsumer_setPollNameServerInterval(int pollNameServerInterval);
extern void mpullconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
extern void mpullconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);
extern void mpullconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue);
extern void mpullconsumer_setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis);
extern void mpullconsumer_setConsumerGroup(char* consumerGroup);
extern void mpullconsumer_setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis);
extern void mpullconsumer_setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend);
extern void mpullconsumer_setMessageModel( MessageModel messageModel);
//void setMessageQueueListener(int (*fp)(Struct_MessageExt*));
extern void mpullconsumer_setRegisterTopics( int i,  MString* topics);
extern int mpullconsumer_fetchSubscribeMessageQueues(char* topic, SMessageQueues** head);
extern SPullresult* mpullconsumer_pullBlockIfNotFound(SMessageQueues mq,char* subExpression,long long offset, int maxNums,int (*fp)(Struct_MessageExt*));
int deal(Struct_MessageExt* ext){
    char body[ext->m_body_len+1];
//    memcpy();
    strncpy(body,ext->m_body,ext->m_body_len);
    printf("mesageID:%s m_queueI: %d \t m_storeSize: %d \t Broker: %s  body: %s  bodylength:%d \n",ext->m_msgId,ext->m_queueId,ext->m_storeSize,ext->m_bornHost,body,ext->m_body_len);
}
int main(){
    char consumerName[] = "consumergroup1";
    char instanName[] ="pullconsumer1";
    char NameServerAddr[] = "127.0.0.1:9876";
    char topic[] = "testTopicC";
    char TagA[] = "TagA || TagC || TagD";
    char sub[] = "";
    int i=0;
    printf("hello world! this is CPulConsumer\n");
    mpullconsumer_init(consumerName);
    mpullconsumer_setNameServerAddr(NameServerAddr);
    mpullconsumer_setInstanceName(instanName);
    mpullconsumer_start();
    SMessageQueues* messageQueues;
    int len = mpullconsumer_fetchSubscribeMessageQueues(topic,&messageQueues);
    printf("len: %d \n",len);
    for(i=0;i<len;i++){
        /*
         * PullStatus pullStatus;
        long long nextBeginOffset;
        long long minOffset;
        long long maxOffset;
         */
        SPullresult* result =  mpullconsumer_pullBlockIfNotFound(messageQueues[i],sub,0, 1024,&deal);
        if(result!=NULL)
            printf("pullResult = [pullStatus:%d  nextBeginOffset:%lld  minOffset:%lld  maxOffset:%lld size:%d ] \n",result->pullStatus,result->nextBeginOffset,result->minOffset,result->maxOffset,result->len);
    }
    printf("finish!");
    return 0;
}
