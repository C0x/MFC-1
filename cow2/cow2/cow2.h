
// cow2.h : cow2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "AdoSql.h"



typedef struct MYPARMS
{
	SOCKET sock;
	char* pChar;
	CString strPar;
	int	nPar;
} MyParams;
// Ccow2App:
// �йش����ʵ�֣������ cow2.cpp
//

class Ccow2App : public CWinAppEx
{
public:
	Ccow2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
    MyParams* m_Params;
	CAdoSql* m_sql;
};

extern Ccow2App theApp;
