
// NetworkModeling.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetworkModelingApp:
// �йش����ʵ�֣������ NetworkModeling.cpp
//

class CNetworkModelingApp : public CWinApp
{
public:
	CNetworkModelingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetworkModelingApp theApp;