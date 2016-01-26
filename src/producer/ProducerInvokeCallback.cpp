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

#include "ProducerInvokeCallback.h"
#include "ResponseFuture.h"
#include "SendResult.h"
#include "MQClientAPIImpl.h"
#include "SendCallback.h"
#include "MQClientException.h"
#include "RemotingCommand.h"

ProducerInvokeCallback::ProducerInvokeCallback(SendCallback* pSendCallBack,
	MQClientAPIImpl*pMQClientAPIImpl,
	const std::string& topic,
	const std::string& brokerName)
	:m_pSendCallBack(pSendCallBack),
	m_pMQClientAPIImpl(pMQClientAPIImpl),
	m_topic(topic),
	m_brokerName(brokerName)
{
}

ProducerInvokeCallback::~ProducerInvokeCallback()
{
}

void ProducerInvokeCallback::operationComplete(ResponseFuture* pResponseFuture)
{
	if (m_pSendCallBack==NULL)
	{
		delete this;
		return;
	}

	RemotingCommand* response = pResponseFuture->getResponseCommand();
	if (response != NULL)
	{
		try
		{
			SendResult* sendResult =
				m_pMQClientAPIImpl->processSendResponse(m_brokerName, m_topic, response);

			m_pSendCallBack->onSuccess(*sendResult);

			delete sendResult;
		}
		catch (MQException& e)
		{
			m_pSendCallBack->onException(e);
		}

		delete response;
	}
	else
	{
		if (!pResponseFuture->isSendRequestOK())
		{
			//"send request failed", responseFuture	.getCause()
			std::string msg = "send request failed";
			MQClientException e(msg,-1,__FILE__,__LINE__);
			m_pSendCallBack->onException(e);
		}
		else if (pResponseFuture->isTimeout())
		{
			//wait response timeout "+ responseFuture.getTimeoutMillis() + "ms", responseFuture.getCause()
			std::string msg = "wait response timeout";
			MQClientException e(msg,-1,__FILE__,__LINE__);
			m_pSendCallBack->onException(e);
		}
		else
		{
			// "unknow reseaon", responseFuture	.getCause()
			std::string msg = "unknow reseaon";
			MQClientException e(msg,-1,__FILE__,__LINE__);
			m_pSendCallBack->onException(e);
		}
	}

	delete this;
}
