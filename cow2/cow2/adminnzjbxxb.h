// adminnzjbxxb.h : Cadminnzjbxxb ������

#pragma once

// ���������� 2015��3��16��, 19:55

class Cadminnzjbxxb : public CRecordset
{
public:
	Cadminnzjbxxb(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cadminnzjbxxb)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA	m_nzbh;
	// unsupported	m_birth;
	long	m_zb;
	CStringA	m_jbqbh;
	CStringA	m_mnbh;
	CStringA	m_fnbh;
	double	m_cszl;
	double	m_rczl;
	// unsupported	m_rcrq;
	CStringA	m_pz;
	CStringA	m_tzms;
	CLongBinary	m_pic1;
	CLongBinary	m_pic2;
	CLongBinary	m_pic3;
	CLongBinary	m_pic4;
	CLongBinary	m_pic5;
	CStringA	m_bz;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


