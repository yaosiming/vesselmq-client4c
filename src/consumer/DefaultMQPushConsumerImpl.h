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

#if!defined __DEFAULTMQPUSHCONSUMERIMPL_H__
#define __DEFAULTMQPUSHCONSUMERIMPL_H__

#include <string>
#include <set>
#include <map>
#include <chrono>

#include "MQConsumerInner.h"
#include "MessageExt.h"
#include "QueryResult.h"
#include "ServiceState.h"
#include "PullResult.h"
#include "ConsumeMessageHook.h"
#include "MixAll.h"
#include "Logger.h"
#include "DefaultMQPushConsumer.h"
#include "ConsumerStatManage.h"
#include "DefaultMQPullConsumer.h"
#include "DefaultMQProducer.h"
#include "MQClientFactory.h"
#include "MQAdminImpl.h"
#include "RebalancePushImpl.h"
#include "MQClientAPIImpl.h"
#include "OffsetStore.h"
#include "MQClientManager.h"
#include "LocalFileOffsetStore.h"
#include "RemoteBrokerOffsetStore.h"
#include "PullSysFlag.h"
#include "FilterAPI.h"
#include "PullAPIWrapper.h"
#include "MQClientException.h"
#include "Validators.h"
#include "MessageListener.h"
#include "PullMessageService.h"
#include "ConsumeMessageOrderlyService.h"
#include "ConsumeMessageConcurrentlyService.h"
#include "KPRUtil.h"


class DefaultMQPushConsumer;
class ConsumeMessageHook;

class OffsetStore;
class RebalanceImpl;
class ConsumerStatManager;
class ConsumeMessageService;
class MessageListener;
class PullRequest;
class MQClientFactory;
class PullAPIWrapper;
class PullMessageService;
class DefaultMQPushConsumerImplCallback;

/**
* Push��ʽ��Consumerʵ��
*
*/
class DefaultMQPushConsumerImpl : public  MQConsumerInner
{
public:
	DefaultMQPushConsumerImpl(DefaultMQPushConsumer* pDefaultMQPushConsumer);
	
	void start();
	void suspend();
	void resume();
	void shutdown();
	bool isPause();
	void setPause(bool pause);

	bool hasHook();
	void registerHook(ConsumeMessageHook* pHook);
	void executeHookBefore(ConsumeMessageContext& context);
	void executeHookAfter(ConsumeMessageContext& context);

	void createTopic(const std::string& key, const std::string& newTopic, int queueNum);
	std::set<MessageQueue>* fetchSubscribeMessageQueues(const std::string& topic);

	long long earliestMsgStoreTime(const MessageQueue& mq);
	long long maxOffset(const MessageQueue& mq);
	long long minOffset(const MessageQueue& mq);
	OffsetStore* getOffsetStore() ;
	void setOffsetStore(OffsetStore* pOffsetStore);

	//MQConsumerInner
	std::string groupName() ;
	MessageModel messageModel() ;
	ConsumeType consumeType();
	ConsumeFromWhere consumeFromWhere();
	std::set<SubscriptionData> subscriptions();
	void doRebalance() ;
	void persistConsumerOffset() ;
	void updateTopicSubscribeInfo(const std::string& topic, const std::set<MessageQueue>& info);
	std::map<std::string, SubscriptionData>& getSubscriptionInner() ;
	bool isSubscribeTopicNeedUpdate(const std::string& topic);

	MessageExt viewMessage(const std::string& msgId);
	QueryResult queryMessage(const std::string& topic,
							 const std::string&  key,
							 int maxNum,
							 long long begin,
							 long long end);

	void registerMessageListener(MessageListener* pMessageListener);
	long long searchOffset(const MessageQueue& mq, long long timestamp);
	void sendMessageBack(MessageExt& msg, int delayLevel);

	void subscribe(const std::string& topic, const std::string& subExpression);
	void unsubscribe(const std::string& topic);

	void updateConsumeOffset(MessageQueue& mq, long long offset);
	void updateCorePoolSize(int corePoolSize);
	bool isConsumeOrderly();
	void setConsumeOrderly(bool consumeOrderly);
	
	RebalanceImpl* getRebalanceImpl() ;
	MessageListener* getMessageListenerInner();
	DefaultMQPushConsumer* getDefaultMQPushConsumer() ;
	ConsumerStatManager* getConsumerStatManager();

private:
	/**
	* ͨ��Tag����ʱ�������offset��׼ȷ���������Ҫ����
	*/
	void correctTagsOffset(PullRequest& pullRequest) ;

	void pullMessage(PullRequest* pPullRequest);

	/**
	* ����ִ�����PullRequest
	*/
	void executePullRequestImmediately(PullRequest* pullRequest);

	/**
	* �Ժ���ִ�����PullRequest
	*/
	void executePullRequestLater(PullRequest* pullRequest, long timeDelay);

	void makeSureStateOK();	
	void checkConfig();
	void copySubscription() ;
	void updateTopicSubscribeInfoWhenSubscriptionChanged();	

private:
	static long long s_PullTimeDelayMillsWhenException;// ����Ϣ�쳣ʱ���ӳ�һ��ʱ������
	static long long s_PullTimeDelayMillsWhenFlowControl;
	static long long s_PullTimeDelayMillsWhenSuspend;

	static long long s_BrokerSuspendMaxTimeMillis;// ����ѯģʽ��Consumer������Broker�����ʱ��
	static long long s_ConsumerTimeoutMillisWhenSuspend;// ����ѯģʽ��Consumer��ʱʱ�䣨����Ҫ����brokerSuspendMaxTimeMillis��
	
	long long flowControlTimes1;
	long long flowControlTimes2;
	ServiceState m_serviceState;
	volatile bool m_pause;// �Ƿ���ͣ������Ϣ suspend/resume
	bool m_consumeOrderly;// �Ƿ�˳��������Ϣ
	DefaultMQPushConsumer* m_pDefaultMQPushConsumer;
	MQClientFactory* m_pMQClientFactory;
	PullAPIWrapper* m_pPullAPIWrapper;
	MessageListener* m_pMessageListenerInner;// ������Ϣ������
	OffsetStore* m_pOffsetStore;// ���ѽ��ȴ洢
	RebalanceImpl* m_pRebalanceImpl;// Rebalanceʵ��
	ConsumerStatManager* m_pConsumerStatManager;
	ConsumeMessageService* m_pConsumeMessageService;// ������Ϣ����

	std::list<ConsumeMessageHook*> m_hookList;//����ÿ����Ϣ��ص�
	friend class PullMessageService;
	friend class RebalancePushImpl;
	friend class DefaultMQPushConsumerImplCallback;
};

#include "PullCallback.h"
class MQException;

class DefaultMQPushConsumerImplCallback : public PullCallback
{
public:
	DefaultMQPushConsumerImplCallback(SubscriptionData& subscriptionData,
		DefaultMQPushConsumerImpl* pDefaultMQPushConsumerImpl,
		PullRequest* pPullRequest);

	void onSuccess(PullResult& pullResult);
	void onException(MQException& e);

private:
	SubscriptionData m_subscriptionData;
	DefaultMQPushConsumerImpl* m_pDefaultMQPushConsumerImpl;
	PullRequest* m_pPullRequest;
	std::chrono::system_clock::time_point m_beginTimestamp;
};

#endif
