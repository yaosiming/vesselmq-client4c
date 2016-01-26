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
#if!defined __PULLRESULT_H__
#define __PULLRESULT_H__

#include <list>

#include "MessageExt.h"
#include "RocketMQClient.h"

enum PullStatus
{
	FOUND,//�ҵ���Ϣ
	NO_NEW_MSG,//û���µ���Ϣ���Ա���ȡ
	NO_MATCHED_MSG,//�������˺�û��ƥ�����Ϣ
	OFFSET_ILLEGAL//Offset���Ϸ������ܹ�����߹�С
};

/**
* ����Ϣ���ؽ��
*
*/
struct ROCKETMQCLIENT_API PullResult
{
	PullResult()
	{

	}

	PullResult(PullStatus pullStatus,
			   long long nextBeginOffset,
			   long long minOffset,
			   long long maxOffset,
			   std::list<MessageExt*>& msgFoundList)
		:pullStatus(pullStatus),
		 nextBeginOffset(nextBeginOffset),
		 minOffset(minOffset),
		 maxOffset(maxOffset),
		 msgFoundList(msgFoundList)
	{

	}
	
	~PullResult()
	{
		std::list<MessageExt*>::iterator it = msgFoundList.begin();

		for (;it!=msgFoundList.end();it++)
		{
			delete *it;
		}
	}

	PullStatus pullStatus;
	long long nextBeginOffset;
	long long minOffset;
	long long maxOffset;
	std::list<MessageExt*> msgFoundList;
};

#endif
