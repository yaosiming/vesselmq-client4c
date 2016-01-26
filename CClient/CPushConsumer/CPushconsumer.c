//
// Created by root on 16-1-18.
//

#include <stdio.h>

#include "CPushConsumerWapper.h"
#include "Struct_MessageQueues.h"
//消费者初始化
extern void mpushconsumer_init( char* consumerName);

//set NameServer Addr
extern void mpushconsumer_setNameServerAddr( char* nameServerAddr);

//start consumer
extern void mpushconsumer_start();

//shutdown consumer
extern void mpushconsumer_shutdown();

//设置Rebalance算法实现策略
extern void mpushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategystatue);
//设置单队列并行消费匀速的最大跨度
extern void mpushconsumer_setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan);
//Consumer启动后，默认从什么位置开始消费
extern void mpushconsumer_setConsumeFromWhere(ConsumeFromWhere consumeFromWhere);
//批量消费，一次消费多少条信息
extern void mpushconsumer_setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize);
//消费线程池数量最大值
extern void mpushconsumer_setConsumeThreadMax(int consumeThreadMax);
//消费线程池数量最小值
extern void mpushconsumer_setConsumeThreadMin(int consumeThreadMin);
//设置消息监听器
extern void mpushconsumer_setMessageListener(int (*fp)(Struct_MessageExt));
//设置消息模型，支持两种，集群消费和广播消费
extern void mpushconsumer_setMessageModel(MessageModel messageModel) ;
//拉消息间隔，由于时长轮询，所以为0,但是如果应用为了流控，也可以设置大于0的值，单位毫秒
extern void mpushconsumer_setPullBatchSize(int pullBatchSize);
//批量拉消息，一次最多拉多少条
extern void mpushconsumer_setPullInterval(long pullInterval);
//拉消息本地缓存队列缓存消息最大数
extern void mpushconsumer_setPullThresholdForQueue(int pullThresholdForQueue);
//订阅消息
//void mpushconsumer_setSubscription(const std::map<char*, char*>& subscription);

extern void mpushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt));
extern void mpushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)( Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context));

extern void mpushconsumer_subscribe(char* topic, char* subExpression);
extern void mpushconsumer_unsubscribe(char* topic);

extern void mpushconsumer_setClientIP(char* clientIP);
extern void mpushconsumer_setInstanceName(char* instanceName);
extern void mpushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);
extern void mpushconsumer_setPollNameServerInterval(int pollNameServerInterval);
extern void mpushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval);
extern void mpushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);

extern int mpushconsumer_fetchSubscribeMessageQueues(char* topic,SMessageQueues** head);
extern void mpushconsumer_setSubscription(int i,SubscriptionData *subscription);
extern void mpushconsumer_updateCorePoolSize(int corePoolSize);

int deal(struct Struct_MessageExt* ext){
    /*
     *     long long m_queueOffset;// 队列偏移量
    long long m_commitLogOffset;// 消息对应的Commit Log Offset
    long long m_bornTimestamp;// 消息在客户端创建时间戳 <PUT>
    long long m_storeTimestamp;// 消息在服务器存储时间戳
    long long m_preparedTransactionOffset;
    int m_queueId;// 队列ID <PUT>
    int m_storeSize;// 存储记录大小
    int m_sysFlag;// 消息标志位 <PUT>
    int m_bodyCRC;// 消息体CRC
    int m_reconsumeTimes;// 当前消息被某个订阅组重新消费了几次（订阅组之间独立计数）
    char* m_bornHost;// 消息来自哪里 <PUT>
    char* m_storeHost;// 消息存储在哪个服务器 <PUT>
    char* m_msgId;// 消息ID
     */
    //printf("mesageID:%s m_queueI: %d \t m_storeSize: %d \t Broker: %s  body: %s\n",ext->m_msgId,ext->m_queueId,ext->m_storeSize,ext->m_bornHost,ext->m_body);
}

ConsumeConcurrentlyStatus CconsumeMessage(Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context){
    printf("[tConsumeMessageBatchSize: %d]\n",len);
    //for(int i=0;i<len;i++){
    int i = len-1;
        printf("mesageID:%s m_queueI: %d  m_storeSize: %d  Broker: %s \n",ext[i].m_msgId,ext[i].m_queueId,ext[i].m_storeSize,ext[i].m_bornHost);
        //printf("mesageID: m_queueI: %d \n",i);

    //}
    return CONSUME_SUCCESS;
}

int main(){
    int i=0;

    char consumerName[] = "consumergroup1";
    char NameServerAddr[] = "127.0.0.1:9876";
    char topic[] = "testTopicC";
    char TagA[] = "TagA || TagC || TagD";
    printf("hello world! this is CPushConsumer\n");
    mpushconsumer_init(consumerName);
    mpushconsumer_setNameServerAddr(NameServerAddr);
    mpushconsumer_subscribe(topic, TagA);
    //mpushconsumer_registerMessageListener(&deal);
    mpushconsumer_registerMessageListener2(&CconsumeMessage);
    mpushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueAveragely_Statue);
    mpushconsumer_setPullBatchSize(1024);
    mpushconsumer_setConsumeMessageBatchMaxSize(1024);

//    SubscriptionData subscription[2] ;
//    subscription[0]={"TopicTest","label"};
//    subscription[1]={"TopicTest2","label2"};
//    mpushconsumer_setSubscription(2,subscription);

    mpushconsumer_start();

    /*
     *  char* m_topic;
    char* m_brokerName;
    int m_queueId;
     */
//    SMessageQueues* messageQueues;
//    int len = mpushconsumer_fetchSubscribeMessageQueues("TopicTest",&messageQueues);
//
//    printf("len: %d \n",len);
//    for(i=0;i<len;i++)
//        printf("data= %s:%s:%d  \n",(messageQueues)[i].m_topic,messageQueues[i].m_brokerName,messageQueues[i].m_queueId);

    while(1)
    {
        if (getchar()=='e'&&getchar()=='x'&&getchar()=='i'&&getchar()=='t')
        {
            break;
        }

    }
    mpushconsumer_shutdown();
    return 0;
}


