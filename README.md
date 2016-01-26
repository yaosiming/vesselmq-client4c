[RocketMQ](https://github.com/alibaba/RocketMQ)  C Client
===================

### 主要贡献者
* @[Kang Liqiang](https://github.com/kangliqiang)
* @[Wang Xiaorui](https://github.com/vintagewang)
* @[Li Zhanhui](https://github.com/lizhanhui)
* @[Yao siming](https://github.com/yaosiming)

### 目前现状
* 支持同步、异步发送消息， Pull和Push方式消费消息.
* API还不完善.
* 支持SSL传输
* * C客户端中取消ssl支持

### 发展规划
* 支持完整的RocketMQ客户端功能,包括发送与接收及其他高级接口.
* 完善日志以详尽记录系统运行状态.
* 用RapidJson替换当前的jsoncpp库.
* 使用std:unique_ptr, std:shared_ptr代替现有的指针操作.
* 使用C++11的同步semantic替换当前的kpr库, 重构代码.
* 增加系统可配执行, 比如log目录, SSL key目录等.
* add new authorization management

### Development/Deployment Guide
* 参看README.txt文档
