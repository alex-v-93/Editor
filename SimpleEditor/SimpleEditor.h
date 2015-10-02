
// SimpleEditor.h : главный файл заголовка для приложения SimpleEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSimpleEditorApp:
// О реализации данного класса см. SimpleEditor.cpp
//

class CSimpleEditorApp : public CWinApp
{
	ULONG m_tockenGdipus = 0;
public:
	CSimpleEditorApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimpleEditorApp theApp;
