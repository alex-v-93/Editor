
// SimpleEditorView.cpp : реализация класса CSimpleEditorView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SimpleEditor.h"
#endif

#include "SimpleEditorDoc.h"
#include "SimpleEditorView.h"
#include <windowsx.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleEditorView

IMPLEMENT_DYNCREATE(CSimpleEditorView, CView)

BEGIN_MESSAGE_MAP(CSimpleEditorView, CView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// создание/уничтожение CSimpleEditorView

CSimpleEditorView::CSimpleEditorView()
{
	// TODO: добавьте код создания
	
}

CSimpleEditorView::~CSimpleEditorView()
{
}

BOOL CSimpleEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	BOOL result = CView::PreCreateWindow(cs);
	
	return result;
}

// рисование CSimpleEditorView

void CSimpleEditorView::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;

	if (bpp == 8)
	{
		RGBQUAD* palette = bmi->bmiColors;

		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}

char* CSimpleEditorView::IplImageToBuffer(IplImage* pImg)
{
	LPVOID bits_copy = GlobalAlloc(GMEM_FIXED, pImg->width*pImg->height*pImg->nChannels);
	char* result = new char[pImg->width*pImg->height*pImg->nChannels];
	char* pIter = result;
	for (int i = 0; i < pImg->height; i++)
	{
		char* line = pImg->imageDataOrigin + pImg->widthStep*i;
		for (int j = 0; j < pImg->width; j++, line += pImg->nChannels)
		{
			int c = pImg->nChannels;
			while (c != 0)
			{
				memcpy(pIter, line + c, sizeof(char));
				//*pIter = *line;
				c--;
				pIter++;
			}
			
		}
	}
	return result;
}

HBITMAP CSimpleEditorView::ConvertIplImageToHBITMAP(IplImage* pimg)
{
	HBITMAP result = nullptr;
	int bpp = pimg->nChannels*pimg->depth;
	assert(pimg->width >= 0 && pimg->height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));
	CvMat dst;
	void* dst_ptr = 0;
	unsigned char buffer[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	ZeroMemory(bmih, sizeof(BITMAPINFOHEADER));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = pimg->width;
	bmih->biHeight = pimg->origin ? abs(pimg->height) : -abs(pimg->height);
	bmih->biPlanes = 1;
	bmih->biBitCount = bpp;
	bmih->biCompression = BI_RGB;
	result = CreateDIBSection(nullptr, bmi, DIB_RGB_COLORS, &dst_ptr, 0, 0);
	cvInitMatHeader(&dst, pimg->height, pimg->width, CV_8UC3, dst_ptr, /*pimg->widthStep*/(pimg->width*pimg->nChannels + 3) & -4);
	
	cvConvertImage(pimg, &dst, pimg->origin ? CV_CVTIMG_FLIP : 0);
	return result;
}

