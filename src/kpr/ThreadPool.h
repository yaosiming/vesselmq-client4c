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
#if!defined __KPR_THREADPOOL_H__
#define __KPR_THREADPOOL_H__

#include<time.h>
#include <assert.h>
#include <list>
#include "Mutex.h"
#include "Thread.h"
#include "Monitor.h"

#include "ThreadPoolWork.h"

namespace kpr
{
	const int MAX_THREAD_COUNT = 300;
	const int MIN_THREAD_COUNT = 5;
	const int MAX_IDLE_THREAD_TIME = 300000;
	const int THREAD_STEP = 10;
	const int CHECK_IDLE_THREADS_INTERVAL = 30000;

	class ThreadPool;
	class ThreadPoolWorker : public kpr::Thread, public kpr::Monitor
	{
	public:
		ThreadPoolWorker(ThreadPool* pThreadPool, const char* strName);

		virtual void Run();
		void WakeUp();
		void Stop();
		bool IsWaiting();
		bool IsIdle();
		void SetIdle(bool idle);
		int IdleTime(int idleTime);

	private:
		ThreadPool* m_pThreadPool;
		bool m_canWork;
		bool m_isWaiting;
		bool m_stop;
		int m_idleTime;
		bool m_idle;
	};

	DECLAREVAR(ThreadPoolWorker)

	class ThreadPoolManage : public kpr::Thread, public kpr::Monitor
	{
	public:
		ThreadPoolManage(ThreadPool * pThreadPool, int nCheckldleThreadsInterval);

		~ThreadPoolManage();
		virtual void Run();
		void Stop();

	private:
		ThreadPool* m_pThreadPool;
		bool m_stop;
		int m_checkIdleThreadsInterval;
	};

	DECLAREVAR(ThreadPoolManage)

	class ThreadPool : public kpr::Monitor
	{
	public:
		ThreadPool(int initCount,
				   int minCount,
				   int maxCount,
				   int step = THREAD_STEP,
				   int maxIdleTime = MAX_IDLE_THREAD_TIME,
				   int checkldleThreadsInterval = CHECK_IDLE_THREADS_INTERVAL);

		~ThreadPool();
		void Destroy();

		int AddWork(ThreadPoolWork* pWork);
		ThreadPoolWork* GetWork(ThreadPoolWorker* pWorker);

		void RemoveIdleThreads();
		void RemoveThread(ThreadPoolWorker* pWorker);

		bool WakeOneThread();
		bool IsDestroy();

	private:
		void AddThreads(int count);

	private:
		bool m_destroy;
		int m_minCount;
		int m_maxCount;
		int m_maxIdleTime;
		int m_count;
		int m_step;

		unsigned int m_index;
		unsigned long long m_lastRemoveIdleThreadsTime;
		ThreadPoolManage_var m_manager;

		std::list<ThreadPoolWork*> m_works;
		std::list<ThreadPoolWorker_var> m_workers;
	};
}
#endif
