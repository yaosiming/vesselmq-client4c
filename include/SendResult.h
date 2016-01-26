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
#if!defined __SENDRESULT_H__
#define __SENDRESULT_H__

#include "MessageQueue.h"
#include "RocketMQClient.h"

/**
* ��4��״̬����ʾ��Ϣ�Ѿ��ɹ�����Master
*
*/
enum SendStatus
{
	// ��Ϣ���ͳɹ�
	SEND_OK,
	// ��Ϣ���ͳɹ������Ƿ�����ˢ�̳�ʱ����Ϣ�Ѿ�������������У�ֻ�д�ʱ������崻�����Ϣ�Żᶪʧ
	FLUSH_DISK_TIMEOUT,
	// ��Ϣ���ͳɹ������Ƿ�����ͬ����Slaveʱ��ʱ����Ϣ�Ѿ�������������У�ֻ�д�ʱ������崻�����Ϣ�Żᶪʧ
	FLUSH_SLAVE_TIMEOUT,
	// ��Ϣ���ͳɹ������Ǵ�ʱslave�����ã���Ϣ�Ѿ�������������У�ֻ�д�ʱ������崻�����Ϣ�Żᶪʧ
	SLAVE_NOT_AVAILABLE
};

/**
* ������Ϣ���
*
*/
class ROCKETMQCLIENT_API SendResult
{
public:
	SendResult();
	SendResult(const SendStatus& sendStatus,
		const std::string&  msgId,
		MessageQueue& messageQueue,
		long long queueOffset,
		std::string&  projectGroupPrefix);

	const std::string&  getMsgId();
	void setMsgId(const std::string&  msgId);
	SendStatus getSendStatus();
	void setSendStatus(const SendStatus& sendStatus);
	MessageQueue& getMessageQueue();
	void setMessageQueue(MessageQueue& messageQueue);
	long long getQueueOffset();
	void setQueueOffset(long long queueOffset);

private:
	SendStatus m_sendStatus;
	std::string m_msgId;
	MessageQueue m_messageQueue;
	long long m_queueOffset;
};

enum LocalTransactionState
{
	COMMIT_MESSAGE,// �ύ����
	ROLLBACK_MESSAGE,// �ع�����
	UNKNOW,
};

/**
* ����������Ϣ���ؽ��
*
*/
class ROCKETMQCLIENT_API TransactionSendResult : public SendResult
{
public:
	TransactionSendResult();
	LocalTransactionState getLocalTransactionState();
	void setLocalTransactionState(LocalTransactionState localTransactionState);

private:
	LocalTransactionState m_localTransactionState;
};

#endif
