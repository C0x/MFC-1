#pragma once
#include "afxwin.h"


// CDlgDelUser �Ի���

class CDlgDelUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDelUser)

public:
	CDlgDelUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDelUser();

// �Ի�������
	enum { IDD = IDD_DLG_DelUser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButDeluser();
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeComboUser();
	int nSel; 
};
