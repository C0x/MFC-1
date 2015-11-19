#pragma once
#include "afxwin.h"
#include "tchart1.h"


// CDlgDataView �Ի���

class CDlgDataView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDataView)

public:
	CDlgDataView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDataView();

// �Ի�������
	enum { IDD = IDD_DLG3DataView };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButsearch();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CTchart1 m_TeeChart;
	int m_Radio0;
	CString strNode;
};
