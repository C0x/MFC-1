#pragma once


// CBeginDlg �Ի���

class CBeginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBeginDlg)

public:
	CBeginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBeginDlg();

// �Ի�������
	enum { IDD = IDD_DLG_Begin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	static void ShowSplashScreen(CWnd* pParentWnd);
	static CBeginDlg*c_BeginDlg;
	afx_msg void OnBnClickedButQuit();
	afx_msg void OnCancel();
	CWnd* m_F;
	afx_msg void OnBnClickedButLogin();
};
