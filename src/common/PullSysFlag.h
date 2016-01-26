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

#if!defined __PULLSYSFLAG_H__
#define __PULLSYSFLAG_H__

/**
* Pull�ӿ��õ���flag����
* 
*/
class PullSysFlag 
{
public:
	static int buildSysFlag(bool commitOffset, bool suspend, bool subscription);
	static int clearCommitOffsetFlag(int sysFlag);
	static bool hasCommitOffsetFlag(int sysFlag);
	static bool hasSuspendFlag(int sysFlag);
	static bool hasSubscriptionFlag(int sysFlag);

private:
	static int FLAG_COMMIT_OFFSET;
	static int FLAG_SUSPEND;
	static int FLAG_SUBSCRIPTION;
};

#endif
