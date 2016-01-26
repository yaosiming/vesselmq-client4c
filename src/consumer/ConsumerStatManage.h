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
#if!defined __CONSUMERSTAT_H__
#define __CONSUMERSTAT_H__

#include <list>
#include <string>

#include "AtomicValue.h"

/**
* Consumer�ڲ�����ʱͳ����Ϣ
*
*/
typedef struct 
{
	long long createTimestamp;// ���ʱ���	
	AtomicLong consumeMsgRTMax;// һ��������Ϣ�����RT
	AtomicLong consumeMsgRTTotal;// ÿ��������ϢRT�����ܺ�
	AtomicLong consumeMsgOKTotal;// ������Ϣ�ɹ������ܺ�	
	AtomicLong consumeMsgFailedTotal;// ������Ϣʧ�ܴ����ܺ�	
	AtomicLong pullRTTotal;// ����ϢRT�����ܺͣ�ֻ�����ɹ������ģ�	
	AtomicLong pullTimesTotal;// ����Ϣ������ֻ�����ɹ������ģ�
}ConsumerStat;

/**
* ����ͳ��Consumer����״̬
*
*/
class ConsumerStatManager
{
public:
	ConsumerStat& getConsumertat()
	{
		return m_consumertat;
	}

	std::list<ConsumerStat>& getSnapshotList()
	{
		return m_snapshotList;
	}

	/**
	* ÿ��1���¼һ��
	*/
	void recordSnapshotPeriodically()
	{
		m_snapshotList.push_back(m_consumertat);
		if (m_snapshotList.size() > 60)
		{
			m_snapshotList.pop_front();
		}
	}

	/**
	* ÿ��1���Ӽ�¼һ��
	*/
	void logStatsPeriodically(std::string& group, std::string& clientId)
	{
		if (m_snapshotList.size() >= 60)
		{
			ConsumerStat& first = m_snapshotList.front();
			ConsumerStat& last = m_snapshotList.back();

			// �������
			{
				double avgRT = (last.consumeMsgRTTotal.Get() - first.consumeMsgRTTotal.Get())
					/
					(double) ((last.consumeMsgOKTotal.Get() + last.consumeMsgFailedTotal.Get())
					-(first.consumeMsgOKTotal.Get() + first.consumeMsgFailedTotal.Get()));

				double tps = ((last.consumeMsgOKTotal.Get() + last.consumeMsgFailedTotal.Get())
					- (first.consumeMsgOKTotal.Get() + first.consumeMsgFailedTotal.Get()))
					/(double) (last.createTimestamp - first.createTimestamp);

				tps *= 1000;

				//log.info(
				//	"Consumer, {} {}, ConsumeAvgRT: {} ConsumeMaxRT: {} TotalOKMsg: {} TotalFailedMsg: {} consumeTPS: {}",
				//	group,
				//	clientId,
				//	avgRT,
				//	last.consumeMsgRTMax,
				//	last.consumeMsgOKTotal,
				//	last.consumeMsgFailedTotal,
				//	tps);
			}

			// ����Ϣ���
			{
				double avgRT = (last.pullRTTotal.Get() - first.pullRTTotal.Get())
					/(double) (last.pullTimesTotal.Get() - first.pullTimesTotal.Get());

				//log.info("Consumer, {} {}, PullAvgRT: {}  PullTimesTotal: {}",
				//	group,
				//	clientId,
				//	avgRT,
				//	last.pullTimesTotal);
			}
		}
	}

private:
	ConsumerStat m_consumertat;
	std::list<ConsumerStat> m_snapshotList;
};

#endif
