// DlgDataView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cow2.h"
#include "DlgDataView.h"
#include "afxdialogex.h"
#include "Global.h"
#include "CSeries.h" 
#include "CAxis.h"
#include "CAxes.h"
#include "CLegend.h"
#include "AdoSql.h"


// CDlgDataView �Ի���

IMPLEMENT_DYNAMIC(CDlgDataView, CDialogEx)

CDlgDataView::CDlgDataView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDataView::IDD, pParent)
	, m_Radio0(0)
{

}

CDlgDataView::~CDlgDataView()
{
}

void CDlgDataView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);

	for (int i=0;i<999;i++)
	{
		if (node[i].IsEmpty())
		{
			//continue;
		}
		else
		{
			m_combo.AddString(node[i]);
		}

	}
	m_Radio0=0;
	DDX_Control(pDX, IDC_TCHART1, m_TeeChart);
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
}


BEGIN_MESSAGE_MAP(CDlgDataView, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgDataView::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUT_search, &CDlgDataView::OnBnClickedButsearch)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgDataView::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgDataView::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CDlgDataView ��Ϣ�������


void CDlgDataView::OnCbnSelchangeCombo1()
{
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_combo.GetCurSel();   
	// ����ѡ����������ȡ�����ַ���   
	m_combo.GetLBText(nSel, strNode);   
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
	SetDlgItemText(IDC_EDIT_Cow,cowName[nSel]);
}


void CDlgDataView::OnBnClickedButsearch()
{
	
	CAdoSql sql;
	sql.DIYGetCowData(strNode);
	POSITION rPos1,rPos2;
	rPos1 = ListCowData.GetHeadPosition();
	rPos2 = ListCowDataTime.GetHeadPosition();
	if(m_Radio0==0)
	{
	CSeries barSeries = (CSeries)m_TeeChart.Series(1);
	barSeries.Clear();
    CSeries lineSeries = (CSeries)m_TeeChart.Series(0);
	lineSeries.Clear();
	int i=0;
	while (rPos1 != NULL)
		{
			lineSeries.AddXY(i,_ttoi(ListCowData.GetNext(rPos1)),ListCowDataTime.GetNext(rPos2),0);
			i++;
		}
	}
	if(m_Radio0==1)
	{
		CSeries barSeries = (CSeries)m_TeeChart.Series(1);
		barSeries.Clear();
		CSeries lineSeries = (CSeries)m_TeeChart.Series(0);
		lineSeries.Clear();
		int i=0;
		while (rPos1 != NULL)
		{
			barSeries.AddXY(i,_ttoi(ListCowData.GetNext(rPos1)),ListCowDataTime.GetNext(rPos2),0);
			i++;
		}
	}
}




void CDlgDataView::OnBnClickedRadio1()
{
	m_Radio0=0;// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgDataView::OnBnClickedRadio2()
{
	m_Radio0=1;// TODO: �ڴ���ӿؼ�֪ͨ����������
}
