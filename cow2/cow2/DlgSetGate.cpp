// DlgSetGate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgSetGate.h"
#include "afxdialogex.h"


// CDlgSetGate �Ի���

IMPLEMENT_DYNAMIC(CDlgSetGate, CDialogEx)

CDlgSetGate::CDlgSetGate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetGate::IDD, pParent)
{

}

CDlgSetGate::~CDlgSetGate()
{
}

void CDlgSetGate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Show, m_ShowError);
}


BEGIN_MESSAGE_MAP(CDlgSetGate, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_StartGprs, &CDlgSetGate::OnBnClickedButStartgprs)
	ON_BN_CLICKED(IDC_BUT_inGprs, &CDlgSetGate::OnBnClickedButingprs)
END_MESSAGE_MAP()


// CDlgSetGate ��Ϣ�������


void CDlgSetGate::editAppend(CString strData)
{
		CString str,str_time;
		CTime tm=CTime::GetCurrentTime();//��ȡϵͳʱ��
		str_time=tm.Format("%H:%M:%S %m/%d");
		m_ShowError.SetSel(-1);
		m_ShowError.ReplaceSel(strData+" "+str_time+"\r\n");
		/*GetDlgItemText(IDC_EDIT_State,str); //IDC_EDIT�ǿؼ���ID
		str+=strData;
		str+=str_TableName+"\r\n";
		SetDlgItemText(IDC_EDIT_State,str);*/

}

void CDlgSetGate::OnBnClickedButStartgprs()
{
	editAppend("��ʼGPRS����ģʽ�����ж�");// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgSetGate::OnBnClickedButingprs()
{
	editAppend("����Gprs����");// TODO: �ڴ���ӿؼ�֪ͨ����������
}
