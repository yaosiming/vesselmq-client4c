cmake_minimum_required(VERSION 3.2)

project(CPushConsumer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(COMMON_FILE ../common)

set(CPushConsumer_FILE ${COMMON_FILE}/Struct_SendResult.h CPushConsumer.h CPushConsumer.cpp CPushConsumerWapper.h CPushConsumerWapper.cpp ${COMMON_FILE}/Struct_MessageExt.h Tool.cpp Tool.h ${COMMON_FILE}/AllocateMessageQueueStrategyStatus.h)

LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)

add_library(CPushConsumerWapper SHARED ${CPushConsumer_FILE})


set(LIBRARY_OUTPUT_PATH /usr/lib)
# set_target_properties(jsoncpp PROPERTIES OUTPUT_NAME jsoncpp64)
