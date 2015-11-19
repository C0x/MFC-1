#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgSetServer �Ի���

class CDlgSetServer : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetServer)

public:
	CDlgSetServer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetServer();

// �Ի�������
	enum { IDD = IDD_DLG2_SetSevers };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButLanset();
	CIPAddressCtrl m_ipAddr;
	CComboBox m_combo_Com;
	CComboBox m_combo_PTL;
	afx_msg void OnBnClickedButRs485();
	BOOL GetCom();
	afx_msg void OnCbnSelchangeComboCom();
	afx_msg void OnCbnSelchangeComboPtl();
};
