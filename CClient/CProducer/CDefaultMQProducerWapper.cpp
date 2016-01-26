//
// Created by root on 16-1-15.
//

#include <iostream>
#include <SendResult.h>
#include "CDefaultMQProducer.h"
#include "../common/Struct_SendResult.h"


//Create Producer client and set producer group name
void producer_init( std::string producerName);

//set NameServer Addr
void producer_setNameServerAddr( std::string nameServerAddr);

//start producer
void producer_start();

//shutdown producer
void producer_shutdown();

//send Message
SendResult producer_sendMessage( char* topic, char* tags,  char* keys, const char* body, int len);

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

#ifdef __cplusplus
extern "C"{
#endif
//Create Producer client and set producer group name
void m_producer_init( char* producerName){
    producer_init(producerName);
}

//set NameServer Addr
void m_producer_setNameServerAddr( char* nameServerAddr){
    producer_setNameServerAddr(nameServerAddr);
}

//start producer
void m_producer_start(){
    producer_start();
}

//shutdown producer
void m_producer_shutdown(){
    producer_shutdown();
}

//send Message
structResult m_producer_sendMessage( char* topic,  char* tags,  char* keys,  char* body, int len){
    //std::cout<<topic<<"\t"<<tags<<"\t"<<keys<<"\t"<<body<<"\t"<<len<<"\t"<<std::endl;
    std::string* sbody = new std::string(body);

    SendResult result = producer_sendMessage(topic,  tags,  keys, sbody->c_str(), sbody->size());
   //std::cout<<"result.getSendStatus():"<<result.getSendStatus()<<std::endl;

    structResult structResult1;
    structResult1.m_sendStatus = result.getSendStatus();
    structResult1.m_msgId = result.getMsgId();
    structResult1.m_brokerName = result.getMessageQueue().getBrokerName();
    structResult1.m_queueId = result.getMessageQueue().getQueueId();
    structResult1.m_topic = result.getMessageQueue().getTopic();
    structResult1.m_queueOffset = result.getQueueOffset();

    return  structResult1;

}


//在发送消息时，自动创建服务器不存在的topic，需要指定key
void m_producer_setCreateTopicKey(char* createTopicKey){
    producer_setCreateTopicKey(createTopicKey);
}
//发送信息草食时间，单位毫秒
void m_producer_setSendMsgTimeout(int sendMsgTimeout) {
    producer_setSendMsgTimeout(sendMsgTimeout);
}
//消息body超过多大时开始压缩（Consumer收到消息会自动解压缩），单位字节
void m_producer_setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch){
    producer_setCompressMsgBodyOverHowmuch(compressMsgBodyOverHowmuch);
}
//客户端限制的消息大小，超过报错，同时服务端也会限制128K
void m_producer_setMaxMessageSize(int maxMessageSize){
    producer_setMaxMessageSize(maxMessageSize);
}
//如果发送消息返回sendResult，但是SendStatus！=send_OK，是否重试发送
void m_producer_setRetryAnotherBrokerWhenNotStoreOK(bool retryAnotherBrokerWhenNotStoreOK){
    producer_setRetryAnotherBrokerWhenNotStoreOK(retryAnotherBrokerWhenNotStoreOK);
}
//发送信息时，自动chungking服务器不存在的topic，默认创建的队列数
void m_producer_setDefaultTopicQueueNums(int defaultTopicQueueNums){
    producer_setDefaultTopicQueueNums(defaultTopicQueueNums);
}

#ifdef __cplusplus
};
#endif
