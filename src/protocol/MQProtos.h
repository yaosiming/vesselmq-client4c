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
#if!defined __MQPROTOS_H__
#define __MQPROTOS_H__

enum MQRequestCode
{
	// Broker ������Ϣ
	SEND_MESSAGE_VALUE = 10,
	// Broker ������Ϣ
	PULL_MESSAGE = 11,
	// Broker ��ѯ��Ϣ
	QUERY_MESSAGE_VALUE = 12,
	// Broker ��ѯBroker Offset
	QUERY_BROKER_OFFSET_VALUE = 13,
	// Broker ��ѯConsumer Offset
	QUERY_CONSUMER_OFFSET_VALUE = 14,
	// Broker ����Consumer Offset
	UPDATE_CONSUMER_OFFSET_VALUE = 15,
	// Broker ���»�������һ��Topic
	UPDATE_AND_CREATE_TOPIC_VALUE = 17,
	// Broker ��ȡ����Topic�����ã�Slave��Namesrv������Master��������ã�
	GET_ALL_TOPIC_CONFIG_VALUE = 21,
	// Broker ��ȡ����Topic���ã�Slave��Namesrv������Master��������ã�
	GET_TOPIC_CONFIG_LIST_VALUE = 22,
	// Broker ��ȡ����Topic�����б�
	GET_TOPIC_NAME_LIST_VALUE = 23,
	// Broker ����Broker�ϵ�����
	UPDATE_BROKER_CONFIG_VALUE = 25,
	// Broker ��ȡBroker�ϵ�����
	GET_BROKER_CONFIG_VALUE = 26,
	// Broker ����Brokerɾ���ļ�
	TRIGGER_DELETE_FILES_VALUE = 27,
	// Broker ��ȡBroker����ʱ��Ϣ
	GET_BROKER_RUNTIME_INFO_VALUE = 28,
	// Broker ����ʱ���ѯ���е�Offset
	SEARCH_OFFSET_BY_TIMESTAMP_VALUE = 29,
	// Broker ��ѯ�������Offset
	GET_MAX_OFFSET_VALUE = 30,
	// Broker ��ѯ������СOffset
	GET_MIN_OFFSET_VALUE = 31,
	// Broker ��ѯ����������Ϣ��Ӧʱ��
	GET_EARLIEST_MSG_STORETIME_VALUE = 32,
	// Broker ������ϢID����ѯ��Ϣ
	VIEW_MESSAGE_BY_ID_VALUE = 33,
	// Broker Client��Client������������ע������
	HEART_BEAT_VALUE = 34,
	// Broker Clientע��
	UNREGISTER_CLIENT_VALUE = 35,
	// Broker Consumer�������˵���Ϣ���ط�����
	CONSUMER_SEND_MSG_BACK_VALUE = 36,
	// Broker Commit����Rollback����
	END_TRANSACTION_VALUE = 37,
	// Broker ��ȡConsumerId�б�ͨ��GroupName
	GET_CONSUMER_LIST_BY_GROUP = 38,
	// Broker ������Producer�ز�����״̬
	CHECK_TRANSACTION_STATE_VALUE = 39,
	// Broker Broker֪ͨConsumer�б�仯
	NOTIFY_CONSUMER_IDS_CHANGED_VALUE = 40,
	// Broker Consumer��Master��������
	LOCK_BATCH_MQ_VALUE = 41,
	// Broker Consumer��Master��������
	UNLOCK_BATCH_MQ_VALUE = 42,
	// Broker ��ȡ����Consumer Offset
	GET_ALL_CONSUMER_OFFSET_VALUE = 43,
	// Broker ��ȡ���ж�ʱ����
	GET_ALL_DELAY_OFFSET_VALUE = 45,
	// Namesrv ��Namesrv׷��KV����
	PUT_KV_CONFIG_VALUE = 100,
	// Namesrv ��Namesrv��ȡKV����
	GET_KV_CONFIG_VALUE = 101,
	// Namesrv ��Namesrv��ȡKV����
	DELETE_KV_CONFIG_VALUE = 102,
	// Namesrv ע��һ��Broker�����ݶ��ǳ־û��ģ���������򸲸�����
	REGISTER_BROKER_VALUE = 103,
	// Namesrv ж��һ��Broker�����ݶ��ǳ־û���
	UNREGISTER_BROKER_VALUE = 104,
	// Namesrv ����Topic��ȡBroker Name��������(������������д����)
	GET_ROUTEINTO_BY_TOPIC_VALUE = 105,
	// Namesrv ��ȡע�ᵽName Server������Broker��Ⱥ��Ϣ
	GET_BROKER_CLUSTER_INFO_VALUE = 106,
	UPDATE_AND_CREATE_SUBSCRIPTIONGROUP_VALUE = 200,
	GET_ALL_SUBSCRIPTIONGROUP_CONFIG_VALUE = 201,
	GET_TOPIC_STATS_INFO_VALUE = 202,
	GET_CONSUMER_CONNECTION_LIST_VALUE = 203,
	GET_PRODUCER_CONNECTION_LIST_VALUE = 204,
	WIPE_WRITE_PERM_OF_BROKER_VALUE = 205,

