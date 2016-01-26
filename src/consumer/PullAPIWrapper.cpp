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

#include "PullAPIWrapper.h"

#include <stdlib.h>
#include <list>
#include <set>

#include "MQClientFactory.h"
#include "PullCallback.h"
#include "MixAll.h"
#include "PullSysFlag.h"
#include "CommandCustomHeader.h"
#include "MQClientAPIImpl.h"
#include "MQClientException.h"
#include "SubscriptionData.h"
#include "UtilAll.h"
#include "MessageExt.h"
#include "PullResultExt.h"
#include "MessageDecoder.h"
#include "VirtualEnvUtil.h"

PullAPIWrapper::PullAPIWrapper(MQClientFactory* pMQClientFactory, const std::string& consumerGroup)
{
	m_pMQClientFactory = pMQClientFactory;
	m_consumerGroup = consumerGroup;
}

void  PullAPIWrapper::updatePullFromWhichNode(MessageQueue& mq, long brokerId) 
{
	std::map<MessageQueue, AtomicLong>::iterator it = m_pullFromWhichNodeTable.find(mq);
	if (it!=m_pullFromWhichNodeTable.end())
	{
		it->second.Set(brokerId);
	}
	else
	{
		m_pullFromWhichNodeTable[mq]=AtomicLong(brokerId);
	}
}

PullResult* PullAPIWrapper::processPullResult(MessageQueue& mq, 
	PullResult& pullResult,
	SubscriptionData& subscriptionData) 
{
	std::string projectGroupPrefix = m_pMQClientFactory->getMQClientAPIImpl()->getProjectGroupPrefix();
	PullResultExt& pullResultExt = (PullResultExt&) pullResult;

	updatePullFromWhichNode(mq, pullResultExt.suggestWhichBrokerId);

	if (pullResult.pullStatus == FOUND)
	{
		std::list<MessageExt*> msgList =
			MessageDecoder::decodes(pullResultExt.messageBinary, pullResultExt.messageBinaryLen);

		// ��Ϣ�ٴι���
		std::list<MessageExt*> msgListFilterAgain;

		if (!subscriptionData.getTagsSet().empty()) 
		{
			std::list<MessageExt*>::iterator it = msgList.begin();
			for (;it!=msgList.end();)
			{
				MessageExt* msg = *it;
				if (!msg->getTags().empty())
				{
					std::set<std::string>& tags = subscriptionData.getTagsSet();
					if (tags.find(msg->getTags())!=tags.end())
					{
						msgListFilterAgain.push_back(msg);
						it = msgList.erase(it);
					}
					else
					{
						it++;
					}
				}
			}
		}
		else
		{
			msgListFilterAgain.assign(msgList.begin(),msgList.end());
			msgList.clear();
		}

		// ����������л�����ص�projectGroupPrefix
		if (!UtilAll::isBlank(projectGroupPrefix))
		{
			subscriptionData.setTopic(VirtualEnvUtil::clearProjectGroup(subscriptionData.getTopic(),
				projectGroupPrefix));
			mq.setTopic(VirtualEnvUtil::clearProjectGroup(mq.getTopic(), projectGroupPrefix));

			std::list<MessageExt*>::iterator it = msgListFilterAgain.begin();
			for (;it!=msgListFilterAgain.end();it++)
			{
				MessageExt* msg = *it;
				msg->setTopic(VirtualEnvUtil::clearProjectGroup(msg->getTopic(), projectGroupPrefix));
				// ��Ϣ�з�����е������СOffset������Ӧ������֪��Ϣ�ѻ��̶�

				char tmp[32];
				sprintf(tmp,"%lld",pullResult.minOffset);

				msg->putProperty(Message::PROPERTY_MIN_OFFSET, tmp);

				sprintf(tmp,"%lld",pullResult.maxOffset);
				msg->putProperty(Message::PROPERTY_MAX_OFFSET, tmp);
			}
		}
		else 
		{
			// ��Ϣ�з�����е������СOffset������Ӧ������֪��Ϣ�ѻ��̶�
			std::list<MessageExt*>::iterator it = msgListFilterAgain.begin();
			for (;it!=msgListFilterAgain.end();it++)
			{
				MessageExt* msg = *it;

				char tmp[32];
				sprintf(tmp,"%lld",pullResult.minOffset);

				msg->putProperty(Message::PROPERTY_MIN_OFFSET, tmp);

				sprintf(tmp,"%lld",pullResult.maxOffset);
				msg->putProperty(Message::PROPERTY_MAX_OFFSET, tmp);
			}
		}

		std::list<MessageExt*>::iterator it = msgListFilterAgain.begin();
		for (;it!=msgListFilterAgain.end();it++)
		{
			pullResultExt.msgFoundList.push_back(*it);
		}

		//�����Դ
		it = msgList.begin();
		for (;it!=msgList.end();it++)
		{
			delete *it;
		}

		delete[] pullResultExt.messageBinary;
		pullResultExt.messageBinary = NULL;
		pullResultExt.messageBinaryLen = 0;
	}

	return &pullResult;
}

