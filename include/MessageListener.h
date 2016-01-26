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

#if!defined __MESSAGELISTENER_H__
#define __MESSAGELISTENER_H__

#include <limits.h>
#include <list>

#include "MessageExt.h"
#include "MessageQueue.h"

/**
* ��Ϣ��������������ʽ������Ϣʹ�ã���Ҫ�û�ʵ��<br>
* Ӧ�ò�����ֱ�Ӽ̳д˽ӿ�
*
*/
class ROCKETMQCLIENT_API MessageListener
{
public:
	virtual ~MessageListener(){}
};

enum ConsumeOrderlyStatus
{
	SUCCESS,// ��Ϣ����ɹ�
	ROLLBACK,// �ع���Ϣ
	COMMIT,// �ύ��Ϣ
	SUSPEND_CURRENT_QUEUE_A_MOMENT,// ����ǰ���й���һС���
};

typedef struct tagConsumeOrderlyContext 
{
	tagConsumeOrderlyContext(MessageQueue& mq)
		:messageQueue(mq),
		autoCommit(true),
		suspendCurrentQueueTimeMillis(1000)
	{

	}

	MessageQueue messageQueue;///< Ҫ���ѵ���Ϣ�����ĸ�����
	bool autoCommit;///< ��ϢOffset�Ƿ��Զ��ύ
	long suspendCurrentQueueTimeMillis;
}ConsumeOrderlyContext;

class ROCKETMQCLIENT_API MessageListenerOrderly : public MessageListener
{
	/**
	* �����׳��쳣��ͬ�ڷ��� ConsumeOrderlyStatus.SUSPEND_CURRENT_QUEUE_A_MOMENT<br>
	* P.S: ����Ӧ�ò�Ҫ�׳��쳣
	* 
	* @param msgs
	*            msgs.size() >= 1<br>
	*            DefaultMQPushConsumer.consumeMessageBatchMaxSize=1��Ĭ����Ϣ��Ϊ1
	* @param context
	* @return
	*/
public:
	virtual ConsumeOrderlyStatus consumeMessage(std::list<MessageExt*>& msgs,
												ConsumeOrderlyContext& context)=0;
};

enum ConsumeConcurrentlyStatus
{
	CONSUME_SUCCESS,// ��ʾ���ѳɹ�	
	RECONSUME_LATER,// ��ʾ����ʧ�ܣ������Ժ󻹻���������������Ϣ
};

typedef struct tagConsumeConcurrentlyContext
{
	tagConsumeConcurrentlyContext(MessageQueue& mq)
		:messageQueue(mq),
		delayLevelWhenNextConsume(0),
		ackIndex(INT_MAX)
	{
	}
	MessageQueue messageQueue;///< Ҫ���ѵ���Ϣ�����ĸ�����
	/**
	* �´���Ϣ������ʱʱ��<br>
	* -1����ʾ�����ԣ�ֱ�ӽ������Ŷ���<br>
	* 0����ʾ�ɷ������������Դ����Զ�����<br>
	* >0����ʾ�ͻ���ǿ��ָ����ʱLevel
	*/
	int delayLevelWhenNextConsume;
	int ackIndex;///< �����������ѣ�ack��������Ϣ��Ĭ��ȫ��ack�������һ����Ϣ

}ConsumeConcurrentlyContext;

class ROCKETMQCLIENT_API MessageListenerConcurrently : public MessageListener
{
public:
	/**
	* �����׳��쳣��ͬ�ڷ��� ConsumeConcurrentlyStatus.RECONSUME_LATER<br>
	* P.S: ����Ӧ�ò�Ҫ�׳��쳣
	* 
	* @param msgs
	*            msgs.size() >= 1<br>
	*            DefaultMQPushConsumer.consumeMessageBatchMaxSize=1��Ĭ����Ϣ��Ϊ1
	* @param context
	* @return
	*/
	virtual ConsumeConcurrentlyStatus consumeMessage(std::list<MessageExt*>& msgs,
													ConsumeConcurrentlyContext& context)=0;
};

#endif
