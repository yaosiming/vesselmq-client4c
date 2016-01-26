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

#if!defined __MQCONSUMER_H__
#define __MQCONSUMER_H__

#include <set>
#include <string>

#include "MQAdmin.h"
#include "ConsumeType.h"
#include "RocketMQClient.h"

class MessageExt;


/**
* Consumer�ӿ�
*
*/
class ROCKETMQCLIENT_API MQConsumer : public MQAdmin
{
public:
	virtual ~MQConsumer(){}
	/**
	* ��������
	*
	* @throws MQClientException
	*/
	virtual void  start()=0;
	
	/**
	* �رշ���
	*/
	virtual void shutdown()=0;

	/**
	* Consumer����ʧ�ܵ���Ϣ����ѡ�����·��ص��������ˣ�����ʱ����<br>
	* �����ȳ��Խ���Ϣ���ص���Ϣ֮ǰ�洢����������ʱֻ������ϢOffset����Ϣ�岻���ͣ�����ռ���������<br>
	* �������ʧ�ܣ����Զ����Է���������������ʱ��Ϣ��Ҳ�ᴫ��<br>
	* �ش���ȥ����Ϣֻ�ᱻ��ǰConsumer Group���ѡ�
	*
	* @param msg
	* @param delayLevel
	* @throws InterruptedException
	* @throws MQBrokerException
	* @throws RemotingException
	* @throws MQClientException
	*/
	virtual void sendMessageBack(MessageExt& msg, int delayLevel)=0;
	
	/**
	* ����topic��ȡ��Ӧ��MessageQueue���ǿɱ����ĵĶ���<br>
	* P.S ��Consumer Cache�������ݣ�����Ƶ�����á�Cache�����ݴ�Լ30�����һ��
	*
	* @param topic
	*            ��ϢTopic
	* @return ���ض��м���
	* @throws MQClientException
	*/
	virtual std::set<MessageQueue>* fetchSubscribeMessageQueues(const std::string& topic)=0;
};

#endif
