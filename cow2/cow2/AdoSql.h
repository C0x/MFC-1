#pragma once
#define WM_USERMESSAGE WM_USER+101
class CAdoSql
{
public:
	CAdoSql(void);
	~CAdoSql(void);
public:
	bool DIYUseSQL(CString strOrder);//ʹ�����ݿ�
	void DIYInsertName(CString name,CString pwd);//�����û�����
	void DIYCreatDateBase();//�������ݿ�
	void DIYCreatTable();//�����û����ݱ�
	void DIYGetInfoOfUser();
	void DIYCreatCowTable(CString CowNode);//�ڵ��
	void DIYCrestCowInfoTable();//��ţ��Ϣ��
	void DIYGetCowInfo();
	void DIYInsertCowInfo(CString node,CString cow);//������ţ��Ϣ
	bool DIYInsertCowData(CString node,CString data,CString strtime,CString time);//����������
	void DIYGetCowData(CString node);//��ȡ�ڵ�����
	void DIYDeleteCowData(CString node);//ɾ����ţ�ڵ��
	bool DIYUpdateCowInfo(CString node,CString cowName);//������ţ��Ϣ
	void DIYTnsertASA(CString id,CString date,CString time,CString data);
	void DIYGetASA(CString strOrder);
	CString DIYTransfrom(char buf);//�������ݴ���
	void DIYDelTable(CString num);
	void DIYTnsertCowMysql(CString id,CString cowID);
	void DIYUpdateCowMysql(CString id,CString cowID);
	void DIYTnsertMysql(CString id,CString date,CString time,CString data);
	void DIYADOMysql(CString id,CString date,CString time,CString data);
	void DIYGetCowDataByDay(CString node,CString time);
	void DIYADOMysqlorder(CString id,CString date,CString time,CString data);
	void SaveLog(CString strText);
};

