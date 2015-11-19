// DlgOutData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgOutData.h"
#include "afxdialogex.h"
#include "DlgOutData2.h"
#include "AdoSql.h"


// CDlgOutData �Ի���

IMPLEMENT_DYNAMIC(CDlgOutData, CDialogEx)

CDlgOutData::CDlgOutData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOutData::IDD, pParent)
{

}

CDlgOutData::~CDlgOutData()
{
}

void CDlgOutData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_mylist);
}


BEGIN_MESSAGE_MAP(CDlgOutData, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_OutData2, &CDlgOutData::OnBnClickedButOutdata2)
	ON_BN_CLICKED(IDC_BUT_ShowTable, &CDlgOutData::OnBnClickedButShowtable)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgOutData::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUT_out, &CDlgOutData::OnBnClickedButout)
END_MESSAGE_MAP()


// CDlgOutData ��Ϣ�������


void CDlgOutData::OnBnClickedButOutdata2()
{
	CDlgOutData2 dlg;// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(dlg.DoModal()==IDOK)
		Invalidate();
}


void CDlgOutData::OnBnClickedButShowtable()
{
// 	int a = m_mylist.GetCount();//������
// 
// 	for(int i=0;i<a;i++)
// 	{
// 		m_mylist.DeleteString(i);//ɾ��ListBox ��ǰ��
// 
// 	}
// 	try
// 	{
// 		CoInitialize(NULL);//com�����ʼ��  
// 		_ConnectionPtr pConn;//(__uuidof(Connection));
// 		_CommandPtr pComm;//(__uuidof(Command));;
// 		_RecordsetPtr pRst;//(__uuidof(Recordset));   
// 		pConn.CreateInstance(__uuidof(Connection));
// 		pComm.CreateInstance(__uuidof(Command));
// 		pRst.CreateInstance(__uuidof(Recordset));
// 		pConn->ConnectionString="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=master;Data Source=WJ-20140605XBQL";
// 		pConn->Open("","","",-1);
// 		pRst=pConn->Execute("SELECT Name FROM db_Node..SysObjects Where XType='U' ORDER BY Name",NULL,adCmdText);
// 		_variant_t   vNum;  
// 		_bstr_t      bstr;  
// 
// 		while(!pRst->EndOfFile)
// 		{
// 			CString str="";
// 			vNum =pRst->GetCollect("Node");
// 			bstr = vNum;          
// 			str = (LPCSTR)bstr;
// 			m_mylist.AddString(_T(str));// �˴��������
// 			pRst->MoveNext();
// 		}
// 	}
// 	catch (_com_error& e)
// 	{
// 		CString strMsg;
// 		strMsg.Format(_T("����������%s\n������Ϣ%s"), 
// 			(LPCTSTR)e.Description(),
// 			(LPCTSTR)e.ErrorMessage());
// 		AfxMessageBox("���ݿ��������"+strMsg);
// 	}// TODO: �ڴ���ӿؼ�֪ͨ����������// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	//strTable="1";
}


void CDlgOutData::OnLbnSelchangeList1()
{
	int nCurSel;
	nCurSel = m_mylist.GetCurSel();           // ��ȡ��ǰѡ���б���   
	m_mylist.GetText(nCurSel, strTable);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgOutData::OnBnClickedButout()
{
	CString fileName,str_time,str;
	CTime tm=CTime::GetCurrentTime();//��ȡϵͳʱ��
	str_time=tm.Format("ʱ��%Hʱ%M��%m��%d��");
	GetDlgItemText(IDC_EDIT_Node,str);
	int i=str.GetLength();
	if (i==1)
	{
		str="�ڵ�000"+str;
	} 
	else
	{
		if (i==2)
		{
			str="�ڵ�00"+str;
		} 
		else
		{
			if (i==3)
			{
				str="�ڵ�0"+str;
			} 
		}
	}
	if (str.IsEmpty())
	{
		AfxMessageBox("��ѡ�����ɵ����ݱ�");
	}
	else
	{
		CString str_order;
		CFileDialog  Dlg(FALSE,NULL,(str+str_time),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"excel�ļ�(*.xls)");
		if(Dlg.DoModal() == IDOK)
		{
			fileName = Dlg.GetPathName();
			fileName=fileName+".xls";
			str_order="exec sp_configure 'show advanced options', 1   RECONFIGURE   exec sp_configure 'Web Assistant Procedures', 1   RECONFIGURE  EXEC sp_makewebtask   @outputfile = '";
			str_order=str_order+fileName+"',   @query = 'Select  * from db_cows..";
			str_order=str_order+str+"',   @colheaders =1,   @FixedFont=0,@lastupdated=0,@resultstitle='�ڵ�����'";
			CAdoSql sql;
			sql.DIYUseSQL(str_order);
			AfxMessageBox("�����ɹ�");
		}
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
