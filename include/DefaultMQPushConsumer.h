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
#if!defined __DEFAULTMQPUSHCONSUMER_H__
#define __DEFAULTMQPUSHCONSUMER_H__

#include <list>
#include <string>

#include "MQPushConsumer.h"
#include "MessageExt.h"
#include "ClientConfig.h"
#include "RocketMQClient.h"

class AllocateMessageQueueStrategy;
class DefaultMQPushConsumerImpl;
class OffsetStore;

/**
* ������Broker Push��Ϣ��Consumer��ʽ����ʵ����Ȼ��Consumer�ڲ���̨��Broker Pull��Ϣ<br>
* ���ó���ѯ��ʽ����Ϣ��ʵʱ��ͬpush��ʽһ�£��Ҳ�����ν������Ϣ����Broker��Consumerѹ������
*
*/
class ROCKETMQCLIENT_API DefaultMQPushConsumer : public ClientConfig ,public MQPushConsumer
{
public:
	DefaultMQPushConsumer();
	DefaultMQPushConsumer(const std::string& consumerGroup);
	~DefaultMQPushConsumer();

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
	
	int getConsumeConcurrentlyMaxSpan();
	void setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan);

	ConsumeFromWhere getConsumeFromWhere();
	void setConsumeFromWhere(ConsumeFromWhere consumeFromWhere);

	int getConsumeMessageBatchMaxSize();
	void setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize);

	std::string getConsumerGroup();
	void setConsumerGroup(const std::string& consumerGroup) ;

	int getConsumeThreadMax() ;
	void setConsumeThreadMax(int consumeThreadMax);

	int getConsumeThreadMin();
	void setConsumeThreadMin(int consumeThreadMin);

	MessageListener* getMessageListener();
	void setMessageListener(MessageListener* pMessageListener);

	MessageModel getMessageModel();
	void setMessageModel(MessageModel messageModel) ;

	int getPullBatchSize() ;
	void setPullBatchSize(int pullBatchSize);

	long getPullInterval();
	void setPullInterval(long pullInterval);

	int getPullThresholdForQueue();
	void setPullThresholdForQueue(int pullThresholdForQueue);

	std::map<std::string, std::string>& getSubscription();
	void setSubscription(const std::map<std::string, std::string>& subscription);

	//MQConsumer
	void sendMessageBack(MessageExt& msg, int delayLevel);
	std::set<MessageQueue>* fetchSubscribeMessageQueues(const std::string& topic);

	void start();
	void shutdown();
	//MQConsumer end
	
	//MQPushConsumer
	void registerMessageListener(MessageListener* pMessageListener);

	void subscribe(const std::string& topic, const std::string& subExpression);
	void unsubscribe(const std::string& topic);

	void updateCorePoolSize(int corePoolSize);

	void suspend() ;
	void resume();
	//MQPushConsumer end

	OffsetStore* getOffsetStore();
	void setOffsetStore(OffsetStore* offsetStore);

	DefaultMQPushConsumerImpl* getDefaultMQPushConsumerImpl();

protected:
	DefaultMQPushConsumerImpl* m_pDefaultMQPushConsumerImpl;

private:
	/**
	* ��ͬ�������Consumer��Ϊͬһ��Group��Ӧ�ñ������ã�����֤����Ψһ
	*/
	std::string m_consumerGroup;

	/**
	* ��Ⱥ����/�㲥����
	*/
	MessageModel m_messageModel;

	/**
	* Consumer����ʱ�������￪ʼ����
	*/
	ConsumeFromWhere m_consumeFromWhere;

	/**
	* ���з����㷨��Ӧ�ÿ���д
	*/
	AllocateMessageQueueStrategy* m_pAllocateMessageQueueStrategy ;

	/**
	* ���Ĺ�ϵ
	*/
	std::map<std::string /* topic */, std::string /* sub expression */> m_subscription ;

	/**
	* ��Ϣ������
	*/
	MessageListener* m_pMessageListener;

	/**
	* Offset�洢��ϵͳ����ݿͻ��������Զ�������Ӧ��ʵ�֣����Ӧ�������ˣ�����Ӧ�����õ�Ϊ��
	*/
	OffsetStore* m_pOffsetStore;

	/**
	* ������Ϣ�̣߳���С��Ŀ
	*/
	int m_consumeThreadMin;

	/**
	* ������Ϣ�̣߳������Ŀ
	*/
	int m_consumeThreadMax;

	/**
	* ͬһ���в������ѵ�����ȣ�˳�����ѷ�ʽ����£��˲�����Ч
	*/
	int m_consumeConcurrentlyMaxSpan;

	/**
	* ���ض�����Ϣ�������˷�ֵ����ʼ����
	*/
	int m_pullThresholdForQueue;

	/**
	* ����Ϣ��������Ϊ�˽�����ȡ�ٶȣ��������ô���0��ֵ
	*/
	long m_pullInterval;

	/**
	* ����һ����Ϣ�������
	*/
	int m_consumeMessageBatchMaxSize;

	/**
	* ����Ϣ��һ����������
	*/
	int m_pullBatchSize;
};

#endif
