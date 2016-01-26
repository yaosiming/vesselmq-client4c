cmake_minimum_required(VERSION 3.2)

project(CPullConsumer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(COMMON_FILE ../common)

set(CPushConsumer_FILE ../common/Struct_SendResult.h CPullConsumer.h CPullConsumer.cpp CPullConsumerWapper.h ../CPushConsumer/Tool.cpp CPullConsumerWapper.cpp )

LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)

add_library(CPullConsumerWapper SHARED ${CPushConsumer_FILE})

set(LIBRARY_OUTPUT_PATH /usr/lib)
