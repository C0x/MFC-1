
// cow2View.cpp : Ccow2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cow2.h"
#endif

#include "cow2Doc.h"
#include "cow2View.h"
#include "DLGpwd.h"
#include "DlgAllUser.h"
#include "DlgData.h"
#include "DlgDataView.h"
#include "DlgDelUser.h"
#include "DlgInData.h"
#include "DlgOutData.h"
#include "DLGpwd.h"
#include "DlgSetGate.h"
#include "DlgSetPort.h"
#include "NewUser.h"
#include "AdoSql.h"
#include "Global.h"
#include "CSeries.h" 
#include "CAxis.h"
#include "CAxes.h"
#include "CLegend.h"
#include "CAxisTitle.h"
#include "CTitles.h"
#include "CPanel.h"
#include "CTChart.h"
#include "CTeeFont.h"
#include <algorithm>
#include "DlgWeb.h"
#include "SplitStr.h"

#include "DlgSetServer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern UINT ReadThreadFunc(LPVOID lpParameter);//����ȫ�ֺ���������
#define WM_SOCKETIO_MSG WM_USER+103//������ִ����ͻ��˵Ķ�д������Ϣ
// Ccow2View

IMPLEMENT_DYNCREATE(Ccow2View, CFormView)

	BEGIN_MESSAGE_MAP(Ccow2View, CFormView)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_MESSAGE(ACCEPT_EVENT,OnEvent)
		ON_BN_CLICKED(IDC_BUTTON1, &Ccow2View::OnBnClickedButton1)
		ON_COMMAND(ID_pwd, &Ccow2View::Onpwd)
		ON_COMMAND(ID_NewUser, &Ccow2View::OnNewuser)
		ON_COMMAND(ID_DelUser, &Ccow2View::OnDeluser)
		ON_COMMAND(ID_AllUser, &Ccow2View::OnAlluser)
		ON_COMMAND(ID_SetServer, &Ccow2View::OnSetserver)
		ON_COMMAND(ID_SetGste, &Ccow2View::OnSetgste)
		ON_COMMAND(ID_SetPort, &Ccow2View::OnSetport)
		ON_COMMAND(ID_Data, &Ccow2View::OnData)
		ON_COMMAND(ID_DataView, &Ccow2View::OnDataview)
		ON_COMMAND(ID_OutData, &Ccow2View::OnOutdata)
		ON_COMMAND(ID_InData, &Ccow2View::OnIndata)
		ON_COMMAND(ID_32775, &Ccow2View::On32775)
		ON_BN_CLICKED(IDC_BUT_SocketClose, &Ccow2View::OnBnClickedButSocketclose)
		ON_WM_TIMER()
		ON_BN_CLICKED(IDC_BUT_OpenCom, &Ccow2View::OnBnClickedButOpencom)
		ON_BN_CLICKED(IDC_BUT_CloseCom, &Ccow2View::OnBnClickedButClosecom)
		ON_MESSAGE(WM_USERMESSAGE,ReceiveMessage)
		//ON_COMMAND(ID_32801, &Ccow2View::On32801)
		ON_BN_CLICKED(IDC_BTN_ReadHistory, &Ccow2View::OnBnClickedBtnReadhistory)
		ON_BN_CLICKED(IDC_BUT_StartGprs, &Ccow2View::OnBnClickedButStartgprs)
		ON_BN_CLICKED(IDC_BUT_StopGprs, &Ccow2View::OnBnClickedButStopgprs)
		ON_BN_CLICKED(IDC_BUT_inGprs, &Ccow2View::OnBnClickedButingprs)
		ON_BN_CLICKED(IDC_BUT_outGprs, &Ccow2View::OnBnClickedButoutgprs)
		ON_BN_CLICKED(IDC_BUT_SetGprs, &Ccow2View::OnBnClickedButSetgprs)
		ON_BN_CLICKED(IDC_BUT_readGprsIp, &Ccow2View::OnBnClickedButreadgprsip)
		ON_BN_CLICKED(IDC_BUT_readGprsPort, &Ccow2View::OnBnClickedButreadgprsport)
		ON_BN_CLICKED(IDC_BUT_setGprsIp, &Ccow2View::OnBnClickedButsetgprsip)
		ON_BN_CLICKED(IDC_BUT_setGprsPort, &Ccow2View::OnBnClickedButsetgprsport)
		ON_BN_CLICKED(IDC_BUT_SaveGprs, &Ccow2View::OnBnClickedButSavegprs)
		ON_MESSAGE(WM_SOCKETIO_MSG,OnSocketIOMsg)
	END_MESSAGE_MAP()

	// Ccow2View ����/����

	Ccow2View::Ccow2View()
		: CFormView(Ccow2View::IDD)
		, m_edit(_T(""))
		, m_GprsIp(_T(""))
		, m_GprsPort(_T(""))
	{
		// TODO: �ڴ˴���ӹ������

	}

	Ccow2View::~Ccow2View()
	{
	}

	void Ccow2View::DoDataExchange(CDataExchange* pDX)
	{
		CFormView::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_EDIT_ShowError, m_ShowError);
		DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
		//GetDlgItem(IDC_BUT_OpenCom)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUT_CloseCom)->EnableWindow(FALSE);
		CAdoSql sql;
		sql.DIYCreatDateBase();
		sql.DIYCreatTable();
		// 	sql.DIYInsertName("admin","141516");
		// 	sql.DIYGetInfoOfUser();
		sql.DIYCrestCowInfoTable();
		sql.DIYGetCowInfo();

		DDX_Text(pDX, IDC_EDIT_order, m_edit);
		DDX_Text(pDX, IDC_EDIT_GprsPort2, m_GprsIp);
		DDX_Text(pDX, IDC_EDIT_GprsPort, m_GprsPort);
		SetDlgItemText(IDC_EDIT_order,"AT+");
	}

	BOOL Ccow2View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ
		// 	HANDLE m_hMutex = ::CreateMutex(NULL,TRUE,"��ţ������߼��ϵͳ");
		// 	if (GetLastError() == ERROR_ALREADY_EXISTS)
		// 	{
		// 		AfxMessageBox("�����Ѿ��������У������ظ�������");//�����Ի���ȷ�ϲ������еڶ���ʵ����
		// 		return FALSE;
		// 	}
		return CFormView::PreCreateWindow(cs);
	}

	void Ccow2View::OnInitialUpdate()
	{
		CFormView::OnInitialUpdate();/////////////4.25ע��
		GetParentFrame()->RecalcLayout();
		ResizeParentToFit();
// 		CAdoSql sql;
// 		sql.DIYCreatDateBase();
// 		sql.DIYCreatTable();
// 		sql.DIYInsertName("admin","141516");
// 		sql.DIYGetInfoOfUser();
// 		sql.DIYCrestCowInfoTable();
// 		sql.DIYGetCowInfo();
		m_hIconLedGreen= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON_Green),IMAGE_ICON,20,20,LR_DEFAULTCOLOR);
		m_hIconLedGray= (HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON_Gray),IMAGE_ICON,20,20,LR_DEFAULTCOLOR);
		HKEY hKey; 
		//�ҵ�ϵͳ��������   
		LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";   
		//��������Key   
		long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &hKey);   
		if(lRet == ERROR_SUCCESS)   
		{   
			char pFileName[MAX_PATH] = {0};   
			//�õ����������ȫ·��   
			DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH);   
			//���һ����Key,������ֵ // �����"test"��Ӧ�ó������֣����Ӻ�׺.exe��  
			lRet = RegSetValueEx(hKey, "��ţ������߼��ϵͳ", 0, REG_SZ, (BYTE *)pFileName, dwRet);   
			//�ر�ע���   
			RegCloseKey(hKey);   
			if(lRet != ERROR_SUCCESS)   
			{   
				editAppend("ϵͳ��������,������ɿ�����������");   
			}   
			else  
			{  
				editAppend("�򿪿��������ɹ�");   
			}   
		}
		DIYConntSocket();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		iIndex=0;
		SetTimer(1, 1000, NULL);
		//m_TeeChart.GetHeader().GetText().SetItem(0,COleVariant("��ţ�������"));
	}

	void Ccow2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void Ccow2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// Ccow2View ���

