#pragma once


// CDlgAddNewPort �Ի���

class CDlgAddNewPort : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddNewPort)

public:
	CDlgAddNewPort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddNewPort();

// �Ի�������
	enum { IDD = IDD_DLG2NewPort };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButaddport();
};
