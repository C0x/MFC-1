#pragma once
#include "afxwin.h"


// CDlgSetGate �Ի���

class CDlgSetGate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetGate)

public:
	CDlgSetGate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetGate();

// �Ի�������
	enum { IDD = IDD_DLG2_SetGate };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButStartgprs();
	void editAppend(CString strData);
	CEdit m_ShowError;
	afx_msg void OnBnClickedButingprs();
};
