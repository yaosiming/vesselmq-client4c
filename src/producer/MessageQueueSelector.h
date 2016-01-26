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

#if!defined __MESSAGEQUEUESELECTOR_H__
#define __MESSAGEQUEUESELECTOR_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <set>
#include <string>
#include <vector>

#include "MessageQueue.h"
#include "UtilAll.h"

class Message;

/**
* ����ѡ����
*
*/
class MessageQueueSelector
{
public:
	virtual ~MessageQueueSelector() {}
	virtual MessageQueue* select(std::vector<MessageQueue*>& mqs, const Message& msg, void* arg)=0;
};

/**
* ������Ϣ�����ѡ�����
*
*/
class SelectMessageQueueByRandoom :public MessageQueueSelector
{
public:
	MessageQueue* select(std::vector<MessageQueue*>& mqs, const Message& msg, void* arg)
	{
		srand( (unsigned)time( NULL ));
		int Value = rand();
		value = value % mqs.size();
		return mqs[value];
	}
};

/**
* ʹ�ù�ϣ�㷨��ѡ����У�˳����Ϣͨ����������<br>
*
*/
class SelectMessageQueueByHash : public MessageQueueSelector
{
public:
	MessageQueue* select(std::vector<MessageQueue*>& mqs, const Message& msg, void* arg,int len)
	{
		int value = UtilAll.hashCode(arg,len);
		if (value < 0)
		{
			value = abs(value);
		}

		value = value % mqs.size();
		return mqs.at(value);
	}
};


/**
* ���ݻ�����ѡ�����ĸ����У�֧�����߼�����ʹ��
*
*/
class SelectMessageQueueByMachineRoom : public MessageQueueSelector
{
public:
	MessageQueue* select(std::vector<MessageQueue*>& mqs, const Message& msg, void* arg)
	{
		// TODO Auto-generated method stub
		return null;
	}

	std::set<std::string> getConsumeridcs()
	{
		return m_consumeridcs;
	}

	void setConsumeridcs(const std::set<std::string>& consumeridcs)
	{
		m_consumeridcs = consumeridcs;
	}

private:
	std::set<std::string> m_consumeridcs;
};

#endif
