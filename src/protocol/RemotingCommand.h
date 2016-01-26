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

#if!defined __REMOTINGCOMMAND_H__
#define __REMOTINGCOMMAND_H__

#include <sstream>
#include <string>
#include "AtomicValue.h"

const std::string CODE_STRING="\"code\":";
const std::string language_STRING="\"language\":";
const std::string version_STRING="\"version\":";
const std::string opaque_STRING="\"opaque\":";
const std::string flag_STRING="\"flag\":";
const std::string remark_STRING="\"remark\":";
const std::string extFields_STRING="\"extFields\":";

const std::string RemotingVersionKey = "rocketmq.remoting.version";

class CommandCustomHeader;

typedef enum
{
	REQUEST_COMMAND,
	RESPONSE_COMMAND
} RemotingCommandType;

typedef enum
{
	SUCCESS_VALUE = 0,// �ɹ�
	SYSTEM_ERROR_VALUE,// ������δ�����쳣
	SYSTEM_BUSY_VALUE,// �����̳߳�ӵ�£�ϵͳ��æ
	REQUEST_CODE_NOT_SUPPORTED_VALUE ,// ������벻֧��
} ResponseCode;

typedef enum
{
	JAVA,
	CPP,
	DOTNET,
	PYTHON,
	DELPHI,
	ERLANG,
	RUBY,
	OTHER,
} LanguageCode;

const int RPC_TYPE = 0; // 0, REQUEST_COMMAND // 1, RESPONSE_COMMAND
const int RPC_ONEWAY = 1; // 0, RPC // 1, Oneway

class RemotingCommand
{
public:
	RemotingCommand(int code);
	RemotingCommand(int code,
					const std::string& language,
					int version,
					int opaque,
					int flag,
					const std::string& remark,
					CommandCustomHeader* pCustomHeader);
	~RemotingCommand();

	void Encode();

	const char* GetHead();
	int GetHeadLen();
	void SetData(char* pData,int len);

	const char* GetBody();
	int GetBodyLen();
	void SetBody(char* pData,int len,bool copy);
	void MakeCustomHeader(int code,const char* pData,int len);

	int getCode();
	void setCode(int code);

	std::string getLanguage();
	void setLanguage(const std::string& language);

	int getVersion();
	void setVersion(int version);

	int getOpaque();
	void setOpaque(int opaque);

	int getFlag();
	void setFlag(int flag);

	std::string getRemark();
	void setRemark(const std::string& remark);

	void setCommandCustomHeader(CommandCustomHeader* pCommandCustomHeader);
	CommandCustomHeader*getCommandCustomHeader();

	RemotingCommandType getType();
	void markResponseType();
	bool isResponseType() ;
	void markOnewayRPC();
	bool isOnewayRPC();

	static void setCmdVersion(RemotingCommand* pCmd);
	static RemotingCommand* CreateRemotingCommand(const char* pData,int len);
	static RemotingCommand* createRequestCommand(int code, CommandCustomHeader* pCustomHeader);
	static RemotingCommand* Decode(char* pData,int len);

private:
	static volatile int s_configVersion;

private:
	int m_code;
	std::string m_language;
	int m_version;
	int m_opaque;
	int m_flag;
	std::string m_remark;
	CommandCustomHeader* m_pCustomHeader;

	int m_headLen;
	char* m_pHead;

	int m_bodyLen;
	char* m_pBody;

	bool m_releaseBody;

	static AtomicInteger s_seqNumber;
};

#endif