#ifdef _DEBUG
	void Ccow2View::AssertValid() const
	{
		CFormView::AssertValid();
	}

	void Ccow2View::Dump(CDumpContext& dc) const
	{
		CFormView::Dump(dc);
	}

	Ccow2Doc* Ccow2View::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccow2Doc)));
		return (Ccow2Doc*)m_pDocument;
	}
#endif //_DEBUG


	// Ccow2View ��Ϣ�������


	void Ccow2View::OnBnClickedButton1()//��������
	{
		DIYConntSocket();
		editAppend("�����������ɹ�");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::Onpwd()
	{

		CDLGpwd dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������

	}



	void Ccow2View::OnNewuser()
	{
		if(!UserFlag)
		{
			editAppend("����Ȩ�޲���");
		}

		else
		{
			CNewUser dlg;
			if(dlg.DoModal()==IDOK)
				Invalidate();// TODO: �ڴ���������������
		}
	}


	void Ccow2View::OnDeluser()
	{
		if(!UserFlag)
		{
			editAppend("����Ȩ�޲���");
		}

		else
		{
			CDlgDelUser dlg;
			if(dlg.DoModal()==IDOK)
				Invalidate();// TODO: �ڴ���������������
		}
	}


	void Ccow2View::OnAlluser()
	{
		if(!UserFlag)
		{
			editAppend("����Ȩ�޲���");
		}

		else
		{
			CDlgAllUser dlg;
			if(dlg.DoModal()==IDOK)
				Invalidate();// TODO: �ڴ���������������
		}
	}


	void Ccow2View::OnSetserver()
	{
		CDlgSetServer dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������

	}


	void Ccow2View::OnSetgste()
	{
		CDlgSetGate dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::OnSetport()
	{
		CDlgSetPort dlg;
		if(dlg.DoModal()==IDCANCEL)
		{
			
		}
		Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::OnData()
	{
		CDlgData dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::OnDataview()
	{
		CDlgDataView dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::OnOutdata()
	{
		CDlgOutData dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::OnIndata()
	{
		CDlgInData dlg;
		if(dlg.DoModal()==IDOK)
			Invalidate();// TODO: �ڴ���������������
	}


	void Ccow2View::On32775()
	{
		if(IDYES==AfxMessageBox("ȷ���˳�",MB_YESNO|MB_ICONQUESTION))    //�����Ի����ж��Ƿ�ɾ���ڵ�
		{
			exit(0);// TODO: �ڴ���������������
		}
	}
	void Ccow2View::DIYConntSocket()
	{
		//UpdateData(true);
		WORD        wVersionRequested;  // ָ����Ҫ���ص� winsock ��汾   
		WSADATA     wsaData;            // ���ڴ洢���ص� wdnsock ��汾��Ϣ   
		int         err;             // ���ڼ�� WSAStartup �������н��   

		wVersionRequested = MAKEWORD(1, 1);     // �趨�汾   

		err  = WSAStartup(wVersionRequested, &wsaData);  

		// ���� WSAStartup ���óɹ����� 0   
		// ������   
		if (err != 0)  
		{  
			return;  
		}  

		if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)  
		{  
			WSACleanup();  
			return;  
		}
		//�����׽���
		sersock = socket(AF_INET, SOCK_STREAM, 0);
		//Socket��ַ�ṹ��Ĵ���
		struct sockaddr_in seraddr;
		int serport;
		memset(&seraddr,0,sizeof(seraddr));
		seraddr.sin_family=AF_INET;
		if (str_Ip.IsEmpty() && str_Port.IsEmpty())
		{
			serport=55321;
			//seraddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
		} 
		else
		{
			serport=_ttoi(str_Port);
			//seraddr.sin_addr.S_un.S_addr=inet_addr(str_Ip);
		}
		seraddr.sin_port=htons(serport);
		seraddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
		//seraddr.sin_addr.S_un.S_addr=inet_addr("192,168,0,100");
		//seraddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
		//���׽��ֵ���������ַ�ṹ
		err=bind(sersock, (SOCKADDR*)&seraddr, sizeof(SOCKADDR));
		if(err!=0)
		{
			editAppend("�����ʧ��");
			//exit(-3);
		}
		//�����׽���
		err=listen(sersock,100);
		if(err!=0)
		{
			editAppend("�������ʧ��");
			//exit(-2);
		}
		//�׽���clisock�Ͻ��յ�����ʱ���򴰿ڷ����Զ�����ϢRECEIVE_EVENT
		WSAAsyncSelect(sersock,GetSafeHwnd(),ACCEPT_EVENT,FD_ACCEPT|FD_CLOSE);
	}
	LRESULT Ccow2View::OnEvent(WPARAM wParam,LPARAM lParam)
	{
		CWinThread* pThread = NULL;
		MyParams* pMyPar = new MyParams;

		int nClientEvent=-1;
		switch(lParam)
		{
		case FD_ACCEPT://8
			{	
				//MessageBox("FD_ACCEPT");

				closeclisock=1;
				int len;
				struct sockaddr_in cliaddr;
				//unsigned short num;
				CString str_ip,str_port;

				len = sizeof(cliaddr);//��ʼ������,�������������г�ʼ��
				clisock =accept(sersock,(SOCKADDR*)&cliaddr, &len);
				m_Client[iIndex]=clisock;
				nClientEvent = WSAAsyncSelect(m_Client[iIndex],GetSafeHwnd(),WM_SOCKETIO_MSG,FD_READ | FD_WRITE | FD_CLOSE);
				if(nClientEvent == SOCKET_ERROR)
				{
						editAppend(_T("����IO�¼�ʧ��!"));
						return FALSE;
				}
				
				
				iIndex++;
				//num=cliaddr.sin_port;
				str_ip=inet_ntoa(cliaddr.sin_addr);
				unsigned short num;
				CString str;
				num=ntohs(cliaddr.sin_port);
				str_port.Format("%d",num);
				//str.Format("%d",num);
				editAppend(str_ip+":"+str_port+"�Ѿ�����");
				//SetDlgItemText(IDC_EDIT_State,str_ip+":"+str_port+"���ӳɹ�");

				if (clisock == INVALID_SOCKET)
				{
					editAppend("��������ʧ��");
				}

				break;	
			}
		case FD_CLOSE://32
			{	
				for (int i=0;i<100;i++)
				{
					if (m_Client[i] == clisock)
					{
						closeclisock=closesocket(clisock);
						//WSAAsyncSelect(clisock,GetSafeHwnd(),0,0);
					}
				}
				break;
				//MessageBox("FD_CLOSE");
				//�׽���clisock�Ͻ��յ�����ʱ���򴰿ڷ����Զ�����ϢRECEIVE_EVENT
			}

		default:
			{
				//MessageBox(_T("default"));
				break;
			}

		}
		UpdateData(false);
		return TRUE;
	}
	LRESULT Ccow2View::OnSocketIOMsg(WPARAM wP, LPARAM lP)//��д  ��Ҫ������   
	{

		CWinThread* pThread = NULL;
		SOCKET hcltSocket = (SOCKET)wP;
		SOCKADDR_IN addrcln;
		int addrsize = sizeof(SOCKADDR_IN);
		getpeername(hcltSocket,(SOCKADDR *)&addrcln,&addrsize);

		MyParams* pMyPar = new MyParams;
		pMyPar->sock = hcltSocket;
		////
		CString str,str2;
		int a;
		/////
		switch(LOWORD(lP))
		{
		case FD_WRITE:
			break;
		case FD_READ:

			pThread = AfxBeginThread((AFX_THREADPROC)ReadThreadFunc,(LPVOID)pMyPar);

			break;
		case FD_CLOSE:
			for (int i=0;i<100;i++)
			{
				if (m_Client[i] == hcltSocket)
				{
					closeclisock=closesocket(hcltSocket);
					//WSAAsyncSelect(hcltSocket,GetSafeHwnd(),0,0);
				}

			}
			break;
		}

		return TRUE;
	}

	void Ccow2View::OnBnClickedButSocketclose()
	{
		if(closeclisock)
		{
			closesocket(clisock);
		}
		closesocket(sersock);
		//�׽���clisock�Ͻ��յ�����ʱ���򴰿ڷ����Զ�����ϢRECEIVE_EVENT

		//WSAAsyncSelect(sersock,GetSafeHwnd(),0,0);
		WSACleanup();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		editAppend("�Ͽ�����");
		editAppend("�Ѿ��Ͽ����ӣ���Ҫ�������ֶ����������������������");// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnTimer(UINT_PTR nIDEvent)
	{
		switch(nIDEvent)
		{
		case 1:
			{ 
				CTime tm = CTime::GetCurrentTime();
				CString str = tm.Format("%H:%M:%S %d/%m");
				GetDlgItem(IDC_STATIC_time)->SetWindowText(str);
				GetDlgItem(IDC_STATIC_user)->SetWindowText(str_id);
				break;
			}
		default:
			break;
		}// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

		CFormView::OnTimer(nIDEvent);
	}
	void Ccow2View::editAppend(CString strData)
	{
		CString str,str_time;
		CTime tm=CTime::GetCurrentTime();//��ȡϵͳʱ��
		str_time=tm.Format("%H:%M:%S %m/%d");
		m_ShowError.SetSel(-1);
		m_ShowError.ReplaceSel(strData+" "+str_time+"\r\n");
		SaveLog(strData+" "+str_time);
		/*GetDlgItemText(IDC_EDIT_State,str); //IDC_EDIT�ǿؼ���ID
		str+=strData;
		str+=str_TableName+"\r\n";
		SetDlgItemText(IDC_EDIT_State,str);*/

	}


	void Ccow2View::OnBnClickedButOpencom()
	{
		if(m_mscomm.get_PortOpen()) //��������Ǵ򿪵ģ����йرմ���
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		if (Com.IsEmpty() || PTY.IsEmpty())
		{
			//editAppend("Ĭ��ѡ�񴮿�3��������128000");
			Com="com7";
			PTY="115200";
			CString str_com=Com.Right(1);
			int m_com=_ttoi(str_com);
			m_mscomm.put_CommPort(m_com); //ѡ��COM1 
			m_mscomm.put_InBufferSize(999999); //���ջ����� 
			m_mscomm.put_OutBufferSize(1024);//���ͻ����� 
			m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ 
			m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
			m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm
			m_mscomm.put_Settings((PTY+",n,8,1"));
			if(!m_mscomm.get_PortOpen())//�������û�д����
			{m_mscomm.put_PortOpen(TRUE);//�򿪴���
			editAppend((Com+"�򿪳ɹ�"));
			}
			else
			{m_mscomm.put_OutBufferCount(0);
			editAppend((Com+"��ʧ��"));
			}// TODO: �ڴ���ӿؼ�֪ͨ����������
			GetDlgItem(IDC_BUT_OpenCom)->EnableWindow(FALSE);

		} 
		else
		{
			CString str_com=Com.Right(1);
			int m_com=_ttoi(str_com);
			m_mscomm.put_CommPort(m_com); //ѡ��COM1 
			m_mscomm.put_InBufferSize(9999); //���ջ����� 
			m_mscomm.put_OutBufferSize(1024);//���ͻ����� 
			m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ 
			m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
			m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm
			m_mscomm.put_Settings((PTY+",n,8,1"));
			if(!m_mscomm.get_PortOpen())//�������û�д����
			{m_mscomm.put_PortOpen(TRUE);//�򿪴���
			editAppend((Com+"�򿪳ɹ�"));
			}
			else
			{m_mscomm.put_OutBufferCount(0);
			editAppend((Com+"��ʧ��"));
			}// TODO: �ڴ���ӿؼ�֪ͨ����������
			GetDlgItem(IDC_BUT_OpenCom)->EnableWindow(FALSE);
		}

	}
	void Ccow2View::OnBnClickedButClosecom()
	{
		/*TODO: Add your control notification handler code here*/
		m_mscomm.put_PortOpen(FALSE);//�رմ���
		editAppend((Com+"�رճɹ�"));
		GetDlgItem(IDC_BUT_OpenCom)->EnableWindow(TRUE);// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	BEGIN_EVENTSINK_MAP(Ccow2View, CFormView)
		ON_EVENT(Ccow2View, IDC_MSCOMM1, 1, Ccow2View::OnCommMscomm1, VTS_NONE)
	END_EVENTSINK_MAP()


	void Ccow2View::OnCommMscomm1()
	{
		Sleep(200);
		CSplitStr Split;
		CString m_EditReceive,strtemp2,m_EditReceive2;
		// TODO: Add your message handler code here
		static unsigned int cnt=0;
		VARIANT variant_inp; COleSafeArray safearray_inp; long len,k;
		unsigned int data[99999]={0};
		byte rxdata[99999]; //���� BYTE ����
		CString strtemp;
		if(m_mscomm.get_CommEvent()==2)
		{	cnt++;
		variant_inp=m_mscomm.get_Input(); //����������Ϣ 
		safearray_inp=variant_inp; ///����ת�� 
		len=safearray_inp.GetOneDimSize();
		for(k=0;k<len;k++)
		{safearray_inp.GetElement(&k,rxdata+k);}
		for(k=0;k<len;k++)
		{	
		strtemp.Format(_T("%x"),*(rxdata+k));
		BYTE bt=*(char*)(rxdata+k);
		strtemp2.Format("%c",bt);
		if (strtemp.GetLength()<2)
		{
			m_EditReceive+="0"+strtemp;
		}
		else{m_EditReceive+=strtemp;}
		m_EditReceive2+=strtemp2;
		// 		CString temp=_T("\r\n"); //����
		// 		m_EditReceive+=temp;
		}
		}
		int IPlen=m_EditReceive.GetLength();
		if (m_EditReceive.Left(14)=="fefc1000195001")
		{
			struct_time* pTime=new struct_time;
			pTime->id=m_EditReceive.Mid(26,4);
			pTime->year=m_EditReceive.Mid(14,2);
			pTime->mouth=m_EditReceive.Mid(16,2);
			pTime->day=m_EditReceive.Mid(18,2);
			pTime->hour=m_EditReceive.Mid(20,2);
			pTime->mint=m_EditReceive.Mid(22,2);
			pTime->scu=m_EditReceive.Mid(24,2);
			int a=strtol((m_EditReceive.Mid(36,4)),NULL,16);
			int b=strtol((m_EditReceive.Mid(40,4)),NULL,16);
			int c=strtol((m_EditReceive.Mid(44,4)),NULL,16);
			int d=strtol((m_EditReceive.Mid(48,4)),NULL,16);
			if (a>=999)
			{
// 				if (b>=999)
// 				{
// 					if (c>999)
// 					{
// 						pTime->data1.Format("%d",d);
// 					} 
// 					else
// 					{
// 						pTime->data1.Format("%d",c);
// 					}
// 				} 
// 				else
// 				{
					pTime->data1.Format("%d",b);
				//}
			}
			else
			{
				pTime->data1.Format("%d",a);
			}
			CString str_time=pTime->year+"/"+pTime->mouth+"/"+pTime->day+" "+pTime->hour+":"+pTime->mint+":"+pTime->scu;
			CAdoSql sql;
			CString str_data=pTime->data1;
			CString strdate=pTime->year+"/"+pTime->mouth+"/"+pTime->day;
			CString strtime=pTime->hour+":"+pTime->mint+":"+pTime->scu;
			sql.DIYInsertCowInfo(pTime->id,pTime->id);
			sql.DIYCreatCowTable(pTime->id);
			sql.DIYInsertCowData(pTime->id,strdate,strtime,str_data);
			//sql.DIYTnsertCowMysql(pTime->id,pTime->id);
			//sql.DIYADOMysqlorder(pTime->id,strdate,strtime,str_data);
			//SaveLog(pTime->id+"���ݵ���    ");
			//editAppend("�ڵ�"+pTime->id+"������");
		}
		if(m_EditReceive=="fefc100003A00101")//FE FC 10 00 03 A0 01 01   
		{
			editAppend("��ʼGPRS���óɹ�������ֹͣ�ɼ�");
		}
		if(m_EditReceive=="fefc100002a005")//FE FC 10 00 02 A0 05   
		{
			editAppend("ֹͣGPRS���óɹ������ݿ�ʼ�ɼ�");
		}
		if(m_EditReceive=="fefc100010a0030d696e20736574206d6f64650d0a")//FE FC 10 00 10 A0 03 0D 69 6E 20 73 65 74 20 6D 6F 64 65 0D 0A  
		{
			editAppend("����GPRS���óɹ���");
		}
		if(m_EditReceive=="fefc100009a003060d0a4f4b0d0a")  
		{
			editAppend("�����ɹ���");
		}
		if (m_EditReceive.Mid(16,18)=="44435356524950303d")
		{
			GprsPressIP(m_EditReceive.Mid(34,(IPlen-46)));
		}
		if (m_EditReceive.Mid(16,22)=="4443535652504f5254303d")
		{
			GprsPressPort(m_EditReceive.Mid(38,(IPlen-50)));
		}
		//UpdateData(FALSE);// TODO: �ڴ˴������Ϣ����������
	}

	CString Ccow2View::DIYTransfrom(char buf)
	{
		char recvBufTemp[99];
		int j=0;
		char temp;
		temp=(buf & 0xF0)>>4;
		recvBufTemp[j]=(temp<=9)?temp+'0':(temp-10)+'A';
		j++;
		temp=(buf & 0x0F);
		recvBufTemp[j]=(temp<=9)?temp+'0':(temp-10)+'A';
		j++;
		recvBufTemp[j]='\0';
		return (CString)recvBufTemp;

	}
	LRESULT Ccow2View::ReceiveMessage(WPARAM wParam, LPARAM lParam)  
	{  
		//int recvint = wParam;   
		CString recvstr = (LPCTSTR)wParam;
		editAppend(recvstr);
		return true; 
	}

	char Ccow2View::HexChar(char c)//���һ���ַ��ǲ���ʮ�������ַ������Ƿ�����Ӧ��ֵ�����򷵻�0x10��
	{	
		if((c>='0')&&(c<='9'))
			return c-0x30;
		else if((c>='A')&&(c<='F'))
			return c-'A'+10;
		else if((c>='a')&&(c<='f'))
			return c-'a'+10;
		else return 0x10;
	}
	int Ccow2View::Str2Hex(CString str,CByteArray &data)
	{
		//��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ�������ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
		int t,t1;
		int rlen=0,len=str.GetLength();
		data.SetSize(len/2);
		for(int i=0;i<len;)
		{char l,h=str[i];
		if(h==' ')
		{i++;
		continue;
		}
		i++;
		if(i>=len)break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
		}
		data.SetSize(rlen);
		return rlen;
	}
// 	void Ccow2View::On32801()
// 	{
// 		AfxMessageBox("a");// TODO: �ڴ���������������
// 	}
	void Ccow2View::OnBnClickedBtnReadhistory()
	{
		CString str_HistoryDataMouth,str_HistoryDataData;
		GetDlgItemText(IDC_EDT_HistoryDataMouth,str_HistoryDataMouth);
		GetDlgItemText(IDC_EDT_HistoryDataDay,str_HistoryDataData);
		if (str_HistoryDataData.IsEmpty()&&str_HistoryDataMouth.IsEmpty())
		{
			AfxMessageBox("����ʱ�䲻׼ȷ���Զ���ѯȫ����ʷ��¼��");
			CString str;
			str="FE FC 10 00 02 50 02 ";
			CByteArray data;
			Str2Hex(str,data);
			m_mscomm.put_Output(COleVariant(data));
		}
		else
		{
			CString str;
			str="FE FC 10 00 02 50 02 ";
			CByteArray data;
			Str2Hex(str,data);
			m_mscomm.put_Output(COleVariant(data));
		}
		// TODO: �ڴ���ӿؼ�֪ͨ����������// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButStartgprs()
	{
		editAppend("��ʼGprs���ã��ɼ������ж�");// TODO: �ڴ���ӿؼ�֪ͨ����������
		CString str;
		str="FE FC 10 00 02 A0 00";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButStopgprs()
	{
		editAppend("�˳�Gprs���ã��ɼ����ݿ�ʼ");// TODO: �ڴ���ӿؼ�֪ͨ����������
		CString str;
		str="FE FC 10 00 02 A0 04";//fe fc 10 00 02 a0 04
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButingprs()
	{
		CString str;
		str="FE FC 10 00 06 A0 02 03 2B 2B 2B";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));
	}


	void Ccow2View::OnBnClickedButoutgprs()
	{

		CString str;
		str="FE FC 10 00 0F A0 02 0C 41 54 2B 4F 55 54 53 45 54 3D 4F 4E";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButSetgprs()
	{
// 		CString str_order;
// 		GetDlgItemText(IDC_EDIT_order,str_order);
// 		int len=str_order.GetLength();
// 		CString str_length;
// 		str_length.Format("%d",len);
		UpdateData(TRUE);
		CString strEdit;
		CString str;
		int len=m_edit.GetLength();
		for(int i=0; i<m_edit.GetLength(); i++)
		{
			str.Format("%2x",m_edit[i]);
			strEdit += str + " ";
		}
		GprsOrder(strEdit,len);
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButreadgprsip()
	{
		CString str;
		str="FE FC 10 00 0F A0 02 0C 41 54 2B 44 43 53 56 52 49 50 30 3F ";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButreadgprsport()
	{
		CString str;
		str="FE FC 10 00 11 A0 02 0E 41 54 2B 44 43 53 56 52 50 4F 52 54 30 3F ";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������
	}

	void Ccow2View::GprsOrder(CString input,int len)
	{
		CString str,str_len1,str_len2;
		str_len2.Format("%.2x",len);
		str_len1.Format("%.2x",(len+3));
		str="FE FC 10 00 "+str_len1+" A0 02 "+str_len2+" "+input;
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));
	}

	void Ccow2View::OnBnClickedButsetgprsip()
	{
		UpdateData(TRUE);
		CString strEdit;
		CString str;
		m_GprsIp="AT+DCSVRIP0="+m_GprsIp;
		int len=m_GprsIp.GetLength();
		
		for(int i=0; i<m_GprsIp.GetLength(); i++)
		{
			str.Format("%2x",m_GprsIp[i]);
			strEdit += str + " ";
		}
		GprsOrder(strEdit,len);
	}


	void Ccow2View::OnBnClickedButsetgprsport()
	{
		UpdateData(TRUE);
		CString strEdit;
		CString str;
		m_GprsPort="AT+DCSVRPORT0="+m_GprsPort;
		int len=m_GprsPort.GetLength();

		for(int i=0; i<m_GprsPort.GetLength(); i++)
		{
			str.Format("%2x",m_GprsPort[i]);
			strEdit += str + " ";
		}
		GprsOrder(strEdit,len);// TODO: �ڴ���ӿؼ�֪ͨ����������
	}


	void Ccow2View::OnBnClickedButSavegprs()
	{

		CString str;
		str="FE FC 10 00 0D A0 02 0A 41 54 2B 53 41 56 45 3D 4F 4E";
		CByteArray data;
		Str2Hex(str,data);
		m_mscomm.put_Output(COleVariant(data));// TODO: �ڴ���ӿؼ�֪ͨ����������// TODO: �ڴ���ӿؼ�֪ͨ����������
	}
	void Ccow2View::GprsPressIP(CString a)
	{
		int IPLen=a.GetLength();
		CString Ip;
		for ( int i=0;i<IPLen;)
		{
			CString str=a.Mid(i,2);
			if (str=="2e")
			{
				Ip=Ip+".";
				i=(i+2);
				continue;
			}
			int d = _ttoi(str);
			int b;
			if (d<=39)
			{
				b=d-30;
			}
			str.Format("%d",b);
			Ip=Ip+str;
			i=(i+2);
		}
		editAppend(("��ǰGprs��Ip��ַ��"+Ip));
	}
	void Ccow2View::GprsPressPort(CString a)
	{
		int IPLen=a.GetLength();
		CString Ip;
		for ( int i=0;i<IPLen;)
		{
			CString str=a.Mid(i,2);
			int d = _ttoi(str);
			int b;
			if (d<=39)
			{
				b=d-30;
			}
			str.Format("%d",b);
			Ip=Ip+str;
			i=(i+2);
		}
		editAppend(("��ǰGprs�Ķ˿ںţ�"+Ip));
	}
	UINT ReadThreadFunc(LPVOID lpParameter)
	{


		//////////////////////////////////////////////////////////////////////////
		CString strBuoyId;
		theApp.m_Params=(MyParams*)lpParameter;
		SOCKET hcltSocket = theApp.m_Params->sock;
		SOCKET sendSocket;

		CString strSQL = _T("");//����ִ�е�SQL��䣻
		//CString sqlTemp = "";//��ʱsql��䣻
		CString strClientIP = _T("");
		CString strClientPort = _T("");
		UINT nPort = 0;
		CString strRecMsg = _T("");//�����Ľ��յ�������;
		char buff[1024];//��ʼ����������
		char buff_sebd[5];
		int nRecLength = 0;//���յ��ͻ��˷��������ݰ����ȣ�
		int nCount = 0;//��ѯ���ݿ�õ��ļ�¼������
		//	SOCKET hcltSocket = (SOCKET)lpParameter;
		SOCKADDR_IN addrcln;
		int addrsize = sizeof(SOCKADDR_IN);

		getpeername(hcltSocket,(SOCKADDR *)&addrcln,&addrsize);
		strClientIP = inet_ntoa(addrcln.sin_addr);
		nPort = ntohs(addrcln.sin_port);
		strClientPort.Format("%d",nPort);
		memset(buff,'\0',sizeof(buff));//�����buffer
		recv(hcltSocket,buff,1024,NULL);//�������Կͻ��˵���Ϣ��
		strcpy(buff_sebd, "beat");
		int senflag=send(hcltSocket,buff_sebd,4,0);
		if (senflag==SOCKET_ERROR)
		{
			theApp.m_sql->SaveLog("�����жϣ�   ");
		}
		CString FLG=(theApp.m_sql->DIYTransfrom(buff[0]));
		if (buff[0]=='NL')
		{
			
		}
		if (FLG=="4E")
		{

		}
		if (FLG=="FE")
		{
		CString id=(theApp.m_sql->DIYTransfrom(buff[13]))+(theApp.m_sql->DIYTransfrom(buff[14]));
		CString year=(theApp.m_sql->DIYTransfrom(buff[7]));
		CString mouth=(theApp.m_sql->DIYTransfrom(buff[8]));
		CString day=(theApp.m_sql->DIYTransfrom(buff[9]));
		CString hour=(theApp.m_sql->DIYTransfrom(buff[10]));
		CString mint=(theApp.m_sql->DIYTransfrom(buff[11]));
		CString scu=(theApp.m_sql->DIYTransfrom(buff[12]));
 		CString cowData=(theApp.m_sql->DIYTransfrom(buff[18]))+(theApp.m_sql->DIYTransfrom(buff[19]));
 		int a=strtol(cowData,NULL,16);
		if (a>=999)
		{
			cowData=(theApp.m_sql->DIYTransfrom(buff[20]))+(theApp.m_sql->DIYTransfrom(buff[21]));
			a=strtol(cowData,NULL,16);
			if (a>=999)
			{
				a=0;
			}
		}
 		cowData.Format("%d",a);
 		CString str_time=year+"/"+mouth+"/"+day+" "+hour+":"+mint+":"+scu;
		CString strdata=year+"/"+mouth+"/"+day;
        CString strtime=hour+":"+mint+":"+scu;
 		//theApp.m_sql->DIYInsertCowInfo(id,id);
		//theApp.m_sql->DIYCreatCowTable(id);
 		//theApp.m_sql->DIYInsertCowData(id,strdata,strtime,cowData);
		theApp.m_sql->DIYTnsertMysql(id,strdata,strtime,cowData);
		theApp.m_sql->DIYADOMysqlorder(id,strdata,strtime,cowData);
		//theApp.m_sql->SaveLog(id+"���ݵ���   ");
		}

		return 0;
	}
	BOOL Ccow2View::GetFreeClient(void)//2
	{
		int iResult = -1;
		for(int i=0;i<100;i++)
		{
			if(m_Client[i] == INVALID_SOCKET)
			{
				iResult = i;//�õ�Client�����е�һ��socketΪ�յ�Client��
				break;
			}
		}
		return iResult;//��������Client�����еĵ�ַ��;
	}
	void Ccow2View::SaveLog(CString strText)
	{

		CString strPath;
		GetCurrentDirectory(MAX_PATH,strPath.GetBuffer(MAX_PATH));
		strPath.ReleaseBuffer();
		strPath+="\\������־\\";
		CreateDirectory(strPath, NULL);
		CTime tCurTime = CTime::GetCurrentTime();//��ǰ����ʱ�䣻
		CString strTime;
		strTime = tCurTime.Format("%Y%m%d_%H%M%S");//��CTimeת��CString��
		strPath+="WebLog_";
		strPath+= strTime;
		strPath+=".txt";
		std::ofstream saveFile;
		saveFile.open(strPath);

		if (saveFile)
		{
				saveFile<<strText<<"\n";
		}
		else
		{
			//�ļ���ʧ�ܣ�
		}

		saveFile.close();

	}