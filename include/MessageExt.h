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
#if!defined __MESSAGEEXT_H__
#define __MESSAGEEXT_H__

#ifdef WIN32
#include <Winsock2.h>
#include <Windows.h>
#else
#include <sys/socket.h>
#endif

#include <string>
#include "Message.h"
#include "TopicFilterType.h"
#include "RocketMQClient.h"

/**
* ��Ϣ��չ���ԣ��ڷ������ϲ����˶���
*
*/
class ROCKETMQCLIENT_API MessageExt : public Message
{
public:
	MessageExt();

	MessageExt(int queueId,
			   long long bornTimestamp,
			   sockaddr bornHost,
			   long long storeTimestamp,
			   sockaddr storeHost,
			   std::string msgId);
	
	~MessageExt();

	static TopicFilterType parseTopicFilterType(int sysFlag);

	int getQueueId();
	void setQueueId(int queueId);

	long long getBornTimestamp();
	void setBornTimestamp(long long bornTimestamp);

	sockaddr getBornHost();
	std::string getBornHostString();
	std::string getBornHostNameString();
	void setBornHost(const sockaddr& bornHost);

	long long getStoreTimestamp();
	void setStoreTimestamp(long long storeTimestamp);

	sockaddr getStoreHost();
	void setStoreHost(const sockaddr& storeHost);

	std::string getMsgId();
	void setMsgId(const std::string& msgId);

	int getSysFlag();
	void setSysFlag(int sysFlag);

	int getBodyCRC();
	void setBodyCRC(int bodyCRC);

	long long getQueueOffset();
	void setQueueOffset(long long queueOffset);

	long long getCommitLogOffset();
	void setCommitLogOffset(long long physicOffset);

	int getStoreSize();
	void setStoreSize(int storeSize);

	int getReconsumeTimes();
	void setReconsumeTimes(int reconsumeTimes);

	long long getPreparedTransactionOffset();
	void setPreparedTransactionOffset(long long preparedTransactionOffset);

private:
	long long m_queueOffset;// ����ƫ����
	long long m_commitLogOffset;// ��Ϣ��Ӧ��Commit Log Offset
	long long m_bornTimestamp;// ��Ϣ�ڿͻ��˴���ʱ��� <PUT>
	long long m_storeTimestamp;// ��Ϣ�ڷ������洢ʱ���
	long long m_preparedTransactionOffset;
	int m_queueId;// ����ID <PUT>
	int m_storeSize;// �洢��¼��С	
	int m_sysFlag;// ��Ϣ��־λ <PUT>
	int m_bodyCRC;// ��Ϣ��CRC
	int m_reconsumeTimes;// ��ǰ��Ϣ��ĳ�����������������˼��Σ�������֮�����������
	sockaddr m_bornHost;// ��Ϣ�������� <PUT>	
	sockaddr m_storeHost;// ��Ϣ�洢���ĸ������� <PUT>
	std::string m_msgId;// ��ϢID
};

#endif
