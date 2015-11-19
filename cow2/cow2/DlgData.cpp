// DlgData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgData.h"
#include "afxdialogex.h"
#include "Global.h"
#include "AdoSql.h"


// CDlgData �Ի���

IMPLEMENT_DYNAMIC(CDlgData, CDialogEx)

CDlgData::CDlgData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgData::IDD, pParent)
{

}

CDlgData::~CDlgData()
{
}

void CDlgData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	for (int i=0;i<20;i++)
	{
		if (node[i].IsEmpty())
		{
			//continue;
		}
		else
		{
			m_combo.AddString(node[i]);
		}
	}
	nSel=-1;
	DDX_Control(pDX, IDC_LIST_User, m_CowDataList);
	CRect rect;   
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_CowDataList.GetClientRect(&rect);  
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_CowDataList.SetExtendedStyle(m_CowDataList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 

	m_CowDataList.InsertColumn(0, _T("����ʱ��"), LVCFMT_CENTER, rect.Width()/2, 0);   
	m_CowDataList.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect.Width()/2, 1);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dateCtrl);
}


BEGIN_MESSAGE_MAP(CDlgData, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgData::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUT_search, &CDlgData::OnBnClickedButsearch)
	ON_BN_CLICKED(IDC_BUT_del, &CDlgData::OnBnClickedButdel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgData::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgData ��Ϣ�������


void CDlgData::OnCbnSelchangeCombo1()
{
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combo.GetCurSel();   
	// ����ѡ����������ȡ�����ַ���   
	m_combo.GetLBText(nSel, strNode);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
	SetDlgItemText(IDC_EDIT_Cow,cowName[nSel]);// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgData::OnBnClickedButsearch()
{
	CAdoSql sql;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_day);
	int state = pBtn->GetCheck();
	if (state==1)
	{
		CTime m_date;
		m_dateCtrl.GetTime(m_date); 
		CString strdata=m_date.Format("%Y/%m/%d");
		sql.DIYGetCowDataByDay(strNode,strdata.Right(8));
	} 
	else
	{
		sql.DIYGetCowData(strNode);
	}
	
	POSITION rPos1,rPos2;
	rPos1 = ListCowData.GetHeadPosition();
	rPos2 = ListCowDataTime.GetHeadPosition();
	if (nSel==-1)
	{
		AfxMessageBox("��ѡ��ڵ�");
	} 
	else
	{
		m_CowDataList.DeleteAllItems();
		int i=0;
		while (rPos1 != NULL)
		{
			m_CowDataList.InsertItem(i, (ListCowDataTime.GetNext(rPos2)));   
			m_CowDataList.SetItemText(i, 1, (ListCowData.GetNext(rPos1))); 
			i++;
		}
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgData::OnBnClickedButdel()
{
	CAdoSql sql;
	sql.DIYDelTable(strNode);// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgData::OnBnClickedButton1()
{
	if ( m_CowDataList.GetItemCount()<= 0 )
	{
		AfxMessageBox("�б���û�м�¼��Ҫ���棡");
		return;
	}
	//�����Ϊ�Ի��� ����Ҫ���� #include <Afxdlgs.h>
	CFileDialog dlg( FALSE, 
		"xls", 
		"�ڵ�", 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Excel �ļ�(*.xls)|*.xls||");
	dlg.m_ofn.lpstrTitle = "�ļ��б����Ϊ";

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	//����ļ�·����
	strFilePath = dlg.GetPathName();
	//�ж��ļ��Ƿ��Ѿ����ڣ�������ɾ���ؽ�
	DWORD dwRe = GetFileAttributes(strFilePath);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strFilePath);
	}

	CDatabase database;//���ݿ����Ҫ����ͷ�ļ� #include <afxdb.h>
	CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel����
	CString sSql,strInsert;

	TRY
	{
		// �������д�ȡ���ַ���
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, strFilePath, strFilePath);

		// �������ݿ� (��Excel����ļ�)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			//����б��������
			int iColumnNum,iRowCount;
			LVCOLUMN lvCol;
			CString strColName; //���ڱ����б�������
			int i,j; //�С���ѭ������

			iColumnNum = m_CowDataList.GetHeaderCtrl()->GetItemCount();
			iRowCount = m_CowDataList.GetItemCount();

			sSql = " CREATE TABLE DSO_DX ( ";
			strInsert = " INSERT INTO DSO_DX ( " ;
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for( i=0 ; i< iColumnNum ; i++ )
			{
				if ( !(m_CowDataList.GetColumn(i,&lvCol)) )
					return;
				if ( i<iColumnNum-1 )
				{
					sSql = sSql + lvCol.pszText + " TEXT , ";
					strInsert = strInsert + lvCol.pszText + " , ";
				}
				else
				{
					sSql = sSql + lvCol.pszText + " TEXT ) ";
					strInsert = strInsert + lvCol.pszText + " )  VALUES ( ";
				}
			}
			//����Excel����ļ�
			database.ExecuteSQL(sSql);

			//ѭ����ȡ��¼�����뵽EXCEL��
			sSql = strInsert;
			char chTemp[33];
			for ( j=0 ; j<iRowCount ; j++ )
			{
				memset(chTemp,0,33);
				for ( i=0 ; i<iColumnNum ; i++ )
				{
					m_CowDataList.GetItemText(j,i,chTemp,33);
					if ( i < (iColumnNum-1) )
					{
						sSql = sSql + "'" + chTemp + "' , ";
					}
					else
					{
						sSql = sSql + "'" + chTemp + "' ) ";
					}
				}
				//����¼���뵽�����
				database.ExecuteSQL(sSql);
				sSql = strInsert; 
			}
		}     

		// �ر�Excel����ļ�
		database.Close();

		AfxMessageBox("�����ѯ���ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;// TODO: �ڴ���ӿؼ�֪ͨ����������
}
