// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ROCKETMQCLIENT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ROCKETMQCLIENT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#if!defined __ROCKETMQCLIENT_H__
#define  __ROCKETMQCLIENT_H__

#ifdef WIN32
#ifdef ROCKETMQCLIENT_EXPORTS
#define ROCKETMQCLIENT_API __declspec(dllexport)
#else
#define ROCKETMQCLIENT_API __declspec(dllimport)
#endif
#else
#define ROCKETMQCLIENT_API
#endif

#endif
