#pragma once
#include "explorer1.h"


// CDlgWeb �Ի���

class CDlgWeb : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWeb)

public:
	CDlgWeb(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWeb();

// �Ի�������
	enum { IDD = IDD_DLG_Web };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_web;
};
