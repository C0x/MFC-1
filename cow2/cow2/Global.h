#include "stdafx.h"
#include "stdafx.h"

extern bool refFlagTime;
extern bool sedFlag;//�������ݱ�־λ
extern int  reftime;  //��������ʱ����

extern int  setNode;//�ڵ�������ͽڵ��
extern bool nodeFlag;//�ڵ㹤���������ͱ�־λ
extern bool nodeFlagSuccess;//�ڵ㹤���������ͳɹ���־λ

//��������
extern CString  nodeUp;   //dlg1�Ľڵ����� 
extern CString  nodeUpDelayed;//dlg1�Ľڵ�������ʱ
extern CString  nodeDown;//dlg1�Ľڵ�����
extern CString  nodeDownDelayed;//dlg1�Ľڵ�������ʱ
extern CString  str_dbname;//���ݿ����  cow+��ǰʱ��ʱ����
extern CString  str_TableName;
//�ؼ���̬��ʾ���� �ؼ�����ʾ�����ص����
extern CString fileName;//���������ļ���
extern CString node[999];//��ӽڵ������
extern CString cowName[999];//�ڵ�1��Ӧ����ţ���
extern CString str_getTime;
extern CString str_UserName[999];
extern CString str_Pwd[999];
extern bool UserFlag;
extern CString str_Ip;//Ip��ַ
extern CString	str_Port;//�˿ں�
extern CString str_id;
extern int PortNum;//
extern CString Com;//com�ں�
extern CString PTY;//������
extern CStringList  ListCowData;//
extern CStringList ListCowDataTime;//