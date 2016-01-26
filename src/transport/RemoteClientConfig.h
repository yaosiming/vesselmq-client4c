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

#if!defined __REMOTECLIENTCONFIG_H__
#define __REMOTECLIENTCONFIG_H__

/**
 * remote�ͻ���������
 *
 */
class RemoteClientConfig
{
public:
	RemoteClientConfig()
	{
		clientWorkerThreads = 4;
		clientCallbackExecutorThreads = 4;//cpu����
		clientSelectorThreads = 1;
		clientOnewaySemaphoreValue = 256;
		clientAsyncSemaphoreValue = 128;
		connectTimeoutMillis = 3000;

		channelNotActiveInterval = 1000 * 60;// channel����1���Ӳ������� �͹ر�
		clientChannelMaxIdleTimeSeconds = 120;
	}

	// ����Server Response/Request
	int clientWorkerThreads;
	int clientCallbackExecutorThreads;//cpu����
	int clientSelectorThreads;
	int clientOnewaySemaphoreValue;
	int clientAsyncSemaphoreValue;
	int connectTimeoutMillis;

	int channelNotActiveInterval;// channel����1���Ӳ������� �͹ر�
	int clientChannelMaxIdleTimeSeconds;
};

#endif
