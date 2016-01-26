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
#if!defined __PULLCALLBACK_H__
#define __PULLCALLBACK_H__

#include "PullResult.h"
#include "RocketMQClient.h"

class MQException;

/**
 * �첽����Ϣ�ص��ӿ�
 *
 */
class ROCKETMQCLIENT_API PullCallback
{
public:
	virtual ~PullCallback() {}
	virtual void onSuccess(PullResult& pullResult)=0;
	virtual void onException(MQException& e)=0;
};

#endif
