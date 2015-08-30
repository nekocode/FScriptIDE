
// fs代码增强工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "fs代码增强工具.h"
#include "fs代码增强工具Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cfs代码增强工具Dlg 对话框
Cfs代码增强工具Dlg::Cfs代码增强工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cfs代码增强工具Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cfs代码增强工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cfs代码增强工具Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cfs代码增强工具Dlg 消息处理程序

BOOL Cfs代码增强工具Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1,1000,NULL);

	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, 200, LWA_ALPHA); 


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cfs代码增强工具Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cfs代码增强工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cfs代码增强工具Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HWND hwnd;
	RECT rect;

	if(hwnd=::FindWindow(L"Notepad++",NULL))
	{
//		::GetWindowRect(hwnd,&rect);
//		::SetWindowPos(this->m_hWnd,HWND_TOP,rect.left,rect.top,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
	}
	else
	{
		//退出程序
		SendMessage(WM_CLOSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Cfs代码增强工具Dlg::OnDropFiles(HDROP hDropInfo)
{
	//获取被拖拽的文件路径
	wchar_t szFileName[MAX_PATH + 1];
	DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
	
	//获取当前路径
	wchar_t szFilePath[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1,szFilePath);

	//截取路径中不相同的部分
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

	// 把文件名显示出来
//	SetWindowText(szFilePath);

	//储存进剪切板中
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char* buffer;
		EmptyClipboard();
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,szFilePath,-1,NULL,0,NULL,FALSE);

		clipbuffer = GlobalAlloc(GMEM_DDESHARE, dwNum);
		buffer = (char*)GlobalLock(clipbuffer);

		//宽字节字符串转换为多字节字符串
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
		//发送粘贴消息
		::PostMessageW(hwnd,WM_PASTE ,0,0);
	}
	else
	{
		SendMessage(WM_CLOSE);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}
