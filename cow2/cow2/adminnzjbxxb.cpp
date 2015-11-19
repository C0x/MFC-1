// adminnzjbxxb.h : Cadminnzjbxxb ���ʵ��



// Cadminnzjbxxb ʵ��

// ���������� 2015��3��16��, 19:55

#include "stdafx.h"
#include "adminnzjbxxb.h"
IMPLEMENT_DYNAMIC(Cadminnzjbxxb, CRecordset)

Cadminnzjbxxb::Cadminnzjbxxb(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nzbh = "";
	m_zb = 0;
	m_jbqbh = "";
	m_mnbh = "";
	m_fnbh = "";
	m_cszl = 0.0;
	m_rczl = 0.0;
	m_pz = "";
	m_tzms = "";
	m_pic1;
	m_pic2;
	m_pic3;
	m_pic4;
	m_pic5;
	m_bz = "";
	m_nFields = 17;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
// CString Cadminnzjbxxb::GetDefaultConnect()
// {
// //	return _T("DSN=mngl;UID=admin;PWD=123098789521;Start=D:\\mfc\x5de5\x4f5c\\asa\\\x65b0\x5efa\x6587\x4ef6\x5939\\dbeng\\dbeng8.exe -d -c8m;DatabaseFile=D:\\mfc\x5de5\x4f5c\\asa\\mngl.db;DatabaseName=mngl;EngineName=mngl;AutoStop=YES;Integrated=No;Debug=NO;DisableMultiRowFetch=NO;Compress=NO");
// }

CString Cadminnzjbxxb::GetDefaultSQL()
{
	return _T("[admin].[nzjbxxb]");
}

void Cadminnzjbxxb::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[nzbh]"), m_nzbh);
	RFX_Long(pFX, _T("[zb]"), m_zb);
	RFX_Text(pFX, _T("[jbqbh]"), m_jbqbh);
	RFX_Text(pFX, _T("[mnbh]"), m_mnbh);
	RFX_Text(pFX, _T("[fnbh]"), m_fnbh);
	RFX_Double(pFX, _T("[cszl]"), m_cszl);
	RFX_Double(pFX, _T("[rczl]"), m_rczl);
	RFX_Text(pFX, _T("[pz]"), m_pz);
	RFX_Text(pFX, _T("[tzms]"), m_tzms);
	RFX_LongBinary(pFX, _T("[pic1]"), m_pic1);
	RFX_LongBinary(pFX, _T("[pic2]"), m_pic2);
	RFX_LongBinary(pFX, _T("[pic3]"), m_pic3);
	RFX_LongBinary(pFX, _T("[pic4]"), m_pic4);
	RFX_LongBinary(pFX, _T("[pic5]"), m_pic5);
	RFX_Text(pFX, _T("[bz]"), m_bz);

}
/////////////////////////////////////////////////////////////////////////////
// Cadminnzjbxxb ���

#ifdef _DEBUG
void Cadminnzjbxxb::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cadminnzjbxxb::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


