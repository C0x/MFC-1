#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CDlgData �Ի���

class CDlgData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgData)

public:
	CDlgData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgData();

// �Ի�������
	enum { IDD = IDD_DLG3Date };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	int nSel;
public:
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButsearch();
	CListCtrl m_CowDataList;
	CString strNode;
	afx_msg void OnBnClickedButdel();
	CDateTimeCtrl m_dateCtrl;
	afx_msg void OnBnClickedButton1();
};
