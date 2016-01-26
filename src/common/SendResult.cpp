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
#include "SendResult.h"
#include "UtilAll.h"
#include "VirtualEnvUtil.h"

SendResult::SendResult()
	:m_sendStatus(SEND_OK)
{
}

SendResult::SendResult(const SendStatus& sendStatus,
	const std::string&  msgId,
	MessageQueue& messageQueue,
	long long queueOffset,
	std::string&  projectGroupPrefix)
	:m_sendStatus(sendStatus),
	m_msgId(msgId),
	m_messageQueue(messageQueue),
	m_queueOffset(queueOffset)
{

	// ����������л�����ص�projectGroupPrefix
	if (!UtilAll::isBlank(projectGroupPrefix))
	{
		m_messageQueue.setTopic(VirtualEnvUtil::clearProjectGroup(m_messageQueue.getTopic(),
			projectGroupPrefix));
	}
}

const std::string&  SendResult::getMsgId()
{
	return m_msgId;
}

void SendResult::setMsgId(const std::string&  msgId)
{
	m_msgId = m_msgId;
}

SendStatus SendResult::getSendStatus()
{
	return m_sendStatus;
}

void SendResult::setSendStatus(const SendStatus& sendStatus)
{
	m_sendStatus = sendStatus;
}

MessageQueue& SendResult::getMessageQueue()
{
	return m_messageQueue;
}

void SendResult::setMessageQueue(MessageQueue& messageQueue)
{
	m_messageQueue = messageQueue;
}

long long SendResult::getQueueOffset()
{
	return m_queueOffset;
}

void SendResult::setQueueOffset(long long queueOffset)
{
	m_queueOffset = m_queueOffset;
}


/**
* ����������Ϣ���ؽ��
*
*/
TransactionSendResult::TransactionSendResult()
{
}

LocalTransactionState TransactionSendResult::getLocalTransactionState()
{
	return m_localTransactionState;
}

void TransactionSendResult::setLocalTransactionState(LocalTransactionState localTransactionState)
{
	m_localTransactionState = localTransactionState;
}
