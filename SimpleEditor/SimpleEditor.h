
// SimpleEditor.h : ������� ���� ��������� ��� ���������� SimpleEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CSimpleEditorApp:
// � ���������� ������� ������ ��. SimpleEditor.cpp
//

class CSimpleEditorApp : public CWinApp
{
	ULONG m_tockenGdipus = 0;
public:
	CSimpleEditorApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimpleEditorApp theApp;
