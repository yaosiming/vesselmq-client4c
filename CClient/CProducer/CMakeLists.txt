cmake_minimum_required(VERSION 3.2)

project(CProducer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CCLIENT_FILE CDefaultMQProducer.cpp CDefaultMQProducerWapper.cpp ../common/Struct_SendResult.h)

LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)

add_library(CDefaultMQProducerWapper SHARED ${CCLIENT_FILE})

set(LIBRARY_OUTPUT_PATH /usr/lib)
# set_target_properties(jsoncpp PROPERTIES OUTPUT_NAME jsoncpp64)
