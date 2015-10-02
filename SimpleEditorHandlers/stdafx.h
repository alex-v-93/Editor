// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ���������� ������ ��������, ������� ����� ������������,
// ����� ����������

#pragma once

#define GDIPVER 0x0110

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ��������� ������������ CString ����� ������

#ifdef _MANAGED
#error ������ ��������� ����������� ����� ������ � ���� ����������� ������.  ��������� � ���������� ����� CLR � ��������� ������� ��������� CLR.
#endif

#ifndef _UNICODE
#error ���������� ������������ ����� ������ ���������� ��������� � ���������� �������.  ���������� �������� "������" ��� ��������� "���������" � ��������� �������.
#endif

#define SHARED_HANDLERS

#include <afxwin.h>
#include <afxext.h>
#include <afxole.h>
#include <afxodlgs.h>
#include <afxrich.h>
#include <afxhtml.h>
#include <afxcview.h>
#include <afxwinappex.h>
#include <afxframewndex.h>
#include <afxmdiframewndex.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdisp.h>        // ������ ������������� MFC
#endif // _AFX_NO_OLE_SUPPORT

#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>


#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
using namespace cv;


#include <memory>

#include <Gdiplus.h>
using namespace Gdiplus;

using namespace std;