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
#if!defined __MQPUSHCONSUMER_H__
#define __MQPUSHCONSUMER_H__

#include <set>
#include <string>

#include "MQConsumer.h"
#include "PullResult.h"
#include "RocketMQClient.h"

class MessageListener;

/**
* �����ߣ�������ʽ����
*
*/
class ROCKETMQCLIENT_API MQPushConsumer : public MQConsumer
{
public:
	/**
	* ע����Ϣ��������һ��Consumerֻ����һ��������
	*
	* @param messageListener
	*/
	virtual void registerMessageListener(MessageListener* pMessageListener)=0;

	/**
	* ������Ϣ���������Ե��ö�������Ĳ�ͬ��Topic��Ҳ�ɸ���֮ǰTopic�Ķ��Ĺ��˱��ʽ
	*
	* @param topic
	*            ��Ϣ����
	* @param subExpression
	*            ���Ĺ��˱��ʽ�ַ�����broker���ݴ˱��ʽ���й��ˡ�Ŀǰֻ֧�ֻ�����<br>
	*            eg: "tag1 || tag2 || tag3"<br>
	*            ���subExpression����null����*�����ʾȫ������
	* @param listener
	*            ��Ϣ�ص�������
	* @throws MQClientException
	*/
	virtual  void subscribe(const std::string& topic, const std::string& subExpression)=0;

	/**
	* ȡ�����ģ��ӵ�ǰ��������ע������Ϣ�ᱻ�����������������߶���
	*
	* @param topic
	*            ��Ϣ����
	*/
	virtual void unsubscribe(const std::string& topic)=0;

	/**
	* ��̬���������̳߳��߳�����
	*
	* @param corePoolSize
	*/
	virtual void updateCorePoolSize(int corePoolSize)=0;

	/**
	* �����̹߳�����ͣ����
	*/
	virtual void suspend()=0;

	/**
	* �����ָ̻߳�����������
	*/
	virtual void resume()=0;
};

#endif
