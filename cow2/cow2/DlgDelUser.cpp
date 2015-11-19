// DlgDelUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgDelUser.h"
#include "afxdialogex.h"
#include "AdoSql.h"
#include "Global.h"


// CDlgDelUser �Ի���

IMPLEMENT_DYNAMIC(CDlgDelUser, CDialogEx)

CDlgDelUser::CDlgDelUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDelUser::IDD, pParent)
{
}

CDlgDelUser::~CDlgDelUser()
{
}

void CDlgDelUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_User, m_combo);
	for (int i=0;i<50;i++)
	{
		if (str_UserName[i].IsEmpty())
		{
			//continue;
		}
		else
		{
			m_combo.AddString(str_UserName[i]);
		}

	}
}


BEGIN_MESSAGE_MAP(CDlgDelUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_DelUser, &CDlgDelUser::OnBnClickedButDeluser)
	ON_CBN_SELCHANGE(IDC_COMBO_User, &CDlgDelUser::OnCbnSelchangeComboUser)
END_MESSAGE_MAP()


// CDlgDelUser ��Ϣ�������


void CDlgDelUser::OnBnClickedButDeluser()
{
	CString str;
	GetDlgItemText(IDC_SEL_EDIT,str);
	if(str.IsEmpty())
	{
		AfxMessageBox("��ѡ��Ҫɾ�����û�");
	}
	else
	{
		CString str_DelSql;
	str_DelSql="DELETE FROM Users WHERE �û��� = '";
	str_DelSql=str_DelSql+str+"'";
	if(IDYES==AfxMessageBox("ȷ���޸�",MB_YESNO|MB_ICONQUESTION))    //�����Ի����ж��Ƿ�ɾ���ڵ�
	{
		for (int i=0;i<50;i++)
		{
			if (str_UserName[i]=str)
			{
				str_UserName[i]="";
				CAdoSql sql;
				sql.DIYUseSQL(str_DelSql);
				sql.DIYGetInfoOfUser();
				m_combo.DeleteString(nSel);
				SetDlgItemText(IDC_SEL_EDIT,"");
				break;
			}
		}
	}
	}
	
}


void CDlgDelUser::OnCbnSelchangeComboUser()
{
	CString strWeb;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combo.GetCurSel();   
	// ����ѡ����������ȡ�����ַ���   
	m_combo.GetLBText(nSel, strWeb);   
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
	SetDlgItemText(IDC_SEL_EDIT, strWeb);// TODO: �ڴ���ӿؼ�֪ͨ����������
}
