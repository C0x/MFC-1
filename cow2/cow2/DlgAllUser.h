#pragma once
#include "afxcmn.h"


// CDlgAllUser �Ի���

class CDlgAllUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAllUser)

public:
	CDlgAllUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAllUser();

// �Ի�������
	enum { IDD = IDD_DLG_AllUser };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_UserList;
};
