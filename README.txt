Development/Deployment Guide

0. Dependent Libraries
   openssl optional, SSL feature relies on it.
   curl required.
   zlib required.

   For ubuntu users, please refer to the following commands
   sudo apt-get install libssl-dev
   sudo apt-get install libcurl4-nss-dev
   sudo apt-get install zlib1g-dev

1. Create directory "build" along with this file.
   mkdir build

2. Build and install jsoncpp and spdlog
   1) install spdlog
   cd libs/spdlog
   mkdir build
   cd build
   cmake ..
   make
   sudo make install

   2) install jsoncpp
   cd libs/jsoncpp-src-0.5.0
   mkdir build
   cd build
   cmake ..
   make
   sudo make install

3. Update CMake Build Scripts.
   To disable SSL feature(If you are using Brokers forked from github.com/alibaba/rocketmq, you need to do this):
   1) Delete this line in CMakeLists.txt "add_definitions(-DOPEN_SSL)"
   2) Delete this line in example/simple/CMakeFiles.txt "LINK_LIBRARIES(ssl)"

   To enable SSL feature, copy docs/cacerts/* to /dianyi/config/RocketMQ/SSL/

4. Build with CMake
   cd build
   cmake ..
   make
   sudo make install

5. Create /dianyi/log folder, make sure it's writable to current user.


6. lalall
