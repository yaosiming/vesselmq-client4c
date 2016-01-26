//
// Created by root on 16-1-18.
//

#include <AllocateMessageQueueStrategy.h>
#include <ConsumeType.h>
#include <MessageListener.h>
#include <DefaultMQPushConsumer.h>
#include <iostream>
#include <transport/SocketUtil.h>
#include <consumer/AllocateMessageQueueStrategyInner.h>
#include "Tool.h"
#include "../common/AllocateMessageQueueStrategyStatus.h"
#include "../common/Struct_MessageExt.h"
#include "../common/Struct_ConsumeConcurrentlyContext.h"


class MsgListener : public MessageListenerConcurrently
{
public:
    MsgListener()
    {
        consumeTimes = 0;
    }

    ~MsgListener()
    {

    }
    MsgListener(int (*fp)(Struct_MessageExt*)){
        this->fp = fp;
        consumerType = 0;
        consumeTimes = 0;
    }
    MsgListener(ConsumeConcurrentlyStatus (*fp)( Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context)){
        this->fp2 = fp;
        consumerType = 1;
        consumeTimes = 0;
    }

    /*
     *  long long m_queueOffset;// 队列偏移量
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


    ConsumeConcurrentlyStatus consumeMessage(std::list<MessageExt*>& msgs,
                                             ConsumeConcurrentlyContext& context)
    {
        if(consumerType == 0)
        {
            MessageExt* msg = msgs.front();
            long long offset = msg->getQueueOffset();
            std::string maxOffset = msg->getProperty(Message::PROPERTY_MAX_OFFSET);

            long long diff = std::stoll(maxOffset) - offset;

            if (diff > 100000)
            {
                // return ConsumeConcurrentlyStatus.CONSUME_SUCCESS;
            }

            std::list<MessageExt*>::iterator it = msgs.begin();
            Struct_MessageExt ext;
            for (;it != msgs.end();it++)
            {
                MessageExt* me = *it;
//            std::string str;
//            str.append("MsgId: ").append(me->getMsgId())
//                    .append(", Topic: ").append(me->getTopic())
//                    .append(", Broker: ").append(me->getBornHostString());
//            std::string body(me->getBody(), me->getBodyLen());
//            str.append(", Body: ").append(body);
//            std::cout<<str<<std::endl;

                ext = tool.ClassToStruct(me);
                (*fp)(&ext);

            }

            consumeTimes++;
            if ((consumeTimes % 2) == 0)
            {
                return RECONSUME_LATER;
            }
            else if ((consumeTimes % 3) == 0)
            {
                context.delayLevelWhenNextConsume = 5;
                return RECONSUME_LATER;
            }

            return CONSUME_SUCCESS;
        }
        else{
            //ConsumeConcurrentlyStatus (*fp)(struct Struct_MessageExt** ext,int len,CConsumerConcurrentlyContext context)

            //std::list<MessageExt*>& msgs -->>  Struct_MessageExt** ext

            int len = (&msgs)->size();
            Struct_MessageExt *exts = new Struct_MessageExt[len];
            std::list<MessageExt*>::iterator it = msgs.begin();
            for(int i=0;it!=msgs.end();it++,i++){
                exts[i] = tool.ClassToStruct(*it);
            }
            CConsumerConcurrentlyContext* Ccontext = new CConsumerConcurrentlyContext();
            Ccontext->messageQueue.m_topic = tool.StringToChar(context.messageQueue.getTopic());
            Ccontext->messageQueue.m_brokerName = tool.StringToChar(context.messageQueue.getBrokerName());
            Ccontext->messageQueue.m_queueId = context.messageQueue.getQueueId();
            Ccontext->ackIndex = context.ackIndex;
            Ccontext->delayLevelWhenNextConsume = context.delayLevelWhenNextConsume;
//            Struct_MessageExt** ext = &exts
//            for(int i=0;i<len;i++){
//                printf("mesageID:%s m_queueI: %d  m_storeSize: %d  Broker: %s \n",exts[i].m_msgId,exts[i].m_queueId,exts[i].m_storeSize,exts[i].m_bornHost);
//                //printf("mesageID: m_queueI: %d \n",i);

//            }
            ConsumeConcurrentlyStatus status =  (*fp2)(exts,len,*Ccontext);
            delete(exts);
            delete(Ccontext);
            return status;

        }

    }

    int (*fp)(Struct_MessageExt*);
    ConsumeConcurrentlyStatus (*fp2)(struct Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context);
    int consumeTimes;
    int consumerType;
    Tool tool;
};
DefaultMQPushConsumer *consumer;


void pushconsumer_init(char *consumerName) {
    consumer = new DefaultMQPushConsumer(consumerName);
//    (*consumer).setConsumerGroup(consumerName);
}

void pushconsumer_setNameServerAddr(char *nameServerAddr) {
    (*consumer).setNamesrvAddr(nameServerAddr);
}

void pushconsumer_start() {
    (*consumer).start();

}

void pushconsumer_shutdown() {
    (*consumer).shutdown();
    delete(consumer);
}

void pushconsumer_setAllocateMessageQueueStrategy(AllocateMessageQueueStrategyStatue strategyStatue) {

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
   // delete(strategy);


}

void pushconsumer_setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan) {
    (*consumer).setConsumeConcurrentlyMaxSpan(consumeConcurrentlyMaxSpan);
}

void pushconsumer_setConsumeFromWhere(ConsumeFromWhere consumeFromWhere) {
    (*consumer).setConsumeFromWhere(consumeFromWhere);
}

void pushconsumer_setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize) {
    (*consumer).setConsumeMessageBatchMaxSize(consumeMessageBatchMaxSize);

}

void pushconsumer_setConsumeThreadMax(int consumeThreadMax) {
    (*consumer).setConsumeThreadMax(consumeThreadMax);

}

void pushconsumer_setConsumeThreadMin(int consumeThreadMin) {
    (*consumer).setConsumeThreadMin(consumeThreadMin);

}

void pushconsumer_setMessageListener(int (*fp)(Struct_MessageExt*)) {
    MsgListener* listener = new MsgListener(fp);
    (*consumer).registerMessageListener(listener);

}

void pushconsumer_registerMessageListener2(ConsumeConcurrentlyStatus (*fp)(Struct_MessageExt* ext,int len,CConsumerConcurrentlyContext context)){
    MsgListener* listener = new MsgListener(fp);
    (*consumer).registerMessageListener(listener);
}


void pushconsumer_setMessageModel(MessageModel messageModel) {
    (*consumer).setMessageModel(messageModel);
}

void pushconsumer_setPullBatchSize(int pullBatchSize) {
    (*consumer).setPullBatchSize(pullBatchSize);
}

void pushconsumer_setPullInterval(long pullInterval) {
    (*consumer).setPullInterval(pullInterval);
}

void pushconsumer_setPullThresholdForQueue(int pullThresholdForQueue) {
    (*consumer).setPullThresholdForQueue(pullThresholdForQueue);
}

void pushconsumer_updateCorePoolSize(int corePoolSize){
    (*consumer).updateCorePoolSize(corePoolSize);
}

void pushconsumer_registerMessageListener(int (*fp)(Struct_MessageExt*)) {
    MsgListener* listener = new MsgListener(fp);
    (*consumer).registerMessageListener(listener);
}

void pushconsumer_subscribe(char *topic, char *subExpression) {
    (*consumer).subscribe(topic,subExpression);
}

void pushconsumer_unsubscribe(char *topic) {
    (*consumer).unsubscribe(topic);
}

void pushconsumer_setClientIP(char *clientIP) {
    (*consumer).setClientIP(clientIP);
}

void pushconsumer_setInstanceName(char *instanceName) {
    (*consumer).setInstanceName(instanceName);
}

void pushconsumer_setClientCallbackExecutorThreads(int clientCallbackExecutorThreads) {
    (*consumer).setClientCallbackExecutorThreads(clientCallbackExecutorThreads);
}

void pushconsumer_setPollNameServerInterval(int pollNameServerInterval) {
    (*consumer).setPollNameServerInterval(pollNameServerInterval);
}

void pushconsumer_setHeartbeatBrokerInterval(int heartbeatBrokerInterval) {
    (*consumer).setHeartbeatBrokerInterval(heartbeatBrokerInterval);
}

void pushconsumer_setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval) {
    (*consumer).setPersistConsumerOffsetInterval(persistConsumerOffsetInterval);
}

std::set<MessageQueue>* pushconsumer_fetchSubscribeMessageQueues(char* topic){
    return (*consumer).fetchSubscribeMessageQueues(topic);
}
void pushconsumer_setSubscription(std::map<std::string, std::string>& subscription){
    (*consumer).setSubscription(subscription);
}
