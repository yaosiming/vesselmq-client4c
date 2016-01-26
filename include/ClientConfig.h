/**
 * Copyright (C) 2010-2013 kangliqiang <kangliq@163.com>
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
#if!defined __CLIENTCONFIG_H__
#define __CLIENTCONFIG_H__

#include <string>
#include "RocketMQClient.h"

/**
 * Producer��Consumer�Ĺ�������
 *
 * @author kangliqiang <kangliq@163.com>
 * @since 2013-10-31
 */
class ROCKETMQCLIENT_API ClientConfig
{
public:
	ClientConfig();
	virtual ~ClientConfig();
	
	//clientid=ip@instanceName
	std::string buildMQClientId();

	void resetClientConfig(const ClientConfig& cc);
	ClientConfig cloneClientConfig();

	std::string getNamesrvAddr();
	void setNamesrvAddr(const std::string& namesrvAddr);

	std::string getClientIP();
	void setClientIP(const std::string& clientIP);

	std::string getInstanceName();
	void setInstanceName(const std::string& instanceName);

	int getClientCallbackExecutorThreads();
	void setClientCallbackExecutorThreads(int clientCallbackExecutorThreads);

	int getPollNameServerInterval();

	void setPollNameServerInterval(int pollNameServerInterval);

	int getHeartbeatBrokerInterval();
	void setHeartbeatBrokerInterval(int heartbeatBrokerInterval);

	int getPersistConsumerOffsetInterval();
	void setPersistConsumerOffsetInterval(int persistConsumerOffsetInterval);

private:
	int m_clientCallbackExecutorThreads;
	int m_pollNameServerInterval;
	int m_heartbeatBrokerInterval;
	int m_persistConsumerOffsetInterval;
	std::string m_namesrvAddr;
	std::string m_clientIP;
	std::string m_instanceName;
	static const std::string CLIENT_ID_IP_NAME_SEPARATOR;
};

#endif
