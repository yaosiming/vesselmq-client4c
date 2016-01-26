//
// Created by root on 16-1-21.
//

#ifndef ROCKETMQ_STRUCT_PULLRESULT_H
#define ROCKETMQ_STRUCT_PULLRESULT_H

#include <PullResult.h>
#include "Struct_MessageExt.h"

struct SPullresult{
    PullStatus pullStatus;
    long long nextBeginOffset;
    long long minOffset;
    long long maxOffset;
    Struct_MessageExt* msgFoundList;
    int len;
};

#endif //ROCKETMQ_STRUCT_PULLRESULT_H
