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
#include "Message.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const std::string Message::PROPERTY_KEYS = "KEYS";
const std::string Message::PROPERTY_TAGS = "TAGS";
const std::string Message::PROPERTY_WAIT_STORE_MSG_OK = "WAIT";
const std::string Message::PROPERTY_DELAY_TIME_LEVEL = "DELAY";

const std::string Message::PROPERTY_RETRY_TOPIC = "RETRY_TOPIC";
const std::string Message::PROPERTY_REAL_TOPIC = "REAL_TOPIC";
const std::string Message::PROPERTY_REAL_QUEUE_ID = "REAL_QID";
const std::string Message::PROPERTY_TRANSACTION_PREPARED = "TRAN_MSG";
const std::string Message::PROPERTY_PRODUCER_GROUP = "PGROUP";
const std::string Message::PROPERTY_MIN_OFFSET = "MIN_OFFSET";
const std::string Message::PROPERTY_MAX_OFFSET = "MAX_OFFSET";

const std::string Message::KEY_SEPARATOR = " ";

Message::Message()
{
	Init("","","",0,0,0,true);
}

Message::Message(const std::string& topic, const char* body,int len)
{
	Init(topic,"","",0,body,len,true);
}

Message::Message(const std::string& topic, const std::string& tags, const char* body,int len)
{
	Init(topic,tags,"",0,body,len,true);
}

Message::Message(const std::string& topic, const std::string& tags,const std::string& keys, const char* body,int len)
{
	Init(topic,tags,keys,0,body,len,true);
}

Message::Message(const std::string& topic,
				 const std::string& tags,
				 const std::string& keys,
				 const int	flag,
				 const char* body,
				 int len,
				 bool waitStoreMsgOK)
{
	Init(topic,tags,keys,flag,body,len,waitStoreMsgOK);
}

Message::~Message()
{
	delete m_body;
}

Message::Message(const Message& other)
{
	m_body = new char[other.m_bodyLen];
	m_bodyLen = other.m_bodyLen;
	memcpy(m_body,other.m_body,other.m_bodyLen);
	m_topic = other.m_topic;
	m_flag = other.m_flag;
	m_properties = other.m_properties;
}

Message& Message::operator=(const Message& other)
{
	if (this!=&other)
	{
		char* tmp = new char[other.m_bodyLen];
		m_bodyLen = other.m_bodyLen;
		delete[] m_body;
		m_body = tmp;
		memcpy(m_body,other.m_body,other.m_bodyLen);
		
		m_topic = other.m_topic;
		m_flag = other.m_flag;
		m_properties = other.m_properties;
	}

	return *this;
}

void Message::clearProperty(const std::string& name)
{
	m_properties.erase(name);
}

void Message::putProperty(const std::string& name, const std::string& value)
{
	m_properties[name]=value;
}

std::string Message::getProperty(const std::string& name)
{
	std::map<std::string,std::string>::const_iterator it = m_properties.find(name);

	return (it==m_properties.end())?"":(*it).second;
}

std::string Message::getTopic()const
{
	return m_topic;
}

void Message::setTopic(const std::string& topic)
{
	m_topic = topic;
}

std::string Message::getTags()
{
	return getProperty(PROPERTY_TAGS);
}

void Message::setTags(const std::string& tags)
{
	putProperty(PROPERTY_TAGS, tags);
}

std::string Message::getKeys()
{
	return getProperty(PROPERTY_KEYS);
}

void Message::setKeys(const std::string& keys)
{
	putProperty(PROPERTY_KEYS, keys);
}

void Message::setKeys(std::list<std::string> keys)
{
	if (keys.empty())
	{
		return;
	}

	std::list<std::string>::const_iterator it = keys.begin();
	std::string str;
	str += *it;
	it++;

	for (; it!=keys.end(); it++)
	{
		str += KEY_SEPARATOR;
		str += *it;
	}

	setKeys(str);
}

int Message::getDelayTimeLevel()
{
	std::string tmp = getProperty(PROPERTY_DELAY_TIME_LEVEL);
	if (!tmp.empty())
	{
		return atoi(tmp.c_str());
	}

	return 0;
}

void Message::setDelayTimeLevel(int level)
{
	char tmp[16];
	sprintf(tmp,"%d",level);

	putProperty(PROPERTY_DELAY_TIME_LEVEL, tmp);
}

bool Message::isWaitStoreMsgOK()
{
	std::string tmp = getProperty(PROPERTY_WAIT_STORE_MSG_OK);
	if (tmp.empty())
	{
		return true;
	}
	else
	{
		return (tmp=="true")?true:false;
	}
}

void Message::setWaitStoreMsgOK(bool waitStoreMsgOK)
{
	if (waitStoreMsgOK)
	{
		putProperty(PROPERTY_WAIT_STORE_MSG_OK, "true");
	}
	else
	{
		putProperty(PROPERTY_WAIT_STORE_MSG_OK, "false");
	}
}

int Message::getFlag()
{
	return m_flag;
}

void Message::setFlag(int flag)
{
	m_flag = flag;
}

const char* Message::getBody()const
{
	return m_body;
}

int Message::getBodyLen()const
{
	return m_bodyLen;
}

void Message::setBody(const char* body,int len)
{
	if (len>0)
	{
		char* tmp = new char[len];
		m_bodyLen = len;
		delete[] m_body;
		m_body = tmp;

		memcpy(m_body,body,len);
	}
}

std::map<std::string, std::string>& Message::getProperties()
{
	return m_properties;
}

void Message::setProperties(std::map<std::string, std::string>& properties)
{
	m_properties=properties;
}

void Message::Init( const std::string& topic, const std::string& tags, const std::string& keys, const int flag, const char* body, int len, bool waitStoreMsgOK )
{
	m_topic = topic;
	m_flag = flag;
	m_bodyLen = len;
	m_body = NULL;

	if (len>0)
	{
		m_body = new char[len];
		memcpy(m_body,body,len);
	}

	if (tags.length() > 0)
	{
		setTags(tags);
	}

	if (keys.length() > 0)
	{
		setKeys(keys);
	}

	setWaitStoreMsgOK(waitStoreMsgOK);
}
