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
#if!defined __MESSAGEDECODER_H__
#define  __MESSAGEDECODER_H__

#include <string>
#include <list>
#include <map>

#include "SocketUtil.h"
#include "MessageId.h"

class MessageExt;
class UnknownHostException;

/**
* ��Ϣ����
*
*/
class MessageDecoder
{
public:
	static std::string createMessageId(sockaddr& addr, long long offset);
	static MessageId decodeMessageId(const std::string& msgId);

	static MessageExt* decode(const char* pData, int len, int& offset);
	static MessageExt* decode(const char* pData, int len, int& offset, bool readBody);

	static std::list<MessageExt*> decodes(const char* pData, int len);
	static std::list<MessageExt*> decodes(const char* pData, int len, bool readBody);

	static std::string messageProperties2String(const std::map<std::string, std::string>& properties);
	static void string2messageProperties(std::map<std::string, std::string>& properties,
										std::string& propertiesString);

public:
	/**
	* ���л���Ϣ����
	*/
	static const char NAME_VALUE_SEPARATOR;
	static const char PROPERTY_SEPARATOR;

	/**
	* ��ϢID����
	*/
	static const int MSG_ID_LENGTH;

	/**
	* �洢��¼�����ֶ�λ��
	*/
	static int MessageMagicCodePostion;
	static int MessageFlagPostion;
	static int MessagePhysicOffsetPostion;
	static int MessageStoreTimestampPostion;
};

#endif
