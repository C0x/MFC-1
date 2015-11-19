// DlgAllUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgAllUser.h"
#include "afxdialogex.h"
#include "AdoSql.h"
#include "Global.h"


// CDlgAllUser �Ի���

IMPLEMENT_DYNAMIC(CDlgAllUser, CDialogEx)

CDlgAllUser::CDlgAllUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAllUser::IDD, pParent)
{

}

CDlgAllUser::~CDlgAllUser()
{
}

void CDlgAllUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_User, m_UserList);
	CRect rect;   
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_UserList.GetClientRect(&rect);  
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_UserList.SetExtendedStyle(m_UserList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
	
	m_UserList.InsertColumn(0, _T("�û���"), LVCFMT_CENTER, rect.Width()/2, 0);   
	m_UserList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width()/2, 1);
	for (int i=0;i<50;i++)
	{  
		if (str_UserName[i].IsEmpty())
		{
		}
		else
		{
		m_UserList.InsertItem(i, (str_UserName[i]));   
		m_UserList.SetItemText(i, 1, (str_Pwd[i])); 
		}
	}
}


BEGIN_MESSAGE_MAP(CDlgAllUser, CDialogEx)
END_MESSAGE_MAP()


// CDlgAllUser ��Ϣ�������
