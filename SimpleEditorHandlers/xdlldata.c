// �������� ��� dlldata.c

#define REGISTER_PROXY_DLL //DllRegisterServer � �. �.

#define _WIN32_WINNT 0x0500	//��� WinNT 4.0 ��� Win95 � DCOM
#define USE_STUBLESS_PROXY	//���������� ������ � ������ MIDL /Oicf

#pragma comment(lib, "rpcns4.lib")
#pragma comment(lib, "rpcrt4.lib")

#define ENTRY_PREFIX	Prx

#include "dlldata.c"
#include "SimpleEditorHandlers_p.c"
