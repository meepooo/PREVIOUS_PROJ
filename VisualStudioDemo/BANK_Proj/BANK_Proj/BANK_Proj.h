
// BANK_Proj.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBANK_ProjApp: 
// �йش����ʵ�֣������ BANK_Proj.cpp
//

class CBANK_ProjApp : public CWinApp
{
public:
	CBANK_ProjApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBANK_ProjApp theApp;