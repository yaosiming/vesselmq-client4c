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
#if!defined __CONSUMETYPE_H__
#define __CONSUMETYPE_H__

#include "RocketMQClient.h"

/**
 * ��������
 *
 */
enum ConsumeType
{
	/**
	* ������ʽ����
	*/
	CONSUME_ACTIVELY,
	/**
	* ������ʽ����
	*/
	CONSUME_PASSIVELY,
};

enum ConsumeFromWhere
{
	/**
	* ÿ�����������ϴμ�¼��λ�㿪ʼ���ѣ�����ǵ�һ������������λ�㿪ʼ���ѣ���������������ʹ��
	*/
	CONSUME_FROM_LAST_OFFSET,
	/**
	* ÿ�����������ϴμ�¼��λ�㿪ʼ���ѣ�����ǵ�һ�����������Сλ�㿪ʼ���ѣ��������ʱʹ��<br>
	* ���ϻ����������������Ҫ��ˣ�������Ч
	*/
	CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST,
	/**
	* ÿ������������Сλ�㿪ʼ���ѣ��������ʱʹ��<br>
	* ���ϻ����������������Ҫ��ˣ�������Ч
	*/
	CONSUME_FROM_MIN_OFFSET,
	/**
	* ÿ�������������λ�㿪ʼ���ѣ��������ʱʹ��
	*/
	CONSUME_FROM_MAX_OFFSET,
};

enum MessageModel
{
	/**
	* �㲥ģ��
	*/
	BROADCASTING,
	/**
	* ��Ⱥģ��
	*/
	CLUSTERING,
	// /**
	// * δ֪��������������ѣ�����ȷ��Ӧ�õ���Ϣģ��
	// */
	// UNKNOWNS,
};

ROCKETMQCLIENT_API const char* getConsumeTypeString(ConsumeType type);
ROCKETMQCLIENT_API const char* getConsumeFromWhereString(ConsumeFromWhere type);
ROCKETMQCLIENT_API const char* getMessageModelString(MessageModel type);

#endif
