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
#if!defined __REMOTEBROKEROFFSETSTORE_H__
#define __REMOTEBROKEROFFSETSTORE_H__

#include "OffsetStore.h"
#include <map>
#include <string>
#include <set>
#include "MessageQueue.h"
#include "AtomicValue.h"
#include "Mutex.h"

class MQClientFactory;

/**
* ���ѽ��ȴ洢��Զ��Broker���ȽϿɿ�
* 
*/
class RemoteBrokerOffsetStore : public OffsetStore
{
public:
	RemoteBrokerOffsetStore(MQClientFactory* pMQClientFactory, const std::string& groupName) ;
	
	void load();
	void updateOffset(MessageQueue& mq, long long offset, bool increaseOnly);
	long long readOffset(MessageQueue& mq, ReadOffsetType type);
	void persistAll(std::set<MessageQueue>& mqs);
	void persist(MessageQueue& mq);

private:
	/**
	* ����Consumer Offset����Master�����ڼ䣬���ܻ���µ�Slave��������Ҫ�Ż���������Slave���Ż��� TODO
	*/
	void updateConsumeOffsetToBroker(const MessageQueue& mq, long long offset);
	long long fetchConsumeOffsetFromBroker(MessageQueue& mq);
	void removeOffset(MessageQueue& mq) ;

private:
	MQClientFactory* m_pMQClientFactory;
	std::string m_groupName;
	AtomicLong m_storeTimesTotal;
	std::map<MessageQueue, AtomicLong*> m_offsetTable;
	kpr::Mutex m_tableMutex;
};

#endif
