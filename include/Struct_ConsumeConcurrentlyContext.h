//
// Created by root on 16-1-22.
//

#ifndef ROCKETMQ_STRUCT_CONSUMECONCURRENTLYCONTEXT_H
#define ROCKETMQ_STRUCT_CONSUMECONCURRENTLYCONTEXT_H

#include "Struct_MessageQueues.h"

typedef struct CConsumerConcurrentlyContext{
    SMessageQueues messageQueue;///< 要消费的消息属于哪个队列
    /**
    * 下次消息重试延时时间<br>
    * -1，表示不重试，直接进入死信队列<br>
    * 0，表示由服务器根据重试次数自动叠加<br>
    * >0，表示客户端强制指定延时Level
    */
    int delayLevelWhenNextConsume;
    int ackIndex;///< 对于批量消费，ack至哪条消息，默认全部ack，至最后一条消息
};
#endif //ROCKETMQ_STRUCT_CONSUMECONCURRENTLYCONTEXT_H
