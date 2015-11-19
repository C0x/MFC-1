// DlgSetServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgSetServer.h"
#include "afxdialogex.h"
#include "Global.h"


// CDlgSetServer �Ի���

IMPLEMENT_DYNAMIC(CDlgSetServer, CDialogEx)

CDlgSetServer::CDlgSetServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetServer::IDD, pParent)
{

}

CDlgSetServer::~CDlgSetServer()
{
}

void CDlgSetServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddr);
	DDX_Control(pDX, IDC_COMBO1, m_combo_Com);
	DDX_Control(pDX, IDC_COMBO2, m_combo_PTL);
	GetCom();
	m_combo_PTL.AddString("1200");
	m_combo_PTL.AddString("2400");
	m_combo_PTL.AddString("4800");
	m_combo_PTL.AddString("9600");
	m_combo_PTL.AddString("115200");
	m_combo_PTL.AddString("128000");
}


BEGIN_MESSAGE_MAP(CDlgSetServer, CDialogEx)
	ON_BN_CLICKED(IDC_BUT_LanSet, &CDlgSetServer::OnBnClickedButLanset)
	ON_BN_CLICKED(IDC_BUT_Rs485, &CDlgSetServer::OnBnClickedButRs485)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgSetServer::OnCbnSelchangeComboCom)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgSetServer::OnCbnSelchangeComboPtl)
END_MESSAGE_MAP()


// CDlgSetServer ��Ϣ�������


void CDlgSetServer::OnBnClickedButLanset()
{
	unsigned   char   *pIP; 
	DWORD   dwIP; 
	m_ipAddr.GetAddress(dwIP); 
	pIP   =   (unsigned   char*)&dwIP; 
	str_Ip.Format( "%u.%u.%u.%u ",*(pIP+3),   *(pIP+2),   *(pIP+1),   *pIP);
	GetDlgItemText(IDC_EDIT_ServerPort,str_Port);// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgSetServer::OnBnClickedButRs485()
{
	if (Com.IsEmpty() || PTY.IsEmpty())
	{
		AfxMessageBox("�����ô���");
	} 
	else
	{
		AfxMessageBox("���ô������óɹ�");
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
BOOL CDlgSetServer::GetCom()
{
	long lReg;  
	HKEY hKey;  
	DWORD MaxValueLength;  
	DWORD dwValueNumber;  

	lReg=RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm",  
		NULL, KEY_READ, &hKey);

	if(lReg!=ERROR_SUCCESS) //�ɹ�ʱ����ERROR_SUCCESS��
	{  
		MessageBox(TEXT("û�����Ӵ���!\n"));  
		return FALSE;
	}  

	lReg=RegQueryInfoKey(hKey,  NULL,  	NULL,  NULL,  NULL,NULL, NULL, 
		&dwValueNumber, &MaxValueLength, 	NULL, NULL,  NULL);  

	if(lReg!=ERROR_SUCCESS) //û�гɹ�
	{  
		MessageBox(TEXT("Getting Info Error!\n"));  
		return FALSE;
	}  

	TCHAR *pValueName, *pCOMNumber;  
	DWORD cchValueName,dwValueSize=10;  

	for(int i=0; i < dwValueNumber; i++)  
	{  
		cchValueName=MaxValueLength+1;  
		dwValueSize=10;  
		pValueName=(TCHAR*)VirtualAlloc(NULL,cchValueName,MEM_COMMIT,PAGE_READWRITE);  
		lReg=RegEnumValue(hKey, i,  pValueName,  
			&cchValueName, 	NULL, NULL, 	NULL, NULL);  

		if((lReg!=ERROR_SUCCESS)&&(lReg!=ERROR_NO_MORE_ITEMS))  
		{  
			MessageBox(TEXT("Enum Registry Error or No More Items!\n"));
			return FALSE;
		}  

		pCOMNumber=(TCHAR*)VirtualAlloc(NULL,6,MEM_COMMIT,PAGE_READWRITE);  
		lReg=RegQueryValueEx(hKey,  pValueName, NULL,  
			NULL, (LPBYTE)pCOMNumber, &dwValueSize);  

		if(lReg!=ERROR_SUCCESS)  
		{  
			MessageBox(TEXT("Can not get the name of the port"));
			return FALSE;
		}  

		CString str(pCOMNumber);
		m_combo_Com.AddString(str); //�ѻ�ȡ��ֵ���뵽ComBox�ؼ���

		VirtualFree(pValueName,0,MEM_RELEASE);  
		VirtualFree(pCOMNumber,0,MEM_RELEASE);  
	}  

	return TRUE ;
}


void CDlgSetServer::OnCbnSelchangeComboCom()
{
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combo_Com.GetCurSel();   
	// ����ѡ����������ȡ�����ַ���   
	m_combo_Com.GetLBText(nSel, Com);
}


void CDlgSetServer::OnCbnSelchangeComboPtl()
{
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combo_PTL.GetCurSel();   
	// ����ѡ����������ȡ�����ַ���   
	m_combo_PTL.GetLBText(nSel, PTY);// TODO: �ڴ���ӿؼ�֪ͨ����������
}
