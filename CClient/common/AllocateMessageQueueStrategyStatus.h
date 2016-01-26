//
// Created by root on 16-1-19.
//

#ifndef ROCKETMQ_ALLOCATEMESSAGEQUEUESTRATEGYSTATUS_H
#define ROCKETMQ_ALLOCATEMESSAGEQUEUESTRATEGYSTATUS_H
enum AllocateMessageQueueStrategyStatue{
    //1 Consumer队列自动分配策略,平均分配队列算法
    AllocateMessageQueueAveragely_Statue,
    //2 按照配置来分配队列
    AllocateMessageQueueByConfig_Statue,
    //3 按照机房来分配队列
    AllocateMessageQueueByMachineRoom_Statue
};
#endif //ROCKETMQ_ALLOCATEMESSAGEQUEUESTRATEGYSTATUS_H
