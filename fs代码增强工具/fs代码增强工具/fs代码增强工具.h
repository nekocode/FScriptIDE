
// fs������ǿ����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cfs������ǿ����App:
// �йش����ʵ�֣������ fs������ǿ����.cpp
//

class Cfs������ǿ����App : public CWinApp
{
public:
	Cfs������ǿ����App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cfs������ǿ����App theApp;