void CSimpleEditorView::DrawIplImage(CDC* pDc, Mat* pImg)
{
#if 0
	if (pImg && pImg->depth == IPL_DEPTH_8U)
	{ 
		CRect rc;
		this->GetClientRect(&rc);

		int width = pImg->width;
		int height = pImg->height;
		double difference = (double)width / (double)height;
		if (width > (rc.Width()))
		{
			width = rc.Width();
			height = width / difference;
		}
		if (height > (rc.Height()))
		{
			height = rc.Height();
			width = height * difference;
		}

		uchar buffer[sizeof(BITMAPINFOHEADER) + 1024]; 
		BITMAPINFO* bmi = (BITMAPINFO*)buffer; 
		int bmp_w = pImg->width, bmp_h = pImg->height;

		FillBitmapInfo(bmi, bmp_w, bmp_h, pImg->depth, pImg->origin);

		int from_x = MIN(MAX(rc.right, 0), bmp_w - 1); 
		int from_y = MIN(MAX(rc.bottom, 0), bmp_h - 1); 

		SetDIBitsToDevice(pDc->m_hDC, // Handle to the device context 
			rc.left,  // Specifies the x-coordinate, in logical units, of the upper-left corner of the destination rectangle 
			rc.top,  // Specifies the y-coordinate, in logical units, of the upper-left corner of the destination rectangle 
			width, // Specifies the width, in logical units, of the DIB 
			height, // Specifies the height, in logical units, of the DIB 
			from_x, // Specifies the x-coordinate, in logical units, of the lower-left corner of the DIB 
			from_y, // Specifies the y-coordinate, in logical units, of the lower-left corner of the DIB 
			from_y, // Specifies the starting scan line in the DIB 
			height, // Specifies the number of DIB scan lines contained in the array pointed to by the lpvBits parameter 
			pImg->imageData + /*from_y*/pImg->height*pImg->widthStep, // Pointer to DIB color data stored as an array of bytes 
			bmi, // Pointer to a BITMAPINFO structure that contains information about the DIB 
			DIB_RGB_COLORS); // Specifies whether the bmiColors member of the BITMAPINFO structure contains explicit red, green, blue (RGB) values or indexes into a palette 
	}
#endif
	
	Mat m;
	IplImage img(*pImg);
	CRect rc;
	this->GetClientRect(&rc);
	//Graphics graphics(pDc->m_hDC);
	int width = img.width;
	int height = img.height;
	double difference = (double)width / (double)height;
	if (width > (rc.Width()))
	{
		width = rc.Width();
		height = width / difference;
	}
	if (height > (rc.Height()))
	{
		height = rc.Height();
		width = height * difference;
	}
	BITMAPINFO info;
	CBitmap bitm;
	BITMAP bi;
	
	HBITMAP hBi = ConvertIplImageToHBITMAP(&img);
	SelectObject(pDc->m_hDC, hBi);
	DeleteBitmap(hBi);
	//GetObject(hBi, sizeof(bi), &bi);

	//char* buf = IplImageToBuffer(pImg);
	//BOOL result = bitm.CreateBitmap(pImg->width, pImg->height, 1, pImg->nChannels*pImg->depth, buf);
	//result = pDc->DrawState(CPoint(rc.left, rc.top), CSize(width, height), &bitm, 0);
	
	//delete[] buf;
}

void CSimpleEditorView::DrawBitmap(CDC* pDc, Gdiplus::Bitmap* pBitmap)
{
	CRect rc;
	this->GetClientRect(&rc);
	Graphics graphics(pDc->m_hDC);
	pBitmap->GetWidth();
	int width = pBitmap->GetWidth();
	int height = pBitmap->GetHeight();
	double difference = (double)width / (double)height;
	if (width > (rc.Width()))
	{
		width = rc.Width();
		height = width / difference;
	}
	if (height > (rc.Height()))
	{
		height = rc.Height();
		width = height * difference;
	}

	graphics.DrawImage(pBitmap, (INT)rc.left, (INT)rc.top, width, height);
}

void CSimpleEditorView::OnDraw(CDC* pDC)
{
	CSimpleEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//Bitmap* spBitm = pDoc->GetBitmap();
	shared_ptr<Mat> pImg = pDoc->GetImage();
	CDC cdc;
	CBitmap bitmap;
	cdc.CreateCompatibleDC(pDC);
	CRect rct;
	this->GetClientRect(&rct);
	bitmap.CreateCompatibleBitmap(pDC, rct.Width(), rct.Height());
	CBitmap* oldBitmap = cdc.SelectObject(&bitmap);
	
	cdc.SelectObject(GetStockObject(WHITE_PEN));
	cdc.Rectangle(rct);
	cdc.SelectObject(GetStockObject((BLACK_PEN)));
	cdc.SetROP2(R2_NOTXORPEN);
	if (pImg != nullptr)
	{
		DrawIplImage(&cdc, pImg.get());
		//DrawBitmap(&cdc, spBitm);
	}
	pDC->BitBlt(0, 0, rct.Width(), rct.Height(), &cdc, 0, 0, SRCCOPY);
	cdc.DeleteDC();
	bitmap.DeleteObject();
	oldBitmap->DeleteObject();
	//DeleteObject(oldBitmap);
	//DeleteObject(bitmap);
}


// диагностика CSimpleEditorView

#ifdef _DEBUG
void CSimpleEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleEditorDoc* CSimpleEditorView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleEditorDoc)));
	return (CSimpleEditorDoc*)m_pDocument;
}

#endif //_DEBUG


// обработчики сообщений CSimpleEditorView


BOOL CSimpleEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	return /*CView::OnEraseBkgnd(pDC)*/FALSE;
}
