#pragma once


// CDlgInData �Ի���

class CDlgInData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInData)

public:
	CDlgInData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInData();

// �Ի�������
	enum { IDD = IDD_DLG3InData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
