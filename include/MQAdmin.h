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

#if!defined __MQADMIN_H__
#define __MQADMIN_H__

#include <string>
#include "MessageExt.h"
#include "RocketMQClient.h"

class MQClientException;
class RemotingException;
class MQBrokerException;
class InterruptedException;
class MessageQueue;
class QueryResult;

/**
* MQ������ӿ�
*
*/
class ROCKETMQCLIENT_API MQAdmin
{
public:
	MQAdmin()
	{
	}

	virtual ~MQAdmin()
	{
	}

	/**
	* ����topic
	*
	* @param key
	*            ������ά��Ա����
	* @param newTopic
	*            Ҫ��������topic
	* @param queueNum
	*            ��topic������
	* @throws MQClientException
	*/
	virtual void createTopic(const std::string& key, const std::string& newTopic, int queueNum)=0;

	/**
	* ����ʱ���ѯ��Ӧ��offset����ȷ������<br>
	* P.S. ��ǰ�ӿ��н϶�IO����������Ƶ������
	*
	* @param mq
	*            ����
	* @param timestamp
	*            ������ʽʱ���
	* @return ָ��ʱ���Ӧ��offset
	* @throws MQClientException
	*/
	virtual long long searchOffset(const MessageQueue& mq, long long timestamp)=0;

	/**
	* ���������ѯ�������Offset PS: ���Offset�޶�Ӧ��Ϣ����1����Ϣ
	*
	* @param mq
	*            ����
	* @return ���е����Offset
	* @throws MQClientException
	*/
	virtual long long maxOffset(const MessageQueue& mq)=0;

	/**
	* ���������ѯ������СOffset PS: ��СOffset�ж�Ӧ��Ϣ
	*
	* @param mq
	*            ����
	* @return ���е���СOffset
	* @throws MQClientException
	*/
	virtual long long minOffset(const MessageQueue& mq)=0;

	/**
	* ���������ѯ���б����������Ϣ��Ӧ�Ĵ洢ʱ��
	*
	* @param mq
	*            ����
	* @return ������Ϣ��Ӧ�Ĵ洢ʱ�䣬��ȷ������
	* @throws MQClientException
	*/
	virtual long long earliestMsgStoreTime(const MessageQueue& mq)=0;

	/**
	* ������ϢID���ӷ�������ȡ��������Ϣ
	*
	* @param msgId
	* @return ������Ϣ
	* @throws InterruptedException
	* @throws MQBrokerException
	* @throws RemotingException
	* @throws MQClientException
	*/
	virtual MessageExt viewMessage(const std::string& msgId)=0;

	/**
	* ������ϢKey��ѯ��Ϣ
	*
	* @param topic
	*            ��Ϣ����
	* @param key
	*            ��Ϣ�ؼ���
	* @param maxNum
	*            ��ѯ�������
	* @param begin
	*            ��ʼʱ���
	* @param end
	*            ����ʱ���
	* @return ��ѯ���
	* @throws MQClientException
	* @throws InterruptedException
	*/
	virtual QueryResult queryMessage(const std::string& topic,
									 const std::string&  key,
									 int maxNum,
									 long long begin,
									 long long end)=0;
};

#endif
