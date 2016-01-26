cmake_minimum_required(VERSION 3.2)
project(rocketmq)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)

find_library(CURL NAMES curl)
find_library(Z_LIB NAMES z)

add_subdirectory(libs/jsoncpp-src-0.5.0)
add_subdirectory(libs/spdlog)

include_directories(libs/jsoncpp/include)
include_directories(libs/zlib/include)

include_directories(include)
include_directories(src)
include_directories(src/common)
include_directories(src/consumer)
include_directories(src/kpr)
include_directories(src/message)
include_directories(src/producer)
include_directories(src/protocol)
include_directories(src/transport)

set(SOURCE_FILES
        src/common/MessageSysFlag.cpp
        src/common/MixAll.cpp
        src/common/MQVersion.cpp
        src/common/PermName.cpp
        src/common/PullSysFlag.cpp
        src/common/SendResult.cpp
        src/common/ServiceThread.cpp
        src/common/TopicConfig.cpp
        src/common/Validators.cpp
        src/common/VirtualEnvUtil.cpp
        src/consumer/ConsumeMessageConcurrentlyService.cpp
        src/consumer/ConsumeMessageOrderlyService.cpp
        src/consumer/ConsumerInvokeCallback.cpp
        src/consumer/ConsumeType.cpp
        src/consumer/DefaultMQPullConsumer.cpp
        src/consumer/DefaultMQPullConsumerImpl.cpp
        src/consumer/DefaultMQPushConsumer.cpp
        src/consumer/DefaultMQPushConsumerImpl.cpp
        src/consumer/LocalFileOffsetStore.cpp
        src/consumer/ProcessQueue.cpp
        src/consumer/PullAPIWrapper.cpp
        src/consumer/PullMessageService.cpp
        src/consumer/PullRequest.cpp
        src/consumer/RebalanceImpl.cpp
        src/consumer/RebalancePullImpl.cpp
        src/consumer/RebalancePushImpl.cpp
        src/consumer/RebalanceService.cpp
        src/consumer/RemoteBrokerOffsetStore.cpp
        src/consumer/SubscriptionData.cpp
        src/kpr/AtomicValue.cpp
        src/kpr/Condition.cpp
        src/kpr/KPRUtil.cpp
        src/kpr/Monitor.cpp
        src/kpr/Mutex.cpp
        src/kpr/RefCount.cpp
        src/kpr/Semaphore.cpp
        src/kpr/Thread.cpp
        src/kpr/ThreadLocal.cpp
        src/kpr/ThreadPool.cpp
        src/kpr/TimerTaskManager.cpp
        src/kpr/TimerThread.cpp
        src/message/Message.cpp
        src/message/MessageDecoder.cpp
        src/message/MessageExt.cpp
        src/message/MessageQueue.cpp
        src/producer/DefaultMQProducer.cpp
        src/producer/DefaultMQProducerImpl.cpp
        src/producer/ProducerInvokeCallback.cpp
        src/protocol/CommandCustomHeader.cpp
        src/protocol/HeartbeatData.cpp
        src/protocol/LockBatchBody.cpp
        src/protocol/RemotingCommand.cpp
        src/transport/ResponseFuture.cpp
        src/transport/SocketUtil.cpp
        src/transport/TcpRemotingClient.cpp
        src/transport/TcpTransport.cpp
        src/ClientConfig.cpp
        src/ClientRemotingProcessor.cpp
        src/dllmain.cpp
        src/MQAdminImpl.cpp
        src/MQClientAPIImpl.cpp
        src/MQClientFactory.cpp
        src/MQClientManager.cpp
        src/Logger.cpp)

add_library(rocketmq SHARED ${SOURCE_FILES})

target_link_libraries(rocketmq jsoncpp)

if(CURL)
    LINK_LIBRARIES(curl)
    message(STATUS "Found curl")
endif()

if(Z_LIB)
    LINK_LIBRARIES(z)
    message(STATUS "Found zlib")
endif()

target_link_libraries(rocketmq spdlog)

install(TARGETS rocketmq
        LIBRARY DESTINATION /usr/lib)
install(DIRECTORY include/
        DESTINATION /usr/include/rocketmq)

add_subdirectory(example/simple)
add_subdirectory(CClient)