#pragma once
#include "afxwin.h"


// CDlgOutData �Ի���

class CDlgOutData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOutData)

public:
	CDlgOutData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOutData();

// �Ի�������
	enum { IDD = IDD_DLG3OutData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CString strTable;//ѡ������ݱ���
public:
	afx_msg void OnBnClickedButOutdata2();
	afx_msg void OnBnClickedButShowtable();
	CListBox m_mylist;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButout();
};
