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

#if!defined __CLIENTREMOTINGPROCESSOR_H__
#define __CLIENTREMOTINGPROCESSOR_H__

#include "TcpRequestProcessor.h"

class MQClientFactory;
class RemotingCommand;

/**
* Client����Broker�Ļص���������������ص���������������������ص�
*
*/
class ClientRemotingProcessor : public TcpRequestProcessor
{
public:
	ClientRemotingProcessor(MQClientFactory* pMQClientFactory);

	RemotingCommand* processRequest(RemotingCommand* pRequest);
	RemotingCommand* checkTransactionState(RemotingCommand* pRequest);
	RemotingCommand* notifyConsumerIdsChanged(RemotingCommand* pRequest);

private:
	MQClientFactory* m_pMQClientFactory;
};

#endif
