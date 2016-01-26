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

#if!defined __RESPONSEFUTURE_H__
#define __RESPONSEFUTURE_H__

#include "AtomicValue.h"
#include "RefCount.h"

class InvokeCallback;
class RemotingCommand;

namespace kpr
{
	class Monitor;
}

/**
* �첽����Ӧ���װ
*
*/
class ResponseFuture : public kpr::RefCount
{
public:
	ResponseFuture(int requestCode,int opaque, int timeoutMillis, InvokeCallback* pInvokeCallback,bool block);
	~ResponseFuture();
	void executeInvokeCallback();
	void release();
	bool isTimeout();
	RemotingCommand* waitResponse(int timeoutMillis);
	void putResponse(RemotingCommand* pResponseCommand);
	long long getBeginTimestamp();
	bool isSendRequestOK();
	void setSendRequestOK(bool sendRequestOK);
	int getRequestCode();
	void setRequestCode(int requestCode);
	long long getTimeoutMillis();
	InvokeCallback* getInvokeCallback();
	RemotingCommand* getResponseCommand();
	void setResponseCommand(RemotingCommand* pResponseCommand);
	int getOpaque();

private:
	RemotingCommand* m_pResponseCommand;
	volatile bool m_sendRequestOK;
	int m_requestCode;
	int m_opaque;
	long long m_timeoutMillis;
	InvokeCallback* m_pInvokeCallback;
	long long m_beginTimestamp;
	kpr::Monitor* m_pMonitor;
	bool m_notifyFlag;
	AtomicInteger m_exec;
	//TODO ȷ�ϸ�java���һ����
};

#endif
