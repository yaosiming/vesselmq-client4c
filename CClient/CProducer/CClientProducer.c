//
// Created by root on 16-1-15.
//

#include <stdio.h>
#include <dlfcn.h>
#include <Struct_SendResult.h>
#include <CDefaultMQProducerWapper.h>

extern void m_producer_init( char* producerName);

//set NameServer Addr
extern void m_producer_setNameServerAddr( char* nameServerAddr);

//start producer
extern void m_producer_start();

//shutdown producer
extern void m_producer_shutdown();

//send Message
extern structResult m_producer_sendMessage( char* topic,  char* tags,  char* keys,  char* body, int len);

//在发送消息时，自动创建服务器不存在的topic，需要指定key
extern void m_producer_setCreateTopicKey(char* createTopicKey);
//发送信息草食时间，单位毫秒
extern void m_producer_setSendMsgTimeout(int sendMsgTimeout) ;
//消息body超过多大时开始压缩（Consumer收到消息会自动解压缩），单位字节
extern void m_producer_setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch);
//客户端限制的消息大小，超过报错，同时服务端也会限制128K
extern void m_producer_setMaxMessageSize(int maxMessageSize);
//如果发送消息返回sendResult，但是SendStatus！=send_OK，是否重试发送
extern void m_producer_setRetryAnotherBrokerWhenNotStoreOK(bool retryAnotherBrokerWhenNotStoreOK);
//发送信息时，自动chungking服务器不存在的topic，默认创建的队列数
extern void m_producer_setDefaultTopicQueueNums(int defaultTopicQueueNums);


int main(){
    int i=0;
    char key[16] = "key1";
    char producerName[] = "group1";
    char NameServerAddr[] = "127.0.0.1:9876";
     char value[] = "this is my C rocketmq client!";
     char topic[] = "testTopicC";
     char TagA[] = "TagA";
    printf("hello world! this is CClientProducer \n");
    m_producer_init(producerName);
    m_producer_setNameServerAddr(NameServerAddr);
    m_producer_setSendMsgTimeout(10000);
    m_producer_setCompressMsgBodyOverHowmuch(4096);
    m_producer_setMaxMessageSize(1024*128);
    m_producer_setRetryAnotherBrokerWhenNotStoreOK(false);
    m_producer_setDefaultTopicQueueNums(4);
    m_producer_start();
    for(i=0;i<1000000;i++){
        sprintf(key, "KEY%d", i);
        structResult result = m_producer_sendMessage(topic,TagA, key, value,strlen(value));
        if(i%100000==0)
        printf("send  %d succeed; sendResult:%d \n",i,result.m_sendStatus);

    }
    m_producer_shutdown();
    return 0;
}
