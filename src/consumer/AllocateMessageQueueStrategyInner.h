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
#if!defined __ALLOCATEMESSAGEQUEUESTRATEGYINNER_H__
#define __ALLOCATEMESSAGEQUEUESTRATEGYINNER_H__

#include <algorithm>

#include "AllocateMessageQueueStrategy.h"
#include "MQClientException.h"

/**
* Consumer�����Զ��������,ƽ����������㷨
*
*/
class AllocateMessageQueueAveragely : public AllocateMessageQueueStrategy
{
	/**
	* ����ǰ��ConsumerId�������
	*
	* @param currentCID
	*            ��ǰConsumerId
	* @param mqAll
	*            ��ǰTopic�����ж��м��ϣ����ظ����ݣ�������
	* @param cidAll
	*            ��ǰ�����������Consumer���ϣ����ظ����ݣ�������
	* @return �����������ظ�����
	*/
public:
	virtual ~AllocateMessageQueueAveragely() {}
	virtual std::vector<MessageQueue>* allocate(const std::string& currentCID,
		std::vector<MessageQueue>& mqAll,
		std::list<std::string>& cidAll)
	{
		if (currentCID.empty())
		{
			THROW_MQEXCEPTION(MQClientException,"currentCID is empty",-1);
		}

		if (mqAll.empty())
		{
			THROW_MQEXCEPTION(MQClientException,"mqAll is empty",-1);
		}

		if (cidAll.empty())
		{
			THROW_MQEXCEPTION(MQClientException,"cidAll is empty",-1);
		}

		int index = -1;
		int cidAllSize = cidAll.size();

		std::list<std::string>::iterator it = cidAll.begin();
		for(int i=0; it != cidAll.end();it++,i++)
		{
			if (*it == currentCID)
			{
				index = i;
				break;
			}
		}

		 // �����ڴ�ConsumerId ,ֱ�ӷ���
		if (index == -1)
		{
			return NULL;
		}

		int mqAllSize = mqAll.size();
		int mod = mqAllSize % cidAllSize;
		int averageSize =
			mqAllSize <= cidAllSize ? 1 : (mod > 0 && index < mod ? mqAllSize / cidAllSize
			+ 1 : mqAllSize / cidAllSize);
		int startIndex = (mod > 0 && index < mod) ? index * averageSize : index * averageSize + mod;

		std::vector<MessageQueue>* result = new std::vector<MessageQueue>();
		int range = std::min<int>(averageSize, mqAllSize - startIndex);
		
		for (int i = 0; i < range; i++)
		{
			result->push_back(mqAll.at((startIndex + i) % mqAllSize));
		}

		return result;
	}
};

/**
* Consumer�����Զ��������,����������������У�����Ӧ��ʹ��Spring����ʼ��
*
*/
class AllocateMessageQueueByConfig : public AllocateMessageQueueStrategy
{
	/**
	* ����ǰ��ConsumerId�������
	*
	* @param currentCID
	*            ��ǰConsumerId
	* @param mqAll
	*            ��ǰTopic�����ж��м��ϣ����ظ����ݣ�������
	* @param cidAll
	*            ��ǰ�����������Consumer���ϣ����ظ����ݣ�������
	* @return �����������ظ�����
	*/
public:
	virtual ~AllocateMessageQueueByConfig() {}
	virtual std::vector<MessageQueue>* allocate(const std::string& currentCID,
		std::vector<MessageQueue>& mqAll,
		std::list<std::string>& cidAll)
	{
		return NULL;
	}
};

/**
* Consumer�����Զ��������,���ջ�����������У�����֧�����߼�����
*
*/
class AllocateMessageQueueByMachineRoom : public AllocateMessageQueueStrategy
{
	/**
	* ����ǰ��ConsumerId�������
	*
	* @param currentCID
	*            ��ǰConsumerId
	* @param mqAll
	*            ��ǰTopic�����ж��м��ϣ����ظ����ݣ�������
	* @param cidAll
	*            ��ǰ�����������Consumer���ϣ����ظ����ݣ�������
	* @return �����������ظ�����
	*/
public:
	virtual ~AllocateMessageQueueByMachineRoom() {}
	virtual std::vector<MessageQueue>* allocate(const std::string& currentCID,
		std::vector<MessageQueue>& mqAll,
		std::list<std::string>& cidAll)
	{
		return NULL;
	}
};

#endif
