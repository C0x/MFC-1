#pragma once
#include "afxwin.h"


// CDlgSetPort �Ի���

class CDlgSetPort : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetPort)

public:
	CDlgSetPort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetPort();

// �Ի�������
	enum { IDD = IDD_DLG2_SetPort };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButaddport();
	afx_msg void OnBnClickedButDelprot();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeCombo1();
	int nSel;
	afx_msg void OnBnClickedButchange();
};
