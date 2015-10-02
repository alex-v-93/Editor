
// SimpleEditorView.h : интерфейс класса CSimpleEditorView
//

#pragma once



class CSimpleEditorView : public CView
{
protected: // создать только из сериализации
	CSimpleEditorView();
	DECLARE_DYNCREATE(CSimpleEditorView)
	
// Атрибуты
public:
	CSimpleEditorDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CSimpleEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void DrawBitmap(CDC* pDc, Gdiplus::Bitmap* pBitmap);
	void DrawIplImage(CDC* pDc, Mat* pImg);
	void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin);
	char* IplImageToBuffer(IplImage* pImg);
	HBITMAP ConvertIplImageToHBITMAP(IplImage* pimg);
};

#ifndef _DEBUG  // отладочная версия в SimpleEditorView.cpp
inline CSimpleEditorDoc* CSimpleEditorView::GetDocument() const
   { return reinterpret_cast<CSimpleEditorDoc*>(m_pDocument); }
#endif

