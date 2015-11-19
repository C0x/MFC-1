#include "StdAfx.h"
#include "AdoSql.h"
#include "Global.h"
#include <fstream>
CAdoSql::CAdoSql(void)
{
}
CAdoSql::~CAdoSql(void)
{
}
bool CAdoSql::DIYUseSQL(CString strOrder)
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=db_cows;Data Source=WJ-20140605XBQL";  
		pConn->Open("","","",-1);
		pConn->Execute(_bstr_t(strOrder),NULL,adCmdText);
		return true;
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("���ݿ��������"+strMsg),0);
		//AfxMessageBox("���ݿ��������"+strMsg);
		return false;
		//editAppend("���ݿ��������"+strMsg);
	}
}
void CAdoSql::DIYCreatDateBase()
{
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=master;Data Source=WJ-20140605XBQL";  
		pConn->Open("","","",-1);
		pConn->Execute("if exists (select * from sys.databases where name = 'db_cows')  select * from sys.databases where name = 'db_cows' else create database db_cows ",NULL,adCmdText);
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("���ݿⴴ������"+strMsg),0);
	}

}
void CAdoSql::DIYCreatTable()
{
	CString str_order;
	str_order="if exists (select * from sysobjects where id = object_id(N'";
	str_order=str_order+"Users"+"') and OBJECTPROPERTY(id, N'IsUserTable') = 1) 	select * from  ";
	str_order=str_order+"Users"+"  else  ";
	str_order=str_order+"create table ";
	str_order=str_order+"Users";
	str_order=str_order+"(�û���   varchar(50)  ,����   varchar(50))";
	DIYUseSQL(str_order);
}
void CAdoSql::DIYInsertName(CString name,CString pwd)
{
	CString str_o;
	str_o="IF ((SELECT  Count(*)  FROM Users WHERE �û���='";
	str_o=str_o+name+"' and �û���='";
	str_o=str_o+name+"')>0)";
	str_o=str_o+"UPDATE Users SET ���� = '";
	str_o=str_o+pwd+"' WHERE �û��� = '";
	str_o=str_o+name+"' else INSERT INTO Users (�û���,����) VALUES ('";
	str_o=str_o+name+"','";
	str_o=str_o+pwd+"')";
	DIYUseSQL(str_o);
}
void CAdoSql::DIYGetInfoOfUser()
{
	for(int i=0;i<50;i++)
		str_UserName[i]="";
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=db_cows;Data Source=WJ-20140605XBQL";
		pConn->Open("","","",-1);
		pRst=pConn->Execute("SELECT  *  FROM Users",NULL,adCmdText);
		_variant_t   vNum;  
		_bstr_t      bstr;  
		int m_i=0;
		while(!pRst->EndOfFile)
		{
			CString str="";
			vNum =pRst->GetCollect("�û���");
			bstr = vNum;          
			str = (LPCSTR)bstr;
			str_UserName[m_i]=str;
			CString str2="";
			vNum =pRst->GetCollect("����");
			bstr = vNum;          
			str2 = (LPCSTR)bstr;
			str_Pwd[m_i]=str2;
			pRst->MoveNext();
			m_i++;
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("��ȡ�û���Ϣ����"+strMsg),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CAdoSql::DIYCreatCowTable(CString CowNode)
{
	CString str_order;
	str_order="if exists (select * from sysobjects where id = object_id(N'";
	str_order=str_order+"�½ڵ�"+CowNode+"') and OBJECTPROPERTY(id, N'IsUserTable') = 1) 	select * from  ";
	str_order=str_order+"�½ڵ�"+CowNode+"  else  ";
	str_order=str_order+"create table ";
	str_order=str_order+"�½ڵ�"+CowNode;
	str_order=str_order+"(�ɼ�����   varchar(50)  ,�ɼ�ʱ��  varchar(50)  ,���   varchar(50))";
	DIYUseSQL(str_order);
}
void CAdoSql::DIYGetCowInfo()
{
	for (int i=0;i<999;i++)
	{
		node[i]="";
		cowName[i]="";
	}
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=db_cows;Data Source=WJ-20140605XBQL";
		pConn->Open("","","",-1);
		pRst=pConn->Execute("SELECT  *  FROM ��ţ��Ϣ",NULL,adCmdText);
		_variant_t   vNum;  
		_bstr_t      bstr;  
		int m_i=0;
		while(!pRst->EndOfFile)
		{
			CString str="";
			vNum =pRst->GetCollect("�ڵ��");
			bstr = vNum;          
			str = (LPCSTR)bstr;
			node[m_i]=str;
			CString str2="";
			vNum =pRst->GetCollect("��ţ�����");
			bstr = vNum;          
			str2 = (LPCSTR)bstr;
			cowName[m_i]=str2;
			pRst->MoveNext();
			m_i++;
			PortNum=m_i;
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("��ȡ��ţ��Ϣ����"+strMsg),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CAdoSql::DIYCrestCowInfoTable()
{
	CString str_order;
	str_order="if exists (select * from sysobjects where id = object_id(N'";
	str_order=str_order+"��ţ��Ϣ"+"') and OBJECTPROPERTY(id, N'IsUserTable') = 1) 	select * from  ";
	str_order=str_order+"��ţ��Ϣ"+"  else  ";
	str_order=str_order+"create table ";
	str_order=str_order+"��ţ��Ϣ";
	str_order=str_order+"(�ڵ��   varchar(50)  ,��ţ�����   varchar(50))";
	DIYUseSQL(str_order);
}
void CAdoSql::DIYInsertCowInfo(CString node,CString cow)
{
	CString str_o;
	str_o="if  not exists(select * from ��ţ��Ϣ where �ڵ��="+node+")";
	str_o=str_o+"INSERT INTO ��ţ��Ϣ (�ڵ��,��ţ�����) VALUES ('";
	str_o=str_o+node+"','";
	str_o=str_o+cow+"')";
	DIYUseSQL(str_o);
}
bool CAdoSql::DIYInsertCowData(CString node,CString time,CString strtime,CString data)
{
	CString time2;
	CString hour=strtime.Left(2);
	CString mint=strtime.Mid(3,2);
	CString sec=strtime.Right(2);
	int int_hour=_ttoi(hour);
	int int_mint=_ttoi(mint);
	int_mint=int_mint-5;
	if (int_mint<0)
	{
		int_mint=60+int_mint;
		int_hour--;
		if (int_hour<0)
		{
			int_hour=24+int_hour;
		}
	}
	CString strtime_H,strtime_M;
	strtime_H.Format("%d",int_hour);
	strtime_M.Format("%d",int_mint);
	if (strtime_M.GetLength()==1)
	{
		strtime_M="0"+strtime_M;
	}
	if (strtime_H.GetLength()==1)
	{
		strtime_H="0"+strtime_H;
	}
	time2=strtime_H+":"+strtime_M+":"+sec;
	//if not exists(SELECT �ɼ�����,�ɼ�ʱ�� FROM �½ڵ�0001 WHERE  �ɼ����� ='15/06/02' and �ɼ�ʱ�� > '23:55:07') INSERT INTO �½ڵ�0001(�ɼ�����,�ɼ�ʱ��,���) values ('2000/05/02','23:50:00','0')
	CString str_o;
	str_o="if not exists(SELECT �ɼ�����,�ɼ�ʱ�� FROM �½ڵ�"+node+" WHERE  �ɼ����� ='"+time+"' and �ɼ�ʱ�� > '"+time2+"') ";
	str_o=str_o+"INSERT INTO �½ڵ�"+node+"(�ɼ�����,�ɼ�ʱ��,���) VALUES ('";
	str_o=str_o+time+"','";
	str_o=str_o+strtime+"','";
	str_o=str_o+data+"')";
	if (DIYUseSQL(str_o))
	{
		return true;
	} 
	else
	{
		return false;
	}

}
void CAdoSql::DIYGetCowData(CString node)
{
	ListCowData.RemoveAll();
	ListCowDataTime.RemoveAll();
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=db_cows;Data Source=WJ-20140605XBQL";
		pConn->Open("","","",-1);
		CString str;
		str="SELECT  *  FROM �½ڵ�"+node+" order by '�ɼ�����'";
		pRst=pConn->Execute(_bstr_t(str),NULL,adCmdText);
		_variant_t   vNum;  
		_bstr_t      bstr;  
		while(!pRst->EndOfFile)
		{
			CString str="";
			vNum =pRst->GetCollect("���");
			bstr = vNum;          
			str = (LPCSTR)bstr;
			if (str.GetLength()>4)
			{
				pRst->MoveNext();
				continue;
			}
			ListCowData.AddTail(str);
			CString str2="";
			vNum =pRst->GetCollect("�ɼ�����");
			bstr = vNum;          
			str2 = (LPCSTR)bstr;
			CString str3="";
			vNum =pRst->GetCollect("�ɼ�ʱ��");
			bstr = vNum;          
			str3 = (LPCSTR)bstr;
			ListCowDataTime.AddTail((str2+" "+str3));
			pRst->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("��ȡ��ţ�������"+strMsg),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CAdoSql::DIYDeleteCowData(CString node)
{
	CString str;
	str="delete from ��ţ��Ϣ where �ڵ�� = "+node;
	DIYUseSQL(str);
}
bool CAdoSql::DIYUpdateCowInfo(CString node,CString cowName)
{
	CString str;
	str="UPDATE ��ţ��Ϣ SET ��ţ����� ="+cowName+" WHERE �ڵ�� = "+node;
	DIYUseSQL(str);
	return true;
}
void CAdoSql::DIYTnsertASA(CString id,CString date,CString time,CString data)
{
		 CDatabase db;
	     db.Open(NULL,FALSE,FALSE,"ODBC;DSN=mngl;UID=admin;PWD=123098789521");
		 CString str_o;
		 str_o="INSERT INTO hdljcjlb(jbqbh,jcrq,jcsj,hdl) VALUES ('";
		 str_o=str_o+id+"','";
		 str_o=str_o+date+"','";
		 str_o=str_o+time+"','";
		 str_o=str_o+data+"')";
		 db.ExecuteSQL(str_o);
		 db.Close();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CAdoSql::DIYGetASA(CString strOrder)
{
	CDatabase db;
	db.Open(NULL,FALSE,FALSE,"ODBC;DSN=mngl;UID=admin;PWD=123098789521");
	CRecordset rs( &db );
	rs.Open( CRecordset::forwardOnly, ("%s", strOrder));
	//short nFields = rs.GetODBCFieldCount();
	 		 while(!rs.IsEOF())
	 		{
	 						 
// 	 			CString id;
// 	 			rs.GetFieldValue("jbqbh", id); 
// 	 			AfxMessageBox(id);
// 				CString date;
// 				rs.GetFieldValue("jcrp", date); 
// 				AfxMessageBox(date);
// 				CString time;
// 				rs.GetFieldValue("jcsj", time); 
// 				AfxMessageBox(time);
				CString dta;
				rs.GetFieldValue("hdl", dta); 
				AfxMessageBox(dta);
	 			rs.MoveNext();
	 		}
	 rs.Close();
	db.Close();
}
CString CAdoSql::DIYTransfrom(char buf)
{
	char recvBufTemp[99];
	int j=0;
	char temp;
	temp=(buf & 0xF0)>>4;
	recvBufTemp[j]=(temp<=9)?temp+'0':(temp-10)+'A';
	j++;
	temp=(buf & 0x0F);
	recvBufTemp[j]=(temp<=9)?temp+'0':(temp-10)+'A';
	j++;
	recvBufTemp[j]='\0';
	return (CString)recvBufTemp;

}
void CAdoSql::DIYDelTable(CString num)
{
	CString str_order;
	str_order="DROP TABLE �ڵ�"+num;
	DIYUseSQL(str_order);

}
void CAdoSql::DIYTnsertCowMysql(CString id,CString cowID)
{
	try
	{
		CDatabase db;
		db.Open(NULL,FALSE,FALSE,"ODBC;DSN=sa;UID=whs;PWD=123789");
		CString str_o;
		str_o="INSERT INTO cowinfo(idcowInfo,OxId) VALUES ('";
		str_o=str_o+id+"','";
		str_o=str_o+cowID+"')";
		db.ExecuteSQL(str_o);
		db.Close();
	}
	catch(CDBException* m_pEx)
	{ 
		//::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)(m_pEx->m_strError),0);
		m_pEx->Delete();
	}	
}
void CAdoSql::DIYUpdateCowMysql(CString id,CString cowID)
{
	try
	{
		CDatabase db;
		db.Open(NULL,FALSE,FALSE,"ODBC;DSN=sa;UID=whs;PWD=123789");
		CString str_o;
		str_o="UPDATE cowinfo SET `OxId`='";
		str_o=str_o+cowID+"' WHERE `idcowInfo`='";
		str_o=str_o+id+"'";
		db.ExecuteSQL(str_o);
		db.Close();
	}
	catch(CDBException* m_pEx)
	{ 
		//::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)(m_pEx->m_strError),0);
		m_pEx->Delete();
	}	
}
void CAdoSql::DIYTnsertMysql(CString id,CString date,CString time,CString data)
{
	try
	{
		CDatabase db;
		db.Open(NULL,FALSE,FALSE,"ODBC;DSN=sa;UID=whs;PWD=123789");
		CString str_o;
		str_o="INSERT INTO yd_cows_all(id,date,time,data) VALUES ('";
		str_o=str_o+id+"','";
		str_o=str_o+date+"','";
		str_o=str_o+time+"','";
		str_o=str_o+data+"')";
		db.ExecuteSQL(str_o);
		db.Close();
	}
	catch(CDBException* m_pEx)
	{ 
		//::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)(m_pEx->m_strError),0);
		m_pEx->Delete();
	}	
}
void CAdoSql::DIYADOMysql(CString id,CString date,CString time,CString data)
{
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset)); 
		pConn->ConnectionString="Provider=MSDASQL.1;Persist Security Info=False;Data Source=sa";
		pConn->Open("","","",-1);
		CString str_o;
		str_o="INSERT INTO yd_cows_all(id,date,time,data) VALUES ('";
		str_o=str_o+id+"','";
		str_o=str_o+date+"','";
		str_o=str_o+time+"','";
		str_o=str_o+data+"')";

		pConn->Execute(_bstr_t(str_o),NULL,adCmdText);
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		//::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("���ݿⴴ������"+strMsg),0);
	}

}
void CAdoSql::DIYGetCowDataByDay(CString node,CString time)
{
	ListCowData.RemoveAll();
	ListCowDataTime.RemoveAll();
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset));
		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=db_cows;Data Source=WJ-20140605XBQL";
		pConn->Open("","","",-1);
		CString str;
		str="SELECT  *  FROM �½ڵ�"+node+" where �ɼ����� ='"+time+"' order by �ɼ�ʱ�� desc";
		pRst=pConn->Execute(_bstr_t(str),NULL,adCmdText);
		_variant_t   vNum;  
		_bstr_t      bstr;  
		while(!pRst->EndOfFile)
		{
			CString str="";
			vNum =pRst->GetCollect("���");
			bstr = vNum;          
			str = (LPCSTR)bstr;
			ListCowData.AddTail(str);
			CString str2="";
			vNum =pRst->GetCollect("�ɼ�ʱ��");
			bstr = vNum;          
			str2 = (LPCSTR)bstr;
			ListCowDataTime.AddTail(str2);
			pRst->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("��ȡ��ţ�������"+strMsg),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CAdoSql::DIYADOMysqlorder(CString id,CString date,CString time,CString data)
{
	CString time2;
	CString hour=time.Left(2);
	CString mint=time.Mid(3,2);
	CString sec=time.Right(2);
	int int_hour=_ttoi(hour);
	int int_mint=_ttoi(mint);
	int_mint=int_mint-3;
	if (int_mint<0)
	{
		int_mint=60+int_mint;
		int_hour--;
		if (int_hour<0)
		{
			int_hour=24+int_hour;
		}
	}
	CString strtime_H,strtime_M;
	strtime_H.Format("%d",int_hour);
	strtime_M.Format("%d",int_mint);
	if (strtime_M.GetLength()==1)
	{
		strtime_M="0"+strtime_M;
	}
	if (strtime_H.GetLength()==1)
	{
		strtime_H="0"+strtime_H;
	}
	time2=strtime_H+":"+strtime_M+":"+sec;
	try
	{
		CoInitialize(NULL);//com�����ʼ��  
		_ConnectionPtr pConn;//(__uuidof(Connection));
		_CommandPtr pComm;//(__uuidof(Command));;
		_RecordsetPtr pRst;//(__uuidof(Recordset));   
		pConn.CreateInstance(__uuidof(Connection));
		pComm.CreateInstance(__uuidof(Command));
		pRst.CreateInstance(__uuidof(Recordset)); 
		pConn->ConnectionString="Provider=MSDASQL.1;Persist Security Info=False;Data Source=sa";
		pConn->Open("","","",-1);
		CString str_o;
		str_o="INSERT INTO yd_cows(id,date,time,data) select '";
		str_o=str_o+id+"','";
		str_o=str_o+date+"','";
		str_o=str_o+time+"','";
		str_o=str_o+data+"'"+" FROM DUAL WHERE NOT EXISTS(SELECT id,date,time FROM yd_cows WHERE ";
		str_o=str_o+"id = '"+id+"' and date ='"+date+"' and time > '"+time2+"')";

		pConn->Execute(_bstr_t(str_o),NULL,adCmdText);
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		//::SendMessage((( (CFrameWnd * )AfxGetMainWnd() )->GetActiveFrame()->GetActiveView()->m_hWnd),WM_USERMESSAGE,(WPARAM)(LPCTSTR)("���ݿⴴ������"+strMsg),0);
	}
}
void CAdoSql::SaveLog(CString strText)
{

	CString strPath;
	GetCurrentDirectory(MAX_PATH,strPath.GetBuffer(MAX_PATH));
	strPath.ReleaseBuffer();
	strPath+="\\������־\\";
	CreateDirectory(strPath, NULL);
	CTime tCurTime = CTime::GetCurrentTime();//��ǰ����ʱ�䣻
	CString strTime;
	strTime = tCurTime.Format("%Y%m%d_%H%M%S");//��CTimeת��CString��
	strPath+="WebLog_NET";
	strPath+= strTime;
	strPath+=".txt";
	std::ofstream saveFile;
	saveFile.open(strPath);

	if (saveFile)
	{
		saveFile<<strText<<"\n";
	}
	else
	{
		//�ļ���ʧ�ܣ�
	}

	saveFile.close();

}