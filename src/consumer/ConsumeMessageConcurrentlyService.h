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

#if!defined __CONSUMEMESSAGECONCURRENTLYSERVICE_H__
#define __CONSUMEMESSAGECONCURRENTLYSERVICE_H__

#include "ConsumeMessageService.h"

#include <list>
#include <string>

#include "MessageQueueLock.h"
#include "ConsumerStatManage.h"
#include "MessageExt.h"
#include "MessageListener.h"
#include "ProcessQueue.h"
#include "ThreadPool.h"
#include "TimerThread.h"

class DefaultMQPushConsumerImpl;
class DefaultMQPushConsumer;
class MessageListenerConcurrently;
class ConsumeMessageConcurrentlyService;

class ConsumeConcurrentlyRequest: public ThreadPoolWork
{
public:
	ConsumeConcurrentlyRequest(std::list<MessageExt*>& msgs,
		ProcessQueue* pProcessQueue,
		MessageQueue& messageQueue,
		ConsumeMessageConcurrentlyService* pService);
	~ConsumeConcurrentlyRequest();
	virtual void Do();

	std::list<MessageExt*>& getMsgs()
	{
		return m_msgs;
	}

	ProcessQueue* getProcessQueue()
	{
		return m_pProcessQueue;
	}

	MessageQueue getMessageQueue()
	{
		return m_messageQueue;
	}

private:
	void resetRetryTopic(std::list<MessageExt*>& msgs);

private:
	std::list<MessageExt*> m_msgs;
	ProcessQueue* m_pProcessQueue;
	MessageQueue m_messageQueue;
	ConsumeMessageConcurrentlyService* m_pService;
};

/**
* ����������Ϣ����
* 
*/
class ConsumeMessageConcurrentlyService : public ConsumeMessageService
{
public:
	ConsumeMessageConcurrentlyService(DefaultMQPushConsumerImpl* pDefaultMQPushConsumerImpl,
		MessageListenerConcurrently* pMessageListener);

	void start();
	void shutdown();
	ConsumerStat& getConsumerStat();
	bool sendMessageBack(MessageExt& msg, ConsumeConcurrentlyContext& context);
	void processConsumeResult(ConsumeConcurrentlyStatus status,
							  ConsumeConcurrentlyContext& context,
							  ConsumeConcurrentlyRequest& consumeRequest);
	/**
	* ��Consumer���ض�ʱ�߳��ж�ʱ����
	*/
	void submitConsumeRequestLater(std::list<MessageExt*>& pMsgs,
		ProcessQueue* pProcessQueue,
		MessageQueue& messageQueue);

	void submitConsumeRequest(std::list<MessageExt*>& pMsgs,
		ProcessQueue* pProcessQueue,
		MessageQueue& messageQueue,
		bool dispathToConsume);

	void updateCorePoolSize(int corePoolSize);

	std::string& getConsumerGroup();
	MessageListenerConcurrently* getMessageListener();
	DefaultMQPushConsumerImpl* getDefaultMQPushConsumerImpl();

private:
	DefaultMQPushConsumerImpl* m_pDefaultMQPushConsumerImpl;
	DefaultMQPushConsumer* m_pDefaultMQPushConsumer;
	MessageListenerConcurrently* m_pMessageListener;
	std::string m_consumerGroup;
	kpr::ThreadPool* m_pConsumeExecutor;
	kpr::TimerThread_var m_scheduledExecutorService;
};

#endif
