cmake_minimum_required(VERSION 3.2)

project(common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CCLIENT_FILE Struct_SendResult.h tool.h tool.cpp)

LINK_LIBRARIES(rocketmq)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(z)
LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(curl)



# set_target_properties(jsoncpp PROPERTIES OUTPUT_NAME jsoncpp64)
