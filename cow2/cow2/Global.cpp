#include "StdAfx.h"
#include "StdAfx.h"
bool sedFlag=false;
bool refFlagTime=false;//�ڵ��ȡ���ݵļ������
bool nodeFlag=false;
bool nodeFlagSuccess=false;

int reftime;
CString  nodeUp="";   //dlg1�Ľڵ����� 
CString  nodeUpDelayed="";//dlg1�Ľڵ�������ʱ
CString  nodeDown="";//dlg1�Ľڵ�����
CString  nodeDownDelayed="";//dlg1�Ľڵ�������ʱ
CString  str_dbname;
CString str_TableName=(CTime::GetCurrentTime()).Format("cow%Y%m%d");
CString fileName;
CString node[999];
CString cowName[999];
CString str_getTime;

CString str_UserName[999];
CString str_Pwd[999];
bool UserFlag=false;
CString str_Ip;
CString str_Port;
CString str_id;//��ǰ��¼���û�
int PortNum=0;
CString Com;//COM�ں�
CString PTY;//������
CStringList  ListCowData;
CStringList ListCowDataTime;
