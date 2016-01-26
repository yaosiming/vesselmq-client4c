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
#if!defined __CONSUMEMESSAGESERVICE_H__
#define __CONSUMEMESSAGESERVICE_H__

#include <list>

class MessageExt;
class ProcessQueue;
class MessageQueue;

/**
* ������Ϣ���񣬹����ӿ�
*
*/
class ConsumeMessageService
{
public:
	virtual ~ConsumeMessageService() {}
	virtual void start()=0;
	virtual void shutdown()=0;
	virtual void updateCorePoolSize(int corePoolSize)=0;
	virtual void submitConsumeRequest(std::list<MessageExt*>& msgs,
									  ProcessQueue* pProcessQueue,
									  MessageQueue& messageQueue,
									  bool dispathToConsume)=0;
};

#endif
