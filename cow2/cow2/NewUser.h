#pragma once


// CNewUser �Ի���

class CNewUser : public CDialogEx
{
	DECLARE_DYNAMIC(CNewUser)

public:
	CNewUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewUser();

// �Ի�������
	enum { IDD = IDD_DLG_NewUser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButAdduser();
};
