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

#if!defined __MQCLIENTFACTORY_H__
#define __MQCLIENTFACTORY_H__

#include "SocketUtil.h"

#include <set>
#include <string>
#include <list>
#include "TopicRouteData.h"
#include "FindBrokerResult.h"
#include "ClientConfig.h"
#include "Mutex.h"
#include "ServiceState.h"
#include "TimerTaskManager.h"

class ClientConfig;
class MessageQueue;
class MQAdminExtInner;
class MQClientAPIImpl;
class MQAdminImpl;
class PullMessageService;
class HeartbeatData;
class RemoteClientConfig;
class ClientRemotingProcessor;
class RebalanceService;
class DefaultMQProducer;
class TopicPublishInfo;
class 	MQProducerInner;
class	MQConsumerInner;
class DefaultMQProducerImpl;

/**
* �ͻ���Factory�࣬��������Producer��Consumer
*
*/

class MQClientFactory
{
public:
	MQClientFactory(ClientConfig& clientConfig, int factoryIndex, const std::string& clientId);
	~MQClientFactory();

	void start();
	void shutdown();
	void sendHeartbeatToAllBrokerWithLock();
	void updateTopicRouteInfoFromNameServer();
	bool updateTopicRouteInfoFromNameServer(const std::string& topic);

	/**
	* ����Name Server�ӿڣ�����Topic��ȡ·����Ϣ
	*/
	bool updateTopicRouteInfoFromNameServer(const std::string& topic, bool isDefault,
											DefaultMQProducer* pDefaultMQProducer);

	static TopicPublishInfo* topicRouteData2TopicPublishInfo(const std::string& topic,
			TopicRouteData& route);

	static std::set<MessageQueue>* topicRouteData2TopicSubscribeInfo(const std::string& topic,
			TopicRouteData& route);

	bool registerConsumer(const std::string& group, MQConsumerInner* pConsumer);
	void unregisterConsumer(const std::string& group);

	bool registerProducer(const std::string& group, DefaultMQProducerImpl* pProducer);
	void unregisterProducer(const std::string& group);

	bool registerAdminExt(const std::string& group, MQAdminExtInner* pAdmin);
	void unregisterAdminExt(const std::string& group);

	void rebalanceImmediately();
	void doRebalance();

	MQProducerInner* selectProducer(const std::string& group);
	MQConsumerInner* selectConsumer(const std::string& group);

	/**
	* ������Ľӿڲ�ѯBroker��ַ��Master����
	*
	* @param brokerName
	* @return
	*/
	FindBrokerResult findBrokerAddressInAdmin(const std::string& brokerName);

	/**
	* ������Ϣ�����У�Ѱ��Broker��ַ��һ������Master
	*/
	std::string findBrokerAddressInPublish(const std::string& brokerName);

	/**
	* ������Ϣ�����У�Ѱ��Broker��ַ��ȡMaster����Slave�ɲ�������
	*/
	FindBrokerResult findBrokerAddressInSubscribe(//
		const std::string& brokerName,//
		long brokerId,//
		bool onlyThisBroker );

	std::list<std::string> findConsumerIdList(const std::string& topic, const std::string& group);
	std::string findBrokerAddrByTopic(const std::string& topic);
	TopicRouteData getAnExistTopicRouteData(const std::string& topic);
	MQClientAPIImpl* getMQClientAPIImpl();
	MQAdminImpl* getMQAdminImpl();
	std::string getClientId();
	long long getBootTimestamp();
	PullMessageService* getPullMessageService();
	DefaultMQProducer* getDefaultMQProducer();

private:
	void sendHeartbeatToAllBroker();
	HeartbeatData* prepareHeartbeatData();

	void makesureInstanceNameIsOnly(const std::string& instanceName);
	void startScheduledTask();

