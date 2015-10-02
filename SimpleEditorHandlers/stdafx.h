// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или конкретных включаемых файлов проектов, которые часто используются,
// редко изменяются

#pragma once

#define GDIPVER 0x0110

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// некоторые конструкторы CString будут явными

#ifdef _MANAGED
#error Нельзя создавать обработчики типов файлов в виде управляемых сборок.  Отключите в параметрах среды CLR в свойствах проекта поддержку CLR.
#endif

#ifndef _UNICODE
#error Построение обработчиков типов файлов необходимо выполнять с поддержкой Юникода.  Установите значение "Юникод" для параметра "Кодировка" в свойствах проекта.
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
#include <afxdisp.h>        // классы автоматизации MFC
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