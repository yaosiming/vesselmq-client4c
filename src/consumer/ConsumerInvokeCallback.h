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

#if!defined __CONSUMER_INVOKECALLBACK_H__
#define __CONSUMER_INVOKECALLBACK_H__

#include "InvokeCallback.h"

class PullCallback;
class MQClientAPIImpl;

/**
* �첽����Ӧ��ص��ӿ�
*
*/
class ConsumerInvokeCallback : public InvokeCallback
{
public:
	ConsumerInvokeCallback(PullCallback* pPullCallback,MQClientAPIImpl* pMQClientAPIImpl);
	virtual ~ConsumerInvokeCallback();
	virtual void operationComplete(ResponseFuture* pResponseFuture);

private:
	PullCallback* m_pPullCallback;
	MQClientAPIImpl* m_pMQClientAPIImpl;
};

#endif
