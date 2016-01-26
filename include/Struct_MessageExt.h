//
// Created by root on 16-1-18.
//

#ifndef ROCKETMQ_MESSAGEEXTS_H
#define ROCKETMQ_MESSAGEEXTS_H
//MessageExt -> struct
struct Struct_MessageExt{
    long long m_queueOffset;// 队列偏移量
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
    char* m_topic;
};
#endif //ROCKETMQ_MESSAGEEXTS_H
