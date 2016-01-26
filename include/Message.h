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

#if!defined __MESSAGE_H__
#define __MESSAGE_H__

#include <map>
#include <string>
#include <list>
#include "RocketMQClient.h"

/**
* ��Ϣ��Producer��Consumerʹ��
*
*/
class ROCKETMQCLIENT_API Message
{
public:
	Message();
	Message(const std::string& topic, const char* body,int len);
	Message(const std::string& topic, const std::string& tags, const char* body,int len);
	Message(const std::string& topic, const std::string& tags,const std::string& keys, const char* body,int len);
	Message(const std::string& topic,
			const std::string& tags,
			const std::string& keys,
			const int	flag,
			const char* body,
			int len,
			bool waitStoreMsgOK);

	virtual ~Message();
	Message(const Message& other);
	Message& operator=(const Message& other);

	void clearProperty(const std::string& name);
	void putProperty(const std::string& name, const std::string& value);
	std::string getProperty(const std::string& name);

	std::string getTopic()const;
	void setTopic(const std::string& topic);

	std::string getTags();
	void setTags(const std::string& tags);

	std::string getKeys();
	void setKeys(const std::string& keys);
	void setKeys(std::list<std::string> keys);

	int getDelayTimeLevel();
	void setDelayTimeLevel(int level);

	bool isWaitStoreMsgOK();
	void setWaitStoreMsgOK(bool waitStoreMsgOK);

	int getFlag();
	void setFlag(int flag);

	const char* getBody()const;
	int getBodyLen()const;
	void setBody(const char* body,int len);

	std::map<std::string, std::string>& getProperties();
	void setProperties(std::map<std::string, std::string>& properties);

protected:
	void Init(const std::string& topic,
			  const std::string& tags,
			  const std::string& keys,
			  const int	flag,
			  const char* body,
			  int len,
			  bool waitStoreMsgOK);

public:
	/**
	* ��Ϣ�ؼ��ʣ����Key��KEY_SEPARATOR��������ѯ��Ϣʹ�ã�
	*/
	static const std::string PROPERTY_KEYS;

	/**
	* ��Ϣ��ǩ��ֻ֧������һ��Tag���������Ϣ����ʹ�ã�
	*/
	static const std::string PROPERTY_TAGS;

	/**
	* �Ƿ�ȴ�����������Ϣ�洢����ٷ��أ������ǵȴ�ˢ����ɻ��ߵȴ�ͬ�����Ƶ�������������
	*/
	static const std::string PROPERTY_WAIT_STORE_MSG_OK;

	/**
	* ��Ϣ��ʱͶ��ʱ�伶��0��ʾ����ʱ������0��ʾ�ض���ʱ���𣨾��弶���ڷ������˶��壩
	*/
	static const std::string PROPERTY_DELAY_TIME_LEVEL;

	/**
	* �ڲ�ʹ��
	*/
	static const std::string PROPERTY_RETRY_TOPIC;
	static const std::string PROPERTY_REAL_TOPIC;
	static const std::string PROPERTY_REAL_QUEUE_ID;
	static const std::string PROPERTY_TRANSACTION_PREPARED;
	static const std::string PROPERTY_PRODUCER_GROUP;
	static const std::string PROPERTY_MIN_OFFSET;
	static const std::string PROPERTY_MAX_OFFSET;

	static const std::string KEY_SEPARATOR;

private:
	std::string m_topic;///< ��Ϣ����
	int m_flag;///< ��Ϣ��־��ϵͳ������Ԥ����ȫ��Ӧ�þ������ʹ��
	std::map<std::string, std::string> m_properties;///< ��Ϣ���ԣ�ϵͳ�б������ԣ�Ӧ��Ҳ�����Զ�������
	char* m_body;///< ��Ϣ��
	int   m_bodyLen;///< ��Ϣ����
};

#endif
