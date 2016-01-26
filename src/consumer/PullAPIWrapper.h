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

#if!defined __PULLAPIWRAPPER_H__
#define __PULLAPIWRAPPER_H__

#include <string>
#include <map>

#include "AtomicValue.h"
#include "PullResult.h"
#include "MessageQueue.h"
#include "CommunicationMode.h"

class MQClientFactory;
class PullCallback;
class SubscriptionData;

/**
* ��Pull�ӿڽ��н�һ���ķ�װ
* 
*/
class PullAPIWrapper 
{
public:
	PullAPIWrapper(MQClientFactory* pMQClientFactory, const std::string& consumerGroup);
	void updatePullFromWhichNode(MessageQueue& mq, long brokerId);

	/**
	* ����ȡ������д�����Ҫ����Ϣ�����л�
	* 
	* @param mq
	* @param pullResult
	* @param subscriptionData
	* @param projectGroupPrefix
	*            ���⻷��projectGroupPrefix�������ڿ�����Ϊ null
	* @return
	*/
	PullResult* processPullResult(MessageQueue& mq, 
		PullResult& pullResult,
		SubscriptionData& subscriptionData);

	/**
	* ÿ�����ж�Ӧ������Ӧ�ı�����������ĸ���������
	*/
	long recalculatePullFromWhichNode(MessageQueue& mq);

	PullResult* pullKernelImpl(MessageQueue& mq,
								const std::string& subExpression,
								long long subVersion,
								long long offset,
								int maxNums,
								int sysFlag,
								long long commitOffset,
								long long brokerSuspendMaxTimeMillis,
								int timeoutMillis,
								CommunicationMode communicationMode,
								PullCallback* pPullCallback);

private:
	std::map<MessageQueue, AtomicLong> m_pullFromWhichNodeTable;
	MQClientFactory* m_pMQClientFactory;
	std::string m_consumerGroup;
};

#endif
