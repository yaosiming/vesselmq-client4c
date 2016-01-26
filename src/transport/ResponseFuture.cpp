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

#include "ResponseFuture.h"
#include "KPRUtil.h"
#include "InvokeCallback.h"
#include "Monitor.h"
#include "ScopedLock.h"

ResponseFuture::ResponseFuture(int requestCode,int opaque, int timeoutMillis, InvokeCallback* pInvokeCallback,bool block)
{
	m_requestCode = requestCode;
	m_opaque = opaque;
	m_timeoutMillis = timeoutMillis;
	m_pInvokeCallback = pInvokeCallback;
	m_beginTimestamp = GetCurrentTimeMillis();
	m_pResponseCommand=NULL;
	m_notifyFlag = false;
	m_pMonitor = NULL;
	m_sendRequestOK = false;

	if (block)
	{
		m_pMonitor = new kpr::Monitor();
	}
}

ResponseFuture::~ResponseFuture()
{
	if(m_pMonitor)
	{
		delete m_pMonitor;
	}
}

void  ResponseFuture::executeInvokeCallback()
{
	if (m_pInvokeCallback != NULL)
	{
		m_pInvokeCallback->operationComplete(this);
	}

	DecRef();
}

void  ResponseFuture::release()
{
}

bool  ResponseFuture::isTimeout()
{
	long long diff = GetCurrentTimeMillis() - m_beginTimestamp;
	return diff > m_timeoutMillis;
}

RemotingCommand*  ResponseFuture::waitResponse(int timeoutMillis)
{
	if (m_pMonitor)
	{
		kpr::ScopedLock<kpr::Monitor> lock(*m_pMonitor);
		if (!m_notifyFlag)
		{
			m_pMonitor->Wait(timeoutMillis);
		}
	}
	
	return m_pResponseCommand;
}

void  ResponseFuture::putResponse(RemotingCommand* pResponseCommand)
{
	m_pResponseCommand = pResponseCommand;
	if (m_pMonitor)
	{
		kpr::ScopedLock<kpr::Monitor> lock(*m_pMonitor);
		m_notifyFlag=true;
		m_pMonitor->Notify();
	}
}

long long  ResponseFuture::getBeginTimestamp()
{
	return m_beginTimestamp;
}

bool  ResponseFuture::isSendRequestOK()
{
	return m_sendRequestOK;
}

void  ResponseFuture::setSendRequestOK(bool sendRequestOK)
{
	m_sendRequestOK = sendRequestOK;
}

long long  ResponseFuture::getTimeoutMillis()
{
	return m_timeoutMillis;
}

InvokeCallback*  ResponseFuture::getInvokeCallback()
{
	return m_pInvokeCallback;
}

RemotingCommand*  ResponseFuture::getResponseCommand()
{
	return m_pResponseCommand;
}

void  ResponseFuture::setResponseCommand(RemotingCommand* pResponseCommand)
{
	m_pResponseCommand = pResponseCommand;
}

int  ResponseFuture::getOpaque()
{
	return m_opaque;
}

int ResponseFuture::getRequestCode()
{
	return m_requestCode;
}

void ResponseFuture::setRequestCode( int requestCode )
{
	m_requestCode = requestCode;
}
