/**
* Copyright (C) 2013 kangliqiang, kangliq@163.com
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
#if!defined __VALIDATORST_H__
#define  __VALIDATORST_H__

#include <string>
class MQClientException;
class DefaultMQProducer;
class Message;

/**
* ��Ч�Լ�鹫���ࡣ
*
* @author manhong.yqd<jodie.yqd@gmail.com>
* @since 2013-8-28
*/
class Validators
{
public:
	/**
	* ͨ��������ʽ�����ַ�ƥ��
	*
	* @param origin
	* @param patternStr
	* @return
	*/
	static bool regularExpressionMatcher(const std::string& origin, const std::string& patternStr);

	/**
	* ͨ��������ʽ����ƥ����ַ�
	*
	* @param origin
	* @param patternStr
	* @return
	*/
	static std::string getGroupWithRegularExpression(const std::string& origin, const std::string& patternStr);

	/**
	* topic ��Ч�Լ��
	*
	* @param topic
	* @throws MQClientException
	*/
	static void checkTopic(const std::string& topic);

	/**
	* group ��Ч�Լ��
	*
	* @param group
	* @throws MQClientException
	*/
	static void checkGroup(const std::string& group);

	/**
	* message ��Ч�Լ��
	*
	* @param msg
	* @param int maxMessageSize
	* @throws MQClientException
	*/
	static void checkMessage(const Message& msg, int maxMessageSize);

public:
	static const std::string validPatternStr;
	static const int CHARACTER_MAX_LENGTH;
};

#endif
