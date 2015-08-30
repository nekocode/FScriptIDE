
// fs������ǿ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "fs������ǿ����.h"
#include "fs������ǿ����Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cfs������ǿ����Dlg �Ի���
Cfs������ǿ����Dlg::Cfs������ǿ����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cfs������ǿ����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cfs������ǿ����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cfs������ǿ����Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cfs������ǿ����Dlg ��Ϣ�������

BOOL Cfs������ǿ����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1,1000,NULL);

	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, 200, LWA_ALPHA); 


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cfs������ǿ����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cfs������ǿ����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cfs������ǿ����Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HWND hwnd;
	RECT rect;

	if(hwnd=::FindWindow(L"Notepad++",NULL))
	{
//		::GetWindowRect(hwnd,&rect);
//		::SetWindowPos(this->m_hWnd,HWND_TOP,rect.left,rect.top,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
	}
	else
	{
		//�˳�����
		SendMessage(WM_CLOSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Cfs������ǿ����Dlg::OnDropFiles(HDROP hDropInfo)
{
	//��ȡ����ק���ļ�·��
	wchar_t szFileName[MAX_PATH + 1];
	DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
	
	//��ȡ��ǰ·��
	wchar_t szFilePath[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1,szFilePath);

	//��ȡ·���в���ͬ�Ĳ���
	int i=0,i2=1;
	while(szFileName[i]==szFilePath[i])
		i++;

	szFilePath[0]='\"';

	for(;i<_tcslen(szFileName)+1;i++)
	{
		if(szFileName[i]=='\0')
		{
			szFilePath[i2]='\"';
			szFilePath[i2+1]='\0';
			break;
		}
		else
		{
			szFilePath[i2]=szFileName[i];
			i2++;
		}
	}

	// ���ļ�����ʾ����
//	SetWindowText(szFilePath);

	//��������а���
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char* buffer;
		EmptyClipboard();
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,szFilePath,-1,NULL,0,NULL,FALSE);

		clipbuffer = GlobalAlloc(GMEM_DDESHARE, dwNum);
		buffer = (char*)GlobalLock(clipbuffer);

		//���ֽ��ַ���ת��Ϊ���ֽ��ַ���
		WideCharToMultiByte (CP_OEMCP,NULL,szFilePath,-1,buffer,dwNum,NULL,FALSE);
//		wcscpy(buffer,szFileName); 
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}

	HWND hwnd;
	if(hwnd=::FindWindow(L"Notepad++",NULL))
	{
		::SetActiveWindow(hwnd);
		hwnd = ::FindWindowExA(hwnd,0,"Scintilla",NULL);
		//����ճ����Ϣ
		::PostMessageW(hwnd,WM_PASTE ,0,0);
	}
	else
	{
		SendMessage(WM_CLOSE);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}
