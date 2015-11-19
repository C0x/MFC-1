// DLGpwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DLGpwd.h"
#include "afxdialogex.h"
#include "AdoSql.h"
#include "Global.h"


// CDLGpwd �Ի���

IMPLEMENT_DYNAMIC(CDLGpwd, CDialogEx)

CDLGpwd::CDLGpwd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGpwd::IDD, pParent)
{

}

CDLGpwd::~CDLGpwd()
{
}

void CDLGpwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDLGpwd, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_ChangePwd, &CDLGpwd::OnBnClickedButChangepwd)
END_MESSAGE_MAP()


// CDLGpwd ��Ϣ�������


void CDLGpwd::OnBnClickedButChangepwd()
{
	CString str_User,str_OldPwd,str_NewPwd,str_NewPwd2;
	int num=0;
	GetDlgItemText(IDC_EDIT_User,str_User);
	GetDlgItemText(IDC_EDIT_OldPwd,str_OldPwd);
	GetDlgItemText(IDC_EDIT_NewPwd,str_NewPwd);
	GetDlgItemText(IDC_EDIT_NewPwd2,str_NewPwd2);
	for (int i=0;i<50;i++)
	{
		if (str_User==str_UserName[i]&&str_OldPwd==str_Pwd[i])
		{
			if (str_NewPwd==str_NewPwd2)
			{
				CAdoSql sql;
				sql.DIYInsertName(str_User,str_NewPwd);
				sql.DIYGetInfoOfUser();
				num--;
				AfxMessageBox("�޸ĳɹ�");
			}
			else
			{
				AfxMessageBox("�����������벻һ��");
			}
		}

		num++;
	}
	if (num==50)
	{
				AfxMessageBox("�û����������������������");
	}
}