	/**
	* �������ߵ�broker
	*/
	void cleanOfflineBroker();
	bool isBrokerAddrExistInTopicRouteTable(const std::string& addr);
	void recordSnapshotPeriodically();
	void logStatsPeriodically();
	void persistAllConsumerOffset();
	bool topicRouteDataIsChange(TopicRouteData& olddata, TopicRouteData& nowdata);
	bool isNeedUpdateTopicRouteInfo(const std::string& topic);
	void unregisterClientWithLock(const std::string& producerGroup, const std::string& consumerGroup);
	void unregisterClient(const std::string& producerGroup, const std::string& consumerGroup);
	
	typedef void (MQClientFactory::*pScheduledFunc)();

	class ScheduledTask : public TimerTask
	{
	public:
		ScheduledTask(MQClientFactory* pMQClientFactory, pScheduledFunc pScheduled)
			:m_pMQClientFactory(pMQClientFactory),m_pScheduled(pScheduled)
		{

		}

		virtual void DoTask()
		{
			(m_pMQClientFactory->*m_pScheduled)();
		}

	private:
		MQClientFactory* m_pMQClientFactory;
		pScheduledFunc m_pScheduled;
	};

	//��ʱ����
	void fetchNameServerAddr();
	void updateTopicRouteInfoFromNameServerTask();
	void cleanBroker();
	void persistAllConsumerOffsetTask();
	void recordSnapshotPeriodicallyTask();
	void logStatsPeriodicallyTask();

private:
	static long LockTimeoutMillis;
	ClientConfig m_clientConfig;
	int m_factoryIndex;
	std::string m_clientId;
	long long m_bootTimestamp;

	// Producer����
	//group --> MQProducerInner
	std::map<std::string, MQProducerInner*> m_producerTable;
	kpr::Mutex m_producerTableLock;

	// Consumer����
	//group --> MQConsumerInner
	std::map<std::string, MQConsumerInner*> m_consumerTable;
	kpr::Mutex m_consumerTableLock;

	// AdminExt����
	// group --> MQAdminExtInner
	std::map<std::string, MQAdminExtInner*> m_adminExtTable ;
	kpr::Mutex m_adminExtTableLock;

	// Զ�̿ͻ�������
	RemoteClientConfig* m_pRemoteClientConfig;

	// RPC���õķ�װ��
	MQClientAPIImpl* m_pMQClientAPIImpl;
	MQAdminImpl* m_pMQAdminImpl;

	// �洢��Name Server�õ���Topic·����Ϣ
	/// Topic---> TopicRouteData
	std::map<std::string, TopicRouteData> m_topicRouteTable;
	kpr::Mutex m_topicRouteTableLock;

	kpr::Mutex m_mutex;
	// ����Name Server��ȡTopic·����Ϣʱ������
	kpr::Mutex m_lockNamesrv;

	// ������ע����������
	kpr::Mutex m_lockHeartbeat;

	// �洢Broker Name ��Broker Address�Ķ�Ӧ��ϵ
	//
	//-----brokerName
	//     ------brokerid  addr
	//     ------brokerid  addr
	std::map<std::string, std::map<int, std::string> > m_brokerAddrTable;
	kpr::Mutex m_brokerAddrTableLock;

	// ��ʱ�߳�
	kpr::TimerTaskManager m_timerTaskManager;
	ScheduledTask* m_pFetchNameServerAddr;
	ScheduledTask* m_pUpdateTopicRouteInfoFromNameServerTask;
	ScheduledTask* m_pCleanBroker;
	ScheduledTask* m_pPersistAllConsumerOffsetTask;
	ScheduledTask* m_pRecordSnapshotPeriodicallyTask;
	ScheduledTask* m_pLogStatsPeriodicallyTask;

	int m_scheduledTaskIds[6];

	ClientRemotingProcessor* m_pClientRemotingProcessor;// �����������������������
	PullMessageService* m_pPullMessageService;// ����Ϣ����
	RebalanceService* m_pRebalanceService;// Rebalance����
	DefaultMQProducer* m_pDefaultMQProducer;// ����Producer����
	ServiceState m_serviceState;

	// ����һ��UDP�˿ڣ�������ֹͬһ��Factory������ݣ��п��ֲܷ��ڶ��JVM�У�����C++�Ƿ���Ҫ
	SOCKET m_datagramSocket;
};

#endif
