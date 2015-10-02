// dllmain.cpp: реализация DllMain.

#include "stdafx.h"
#include "resource.h"
#include "SimpleEditorHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CSimpleEditorHandlersModule _AtlModule;

class CSimpleEditorHandlersApp : public CWinApp
{
public:

// Переопределение
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSimpleEditorHandlersApp, CWinApp)
END_MESSAGE_MAP()

CSimpleEditorHandlersApp theApp;

BOOL CSimpleEditorHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
	return CWinApp::InitInstance();
}

int CSimpleEditorHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
