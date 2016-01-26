//
// Created by root on 16-1-15.
//

#ifndef ROCKETMQ_CDEFAULTMQPRODUCER_H
#define ROCKETMQ_CDEFAULTMQPRODUCER_H

#include <iostream>
#include <SendResult.h>

//Create Producer client and set producer group name
void producer_init( std::string producerName);

//set NameServer Addr
void producer_setNameServerAddr( std::string nameServerAddr);

//start producer
void producer_start();

//shutdown producer
void producer_shutdown();

//send Message
SendResult producer_sendMessage( char* topic, char* tags,  char* keys,const  char* body, int len);

//在发送消息时，自动创建服务器不存在的topic，需要指定key
void producer_setCreateTopicKey(char* createTopicKey);
//发送信息草食时间，单位毫秒
void producer_setSendMsgTimeout(int sendMsgTimeout) ;
//消息body超过多大时开始压缩（Consumer收到消息会自动解压缩），单位字节
void producer_setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch);
//客户端限制的消息大小，超过报错，同时服务端也会限制128K
void producer_setMaxMessageSize(int maxMessageSize);
//如果发送消息返回sendResult，但是SendStatus！=send_OK，是否重试发送
void producer_setRetryAnotherBrokerWhenNotStoreOK(bool retryAnotherBrokerWhenNotStoreOK);
//发送信息时，自动chungking服务器不存在的topic，默认创建的队列数
void producer_setDefaultTopicQueueNums(int defaultTopicQueueNums);


#endif //ROCKETMQ_CDEFAULTMQPRODUCER_H
