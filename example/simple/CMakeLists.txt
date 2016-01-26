cmake_minimum_required(VERSION 3.2)

project(simple)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(PRODUCER_FILES Producer.cpp)

set(ASYNC_PRODUCER_FILES AsyncProducer.cpp )

set(PUSH_CONSUMER_FILES PushConsumer.cpp)

set(PULL_CONSUMER_FILES PullConsumer.cpp)


LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)


add_executable(producer ${PRODUCER_FILES})

add_executable(async_producer ${ASYNC_PRODUCER_FILES})

add_executable(push_consumer ${PUSH_CONSUMER_FILES})

add_executable(pull_consumer ${PULL_CONSUMER_FILES})