	// ��Name Server��ȡ����Topic�б�
	GET_ALL_TOPIC_LIST_FROM_NAMESERVER_VALUE = 206,
	// ��Brokerɾ��������
	DELETE_SUBSCRIPTIONGROUP_VALUE = 207,
	// ��Broker��ȡ����״̬�����ȣ�
	GET_CONSUME_STATS_VALUE = 208,
	// Suspend Consumer���ѹ���
	SUSPEND_CONSUMER_VALUE = 209,
	// Resume Consumer���ѹ���
	RESUME_CONSUMER_VALUE = 210,
	// ����Consumer Offset
	RESET_CONSUMER_OFFSET_IN_CONSUMER_VALUE = 211,
	// ����Consumer Offset
	RESET_CONSUMER_OFFSET_IN_BROKER_VALUE = 212,
	// ����Consumer�̳߳�����
	ADJUST_CONSUMER_THREAD_POOL_VALUE = 213,
	// ��ѯ��Ϣ����Щ����������
	WHO_CONSUME_THE_MESSAGE_VALUE = 214,

	// ��Brokerɾ��Topic����
	DELETE_TOPIC_IN_BROKER_VALUE = 215,
	// ��Namesrvɾ��Topic����
	DELETE_TOPIC_IN_NAMESRV_VALUE = 216,
	// Namesrv ͨ�� project ��ȡ���е� server ip ��Ϣ
	GET_KV_CONFIG_BY_VALUE_VALUE = 217,
	// Namesrv ɾ��ָ�� project group �µ����� server ip ��Ϣ
	DELETE_KV_CONFIG_BY_VALUE_VALUE = 218,
	// ͨ��NameSpace��ȡ���е�KV List
	GET_KVLIST_BY_NAMESPACE_VALUE = 219,
};

enum MQResponseCode
{
	// Broker ˢ�̳�ʱ
	FLUSH_DISK_TIMEOUT_VALUE = 10,
	// Broker ͬ��˫д��Slave������
	SLAVE_NOT_AVAILABLE_VALUE = 11,
	// Broker ͬ��˫д���ȴ�SlaveӦ��ʱ
	FLUSH_SLAVE_TIMEOUT_VALUE = 12,
	// Broker ��Ϣ�Ƿ�
	MESSAGE_ILLEGAL_VALUE = 13,
	// Broker, Namesrv ���񲻿��ã����������ڹرջ���Ȩ������
	SERVICE_NOT_AVAILABLE_VALUE = 14,
	// Broker, Namesrv �汾�Ų�֧��
	VERSION_NOT_SUPPORTED_VALUE = 15,
	// Broker, Namesrv ��Ȩ��ִ�д˲����������Ƿ����ա�������������
	NO_PERMISSION_VALUE = 16,
	// Broker, Topic������
	TOPIC_NOT_EXIST_VALUE = 17,
	// Broker, Topic�Ѿ����ڣ�����Topic
	TOPIC_EXIST_ALREADY_VALUE = 18,
	// Broker ����Ϣδ�ҵ��������Offset�������Offset�����Offset�޶�Ӧ��Ϣ��
	PULL_NOT_FOUND_VALUE = 19,
	// Broker ���ܱ����ˣ�������֪ͨ��
	PULL_RETRY_IMMEDIATELY_VALUE = 20,
	// Broker ����Ϣ�����Offset���Ϸ���̫С��̫��
	PULL_OFFSET_MOVED_VALUE = 21,
	// Broker ��ѯ��Ϣδ�ҵ�
	QUERY_NOT_FOUND_VALUE = 22,
	// Broker ���Ĺ�ϵ����ʧ��
	SUBSCRIPTION_PARSE_FAILED_VALUE = 23,
	// Broker ���Ĺ�ϵ������
	SUBSCRIPTION_NOT_EXIST_VALUE = 24,
	// Broker ���Ĺ�ϵ�������µ�
	SUBSCRIPTION_NOT_LATEST_VALUE = 25,
	// Broker �����鲻����
	SUBSCRIPTION_GROUP_NOT_EXIST_VALUE = 26,
	// Producer ����Ӧ�ñ��ύ
	TRANSACTION_SHOULD_COMMIT_VALUE = 200,
	// Producer ����Ӧ�ñ��ع�
	TRANSACTION_SHOULD_ROLLBACK_VALUE = 201,
	// Producer ����״̬δ֪
	TRANSACTION_STATE_UNKNOW_VALUE = 202,
	// Producer ProducerGroup����
	TRANSACTION_STATE_GROUP_WRONG_VALUE = 203,
};

#endif