long  PullAPIWrapper::recalculatePullFromWhichNode(MessageQueue& mq)
{
	std::map<MessageQueue, AtomicLong>::iterator it = m_pullFromWhichNodeTable.find(mq);
	if (it!=m_pullFromWhichNodeTable.end())
	{
		return it->second.Get();
	}

	return MixAll::MASTER_ID;
}

PullResult* PullAPIWrapper::pullKernelImpl(MessageQueue& mq,
											const std::string& subExpression,
											long long subVersion,
											long long offset,
											int maxNums,
											int sysFlag,
											long long commitOffset,
											long long brokerSuspendMaxTimeMillis,
											int timeoutMillis,
											CommunicationMode communicationMode,
											PullCallback* pPullCallback) 
{
	FindBrokerResult findBrokerResult =
		m_pMQClientFactory->findBrokerAddressInSubscribe(mq.getBrokerName(),
		recalculatePullFromWhichNode(mq), false);
	if (findBrokerResult.brokerAddr.empty()) 
	{
		// TODO �˴����ܶ�Name Serverѹ��������Ҫ����
		m_pMQClientFactory->updateTopicRouteInfoFromNameServer(mq.getTopic());
		findBrokerResult = m_pMQClientFactory->findBrokerAddressInSubscribe(mq.getBrokerName(),
			recalculatePullFromWhichNode(mq), false);
	}

	if (!findBrokerResult.brokerAddr.empty())
	{
		int sysFlagInner = sysFlag;

		// Slave������ʵʱ�ύ���ѽ��ȣ����Զ�ʱ�ύ
		if (findBrokerResult.slave) 
		{
			sysFlagInner = PullSysFlag::clearCommitOffsetFlag(sysFlagInner);
		}

		PullMessageRequestHeader* requestHeader = new PullMessageRequestHeader();
		requestHeader->consumerGroup = m_consumerGroup;
		requestHeader->topic = mq.getTopic();
		requestHeader->queueId = mq.getQueueId();
		requestHeader->queueOffset = offset;
		requestHeader->maxMsgNums = maxNums;
		requestHeader->sysFlag = sysFlagInner;
		requestHeader->commitOffset = commitOffset;
		requestHeader->suspendTimeoutMillis = brokerSuspendMaxTimeMillis;
		requestHeader->subscription = subExpression;
		requestHeader->subVersion = subVersion;

		PullResult* pullResult = m_pMQClientFactory->getMQClientAPIImpl()->pullMessage(//
			findBrokerResult.brokerAddr,//
			requestHeader,//
			timeoutMillis,//
			communicationMode,//
			pPullCallback);



		return pullResult;
	}

	THROW_MQEXCEPTION(MQClientException,"The broker[" + mq.getBrokerName() + "] not exist",-1);
}
