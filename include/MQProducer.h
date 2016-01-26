/**
* Copyright (C) 2013 kangliqiang ,kangliq@163.com
*
* Licensed under the Apache License, Version 2.0 (the "License")=0;
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

#if!defined __MQPRODUCER_H__
#define __MQPRODUCER_H__

#include <vector>
#include <string>
#include "MQAdmin.h"
#include "SendResult.h"
#include "RocketMQClient.h"

class MessageQueue;
class SendCallback;
class LocalTransactionExecuter;
class MessageQueueSelector;

/**
* ��Ϣ������
*
*/
class ROCKETMQCLIENT_API MQProducer : public MQAdmin
{
public:
	MQProducer()
	{

	}

	virtual ~MQProducer()
	{

	}

	/**
	* ��������
	*
	* @throw( MQClientException
	*/
	virtual void start()=0;

	/**
	* �رշ���һ���رգ��˶��󽫲�����
	*/
	virtual void shutdown()=0;

	/**
	* ����topic��ȡ��Ӧ��MessageQueue�������˳����Ϣ������˳����Ϣ���÷���
	*
	* @param topic
	*            ��ϢTopic
	* @return ���ض��м���
	* @throw( MQClientException
	*/
	virtual std::vector<MessageQueue>* fetchPublishMessageQueues(const std::string& topic)=0;

	/**
	* ������Ϣ��ͬ������
	*
	* @param msg
	*            ��Ϣ
	* @return ���ͽ��
	* @throw( InterruptedException
	* @throw( MQBrokerException
	* @throw( RemotingException
	* @throw( MQClientException
	*/
	virtual SendResult send(Message& msg)=0;

	/**
	* ������Ϣ���첽����
	*
	* @param msg
	*            ��Ϣ
	* @param sendCallback
	*            ���ͽ��ͨ���˽ӿڻص�
	* @throw( MQClientException
	* @throw( RemotingException
	* @throw( InterruptedException
	*/
	virtual void send(Message& msg, SendCallback* sendCallback)=0;

	/**
	* ������Ϣ��Oneway��ʽ����������Ӧ���޷���֤��Ϣ�Ƿ�ɹ����������
	*
	* @param msg
	*            ��Ϣ
	* @throw( MQClientException
	* @throw( RemotingException
	* @throw( InterruptedException
	*/
	virtual void sendOneway(Message& msg)=0;

	/**
	* ��ָ�����з�����Ϣ��ͬ������
	*
	* @param msg
	*            ��Ϣ
	* @param mq
	*            ����
	* @return ���ͽ��
	* @throw( InterruptedException
	* @throw( MQBrokerException
	* @throw( RemotingException
	* @throw( MQClientException
	*/
	virtual SendResult send(Message& msg, MessageQueue& mq)=0;

	/**
	* ��ָ�����з�����Ϣ���첽����
	*
	* @param msg
	*            ��Ϣ
	* @param mq
	*            ����
	* @param sendCallback
	*            ���ͽ��ͨ���˽ӿڻص�
	* @throw( InterruptedException
	* @throw( RemotingException
	* @throw( MQClientException
	*/
	virtual void send(Message& msg, MessageQueue& mq, SendCallback* sendCallback)=0;
	
	/**
	* ��ָ�����з�����Ϣ��Oneway��ʽ����������Ӧ���޷���֤��Ϣ�Ƿ�ɹ����������
	*
	* @param msg
	*            ��Ϣ
	* @param mq
	*            ����
	* @throw( MQClientException
	* @throw( RemotingException
	* @throw( InterruptedException
	*/
	virtual void sendOneway(Message& msg, MessageQueue& mq)=0;

	/**
	* ������Ϣ�������Զ���ѡ����У����е��������ܻ�����Broker����ͣ�仯<br>
	* ���Ҫ��֤��Ϣ�ϸ�����������ά��Ա����Topicʱ����Ҫ�ر�˵��<br>
	* ͬ������
	*
	* @param msg
	*            ��Ϣ
	* @param selector
	*            ����ѡ����������ʱ��ص�
	* @param arg
	*            �ص�����ѡ����ʱ���˲����ᴫ�����ѡ�񷽷�
	* @return ���ͽ��
	* @throw( InterruptedException
	* @throw( MQBrokerException
	* @throw( RemotingException
	* @throw( MQClientException
	*/
	virtual SendResult send(Message& msg, MessageQueueSelector* selector, void* arg)=0;

	/**
	* ������Ϣ�������Զ���ѡ����У����е��������ܻ�����Broker����ͣ�仯<br>
	* ���Ҫ��֤��Ϣ�ϸ�����������ά��Ա����Topicʱ����Ҫ�ر�˵��<br>
	* �첽����
	*
	* @param msg
	*            ��Ϣ
	* @param selector
	*            ����ѡ����������ʱ��ص�
	* @param arg
	*            �ص�����ѡ����ʱ���˲����ᴫ�����ѡ�񷽷�
	* @param sendCallback
	*            ���ͽ��ͨ���˽ӿڻص�
	* @throw( MQClientException
	* @throw( RemotingException
	* @throw( InterruptedException
	*/
	virtual void send(Message& msg, MessageQueueSelector* selector, void* arg, SendCallback* sendCallback)=0;

	/**
	* ������Ϣ�������Զ���ѡ����У����е��������ܻ�����Broker����ͣ�仯<br>
	* ���Ҫ��֤��Ϣ�ϸ�����������ά��Ա����Topicʱ����Ҫ�ر�˵��<br>
	* Oneway��ʽ����������Ӧ���޷���֤��Ϣ�Ƿ�ɹ����������
	*
	* @param msg
	*            ��Ϣ
	* @param selector
	*            ����ѡ����������ʱ��ص�
	* @param arg
	*            �ص�����ѡ����ʱ���˲����ᴫ�����ѡ�񷽷�
	* @throw( MQClientException
	* @throw( RemotingException
	* @throw( InterruptedException
	*/
	virtual void sendOneway(Message& msg, MessageQueueSelector* selector, void* arg)=0;

	virtual TransactionSendResult sendMessageInTransaction(Message& msg,
															LocalTransactionExecuter* tranExecuter,
															void* arg)=0;
};

#endif
