/**
* Copyright (C) 2013 kangliqiang ,kangliq@163.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#if!defined __DEFAULTMQPULLCONSUMER_H__
#define __DEFAULTMQPULLCONSUMER_H__

#include <list>
#include <string>

#include "MessageQueue.h"
#include "MessageExt.h"
#include "ClientConfig.h"
#include "MQPullConsumer.h"
#include "RocketMQClient.h"

class OffsetStore;
class DefaultMQPullConsumerImpl;
class AllocateMessageQueueStrategy;

/**
* �����ߣ�������ȡ��ʽ����
*
*/
class ROCKETMQCLIENT_API DefaultMQPullConsumer : public ClientConfig , public MQPullConsumer
{
public:
	DefaultMQPullConsumer();
	DefaultMQPullConsumer(const std::string& consumerGroup);
	~DefaultMQPullConsumer();

	//MQAdmin
	void createTopic(const std::string& key, const std::string& newTopic, int queueNum);
	long long searchOffset(const MessageQueue& mq, long long timestamp);
	long long maxOffset(const MessageQueue& mq);
	long long minOffset(const MessageQueue& mq);
	long long earliestMsgStoreTime(const MessageQueue& mq);
	MessageExt viewMessage(const std::string& msgId);
	QueryResult queryMessage(const std::string& topic,
							 const std::string&  key,
							 int maxNum,
							 long long begin,
							 long long end);
	// MQadmin end

	AllocateMessageQueueStrategy* getAllocateMessageQueueStrategy();
	void setAllocateMessageQueueStrategy(AllocateMessageQueueStrategy* pAllocateMessageQueueStrategy);
	int getBrokerSuspendMaxTimeMillis() ;
	void setBrokerSuspendMaxTimeMillis(int brokerSuspendMaxTimeMillis);
	std::string getConsumerGroup();
	void setConsumerGroup(const std::string& consumerGroup);
	int getConsumerPullTimeoutMillis();
	void setConsumerPullTimeoutMillis(int consumerPullTimeoutMillis);
	int getConsumerTimeoutMillisWhenSuspend() ;
	void setConsumerTimeoutMillisWhenSuspend(int consumerTimeoutMillisWhenSuspend);
	MessageModel getMessageModel();
	void setMessageModel(MessageModel messageModel);
	MessageQueueListener* getMessageQueueListener();
	void setMessageQueueListener(MessageQueueListener* pMessageQueueListener);
	std::set<std::string> getRegisterTopics();
	void setRegisterTopics( std::set<std::string> registerTopics);
	//MQConsumer
	void sendMessageBack(MessageExt& msg, int delayLevel);
	std::set<MessageQueue>* fetchSubscribeMessageQueues(const std::string& topic);
	void start();
	void shutdown() ;
	//MQConsumer end

	//MQPullConsumer
	void registerMessageQueueListener(const std::string& topic, MessageQueueListener* pListener);
	PullResult* pull(MessageQueue& mq, const std::string& subExpression, long long offset,int maxNums);
	void pull(MessageQueue& mq,
		const std::string& subExpression,
		long long offset,
		int maxNums,
		PullCallback* pPullCallback);

	PullResult* pullBlockIfNotFound(MessageQueue& mq,
		const std::string& subExpression,
		long long offset,
		int maxNums);

	void pullBlockIfNotFound(MessageQueue& mq,
							 const std::string& subExpression,
							 long long offset,
							 int maxNums,
							 PullCallback* pPullCallback);

	void updateConsumeOffset(MessageQueue& mq, long long offset);

	long long fetchConsumeOffset(MessageQueue& mq, bool fromStore);

	std::set<MessageQueue*> fetchMessageQueuesInBalance(const std::string& topic);
	//MQPullConsumer end

	OffsetStore* getOffsetStore();
	void setOffsetStore(OffsetStore* offsetStore);

	DefaultMQPullConsumerImpl* getDefaultMQPullConsumerImpl();

protected:
	DefaultMQPullConsumerImpl* m_pDefaultMQPullConsumerImpl;

private:
	/**
	* ��ͬ�������Consumer��Ϊͬһ��Group��Ӧ�ñ������ã�����֤����Ψһ
	*/
	std::string m_consumerGroup;

	/**
	* ����ѯģʽ��Consumer������Broker�����ʱ�䣬�������޸�
	*/
	int m_brokerSuspendMaxTimeMillis ;

	/**
	* ����ѯģʽ��Consumer��ʱʱ�䣨����Ҫ����brokerSuspendMaxTimeMillis�����������޸�
	*/
	int m_consumerTimeoutMillisWhenSuspend;

	/**
	* ��������ģʽ��Consumer��ʱʱ�䣬�������޸�
	*/
	int m_consumerPullTimeoutMillis;

	/**
	* ��Ⱥ����/�㲥����
	*/
	MessageModel m_messageModel;

	/**
	* ���б仯������
	*/
	MessageQueueListener* m_pMessageQueueListener;

	/**
	* Offset�洢��ϵͳ����ݿͻ��������Զ�������Ӧ��ʵ�֣����Ӧ�������ˣ�����Ӧ�����õ�Ϊ��
	*/
	OffsetStore* m_pOffsetStore;

	/**
	* ��Ҫ������ЩTopic�Ķ��б仯
	*/
	std::set<std::string> m_registerTopics;

	/**
	* ���з����㷨��Ӧ�ÿ���д
	*/
	AllocateMessageQueueStrategy* m_pAllocateMessageQueueStrategy;
};

#endif
