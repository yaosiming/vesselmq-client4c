cmake_minimum_required(VERSION 3.2)

project(CClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CPRODUCER_FILE CProducer.cpp )
set(CPPFIlE CClientProducer.cpp common/Struct_MessageQueues.h common/MapData.h common/Struct_PullResult.h common/Struct_ConsumeConcurrentlyContext.h)

add_subdirectory(common)
add_subdirectory(CProducer)
add_subdirectory(CPushConsumer)
add_subdirectory(CPullConsumer)

include_directories(common)
include_directories(CProducer)
include_directories(CPushConsumer)
include_directories(CPullConsumer)

LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)
LINK_LIBRARIES(CDefaultMQProducerWapper)



add_executable(CClientProducercpp  ${CPPFIlE})