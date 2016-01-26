/**
* Copyright (C) 2013 kangliqiang, kangliq@163.com
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
#if!defined __SUBSCRIPTIONGROUPCONFIG_H__
#define __SUBSCRIPTIONGROUPCONFIG_H__

#include <string>

#include "MixAll.h"

class SubscriptionGroupConfig
{
public:
	SubscriptionGroupConfig(const std::string& groupName)
	{
		this->groupName=groupName;
		consumeEnable = true;
		consumeFromMinEnable = true;
		consumeBroadcastEnable = true;
		retryQueueNums = 1;
		retryMaxTimes = 5;
		brokerId = MixAll::MASTER_ID;
		whichBrokerWhenConsumeSlowly = 1;
	}

	std::string groupName;// ��������
	bool consumeEnable;// ���ѹ����Ƿ���
	bool consumeFromMinEnable;// �Ƿ�����Ӷ�����Сλ�ÿ�ʼ���ѣ�����Ĭ�ϻ�����Ϊfalse
	bool consumeBroadcastEnable;// �Ƿ�����㲥��ʽ����
	int retryQueueNums;// ����ʧ�ܵ���Ϣ�ŵ�һ�����Զ��У�ÿ�����������ü������Զ���
	int retryMaxTimes; // ����������������������Ͷ�ݵ����Ŷ��У�����Ͷ�ݣ�������
	long brokerId;// ���ĸ�Broker��ʼ����
	long whichBrokerWhenConsumeSlowly;// ������Ϣ�ѻ��󣬽�Consumer�����������ض�������һ̨Slave����
};

#endif
