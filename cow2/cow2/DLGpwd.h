#pragma once


// CDLGpwd �Ի���

class CDLGpwd : public CDialogEx
{
	DECLARE_DYNAMIC(CDLGpwd)

public:
	CDLGpwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLGpwd();
	_ConnectionPtr pConn;
	_CommandPtr pComm;
	_RecordsetPtr pRst;

// �Ի�������
	enum { IDD = IDD_DLG_pwd };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButChangepwd();
};
