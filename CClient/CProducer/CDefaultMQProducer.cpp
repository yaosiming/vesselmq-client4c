//
// Created by root on 16-1-15.
//

// Producer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#ifdef WIN32
#   include <sys/timeb.h>
#   include <process.h>
#else

#   include <unistd.h>
#   include <sys/types.h>
#   include <signal.h>

#endif

#include <DefaultMQProducer.h>
#include <Message.h>
#include <SendResult.h>
#include <MQClientException.h>


DefaultMQProducer *producer;

inline void MySleep(long millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void Usage(const char *program) {
    printf("Usage:%s [-n] [-c] [-v]\n", program);
    printf("\t -n ip:port\n");
    printf("\t -c message count\n");
    printf("\t -v message size \n");
}
//Create Producer client and set producer group name
void producer_init( std::string producerName){
    producer = new DefaultMQProducer();
    (*producer).setProducerGroup(producerName);
}

//set NameServer Addr
void producer_setNameServerAddr( std::string nameServerAddr){
    (*producer).setNamesrvAddr(nameServerAddr);
}

//start producer
void producer_start(){
    (*producer).start();
}

//shutdown producer
void producer_shutdown(){
    (*producer).shutdown();
    delete(producer);
}

//send Message
SendResult producer_sendMessage( char* topic, char* tags,  char* keys, const char* body, int len){
    //std::cout<<topic<<"\t"<<tags<<"\t"<<keys<<"\t"<<body<<"\t"<<len<<"\t"<<std::endl;
    Message msg(topic,// topic
                tags,// tag
                keys,// key
                body,// body
                len);
    SendResult sendResult = (*producer).send(msg);
    //std::cout<<"sendResult.getSendStatus():"<<sendResult.getSendStatus()<<std::endl;
    return sendResult;
}

//在发送消息时，自动创建服务器不存在的topic，需要指定key
void producer_setCreateTopicKey(char* createTopicKey){
    (*producer).setCreateTopicKey(createTopicKey);
}
//发送信息草食时间，单位毫秒
void producer_setSendMsgTimeout(int sendMsgTimeout) {
    (*producer).setSendMsgTimeout(sendMsgTimeout);
}
//消息body超过多大时开始压缩（Consumer收到消息会自动解压缩），单位字节
void producer_setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch){
    (*producer).setCompressMsgBodyOverHowmuch(compressMsgBodyOverHowmuch);
}
//客户端限制的消息大小，超过报错，同时服务端也会限制128K
void producer_setMaxMessageSize(int maxMessageSize){
    (*producer).setMaxMessageSize(maxMessageSize);
}
//如果发送消息返回sendResult，但是SendStatus！=send_OK，是否重试发送
void producer_setRetryAnotherBrokerWhenNotStoreOK(bool retryAnotherBrokerWhenNotStoreOK){
    (*producer).setRetryAnotherBrokerWhenNotStoreOK(retryAnotherBrokerWhenNotStoreOK);
}
//发送信息时，自动chungking服务器不存在的topic，默认创建的队列数
void producer_setDefaultTopicQueueNums(int defaultTopicQueueNums){
    (*producer).setDefaultTopicQueueNums(defaultTopicQueueNums);
}