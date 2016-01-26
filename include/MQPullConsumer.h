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
#if!defined __MQPULLCONSUMER_H__
#define __MQPULLCONSUMER_H__

#include <set>
#include <string>

#include "MQConsumer.h"
#include "PullResult.h"
#include "RocketMQClient.h"

class MessageQueueListener;
class MessageQueue;
class PullCallback;

/**
* �����ߣ�������ʽ����
*
*/
class ROCKETMQCLIENT_API MQPullConsumer : public MQConsumer
{
public:
	virtual ~MQPullConsumer(){}
	/**
	* ע��������б仯��listener����
	*
	* @param topic
	* @param listener
	*            һ�������仯���ͻ��˻������ص�listener����
	*/
	virtual void registerMessageQueueListener(const std::string& topic, MessageQueueListener* pListener)=0;

	/**
	* ָ�����У�������ȡ��Ϣ����ʹû����Ϣ��Ҳ���̷���
	*
	* @param mq
	*            ָ������Ҫ��ȡ�Ķ���
	* @param subExpression
	*            ���Ĺ��˱��ʽ�ַ�����broker���ݴ˱��ʽ���й��ˡ�Ŀǰֻ֧�ֻ�����<br>
	*            eg: "tag1 || tag2 || tag3"<br>
	*            ���subExpression����null����*�����ʾȫ������
	* @param offset
	*            ��ָ�������ĸ�λ�ÿ�ʼ��ȡ
	* @param maxNums
	*            һ�������ȡ����
	* @return �μ�PullResult
	* @throws MQClientException
	* @throws InterruptedException
	* @throws MQBrokerException
	* @throws RemotingException
	*/
	virtual PullResult* pull(MessageQueue& mq,
		const std::string& subExpression,
		long long offset,int maxNums)=0;

	virtual void pull(MessageQueue& mq,
		const std::string& subExpression,
		long long offset,
		int maxNums,
		PullCallback* pPullCallback)=0;

	/**
	* ָ�����У�������ȡ��Ϣ�����û����Ϣ����broker����һ��ʱ���ٷ��أ�ʱ������ã�<br>
	* broker�����ڼ䣬�������Ϣ�������̽���Ϣ����
	*
	* @param mq
	*            ָ������Ҫ��ȡ�Ķ���
	* @param subExpression
	*            ���Ĺ��˱��ʽ�ַ�����broker���ݴ˱��ʽ���й��ˡ�Ŀǰֻ֧�ֻ�����<br>
	*            eg: "tag1 || tag2 || tag3"<br>
	*            ���subExpression����null����*�����ʾȫ������
	* @param offset
	*            ��ָ�������ĸ�λ�ÿ�ʼ��ȡ
	* @param maxNums
	*            һ�������ȡ����
	* @return �μ�PullResult
	* @throws InterruptedException
	* @throws MQBrokerException
	* @throws RemotingException
	* @throws MQClientException
	*/
	virtual PullResult* pullBlockIfNotFound(MessageQueue& mq,
											const std::string& subExpression,
											long long offset,
											int maxNums)=0;


	virtual void pullBlockIfNotFound(MessageQueue& mq,
									 const std::string& subExpression,
									 long long offset,
									 int maxNums,
									 PullCallback* pPullCallback)=0;

	/**
	* �������ѽ���<br>
	* ֻ�Ǹ���Consumer�����е����ݣ�����ǹ㲥ģʽ����ʱ���µ����ش洢<br>
	* ����Ǽ�Ⱥģʽ����ʱ���µ�Զ��Broker<br>
	* <p/>
	* P.S. ��Ƶ�����ã������ܿ���
	*
	* @param mq
	* @param offset
	* @throws MQClientException
	*/
	virtual void updateConsumeOffset(MessageQueue& mq, long long offset)=0;

	/**
	* ��ȡ���ѽ��ȣ�����-1��ʾ����
	*
	* @param mq
	* @param fromStore
	* @return
	* @throws MQClientException
	*/
	virtual long long fetchConsumeOffset(MessageQueue& mq, bool fromStore)=0;

	/**
	* ����topic��ȡMessageQueue���Ծ��ⷽʽ�����ڶ����Ա֮�����
	*
	* @param topic
	*            ��ϢTopic
	* @return ���ض��м���
	* @throws MQClientException
	*/
	virtual std::set<MessageQueue*> fetchMessageQueuesInBalance(const std::string& topic)=0;
};

#endif
