#pragma once


// CDlgOutData2 �Ի���

class CDlgOutData2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOutData2)

public:
	CDlgOutData2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOutData2();

// �Ի�������
	enum { IDD = IDD_DLG3OutData2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
