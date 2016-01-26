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

#if!defined __PROCESSQUEUE_H__
#define __PROCESSQUEUE_H__

#include <list>
#include <map>

#include "Mutex.h"
#include "AtomicValue.h"

class MessageExt;

/**
* ���ڱ����ѵĶ��У�����Ϣ
*
*/
class ProcessQueue
{

public:
	ProcessQueue();

	bool isLockExpired();

	/**
	* @return �Ƿ���Ҫ�ַ���ǰ���е������̳߳�
	*/
	bool putMessage(const std::list<MessageExt*>& msgs);

	/**
	* ��ȡ��ǰ���е������
	*/
	long long getMaxSpan();

	/**
	* ɾ���Ѿ����ѹ�����Ϣ��������СOffset�����Offset��Ӧ����Ϣδ����
	*
	* @param msgs
	* @return
	*/
	long long removeMessage(const std::list<MessageExt*>& msgs);

	std::map<long long, MessageExt*> getMsgTreeMap();

	AtomicLong getMsgCount();
	bool isDropped();
	void setDropped(bool dropped);

	/**
	* ========================================================================
	* ���²���Ϊ˳����Ϣר�в���
	*/

	void setLocked(bool locked);
	bool isLocked();
	void rollback();

	long long commit();
	void makeMessageToCosumeAgain(const std::list<MessageExt*>& msgs);

	/**
	* ���ȡ������Ϣ������������״̬��Ϊfalse
	*
	* @param batchSize
	* @return
	*/
	std::list<MessageExt*> takeMessages(int batchSize);

	long long getLastLockTimestamp();
	void setLastLockTimestamp(long long lastLockTimestamp);

public:
	static unsigned int s_RebalanceLockMaxLiveTime;// �ͻ��˱���Lock������ʱ�䣬�������Զ����ڣ���λms
	static unsigned int s_RebalanceLockInterval;// ��ʱLock���ʱ�䣬��λms

private:
	kpr::Mutex m_lockTreeMap;
	std::map<long long, MessageExt*> m_msgTreeMap;
	volatile long long m_queueOffsetMax ;
	AtomicLong m_msgCount;
	volatile bool m_dropped;// ��ǰQ�Ƿ�rebalance����

	/**
	* ˳����Ϣר��
	*/
	volatile bool m_locked;// �Ƿ��Broker����
	volatile unsigned long long m_lastLockTimestamp;// ���һ�������ɹ�ʱ���
	volatile bool m_consuming;// �Ƿ����ڱ�����
	std::map<long long, MessageExt*> m_msgTreeMapTemp;// ����ʽ���ѣ�δ�ύ����Ϣ
};

#endif
