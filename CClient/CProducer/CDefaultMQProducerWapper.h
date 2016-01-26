//
// Created by root on 16-1-15.
//

#ifndef ROCKETMQ_CDEFAULTMQPRODUCERWAPPER_H
#define ROCKETMQ_CDEFAULTMQPRODUCERWAPPER_H


#include "../common/Struct_SendResult.h"

#ifdef __cplusplus
extern "C"{
#endif
#include <SendResult.h>

//Create Producer client and set producer group name
void m_producer_init( char* producerName);

//set NameServer Addr
void m_producer_setNameServerAddr( char* nameServerAddr);

//start producer
void m_producer_start();

//shutdown producer
void m_producer_shutdown();

//send Message
structResult m_producer_sendMessage( char* topic,  char* tags,  char* keys,  char* body, int len);

//在发送消息时，自动创建服务器不存在的topic，需要指定key
void m_producer_setCreateTopicKey(char* createTopicKey);
//发送信息草食时间，单位毫秒
void m_producer_setSendMsgTimeout(int sendMsgTimeout) ;
//消息body超过多大时开始压缩（Consumer收到消息会自动解压缩），单位字节
void m_producer_setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch);
//客户端限制的消息大小，超过报错，同时服务端也会限制128K
void m_producer_setMaxMessageSize(int maxMessageSize);
//如果发送消息返回sendResult，但是SendStatus！=send_OK，是否重试发送
void m_producer_setRetryAnotherBrokerWhenNotStoreOK(bool retryAnotherBrokerWhenNotStoreOK);
//发送信息时，自动chungking服务器不存在的topic，默认创建的队列数
void m_producer_setDefaultTopicQueueNums(int defaultTopicQueueNums);

#ifdef __cplusplus
};
#endif

#endif //ROCKETMQ_CDEFAULTMQPRODUCERWAPPER_H
