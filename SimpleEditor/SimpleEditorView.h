
// SimpleEditorView.h : ��������� ������ CSimpleEditorView
//

#pragma once



class CSimpleEditorView : public CView
{
protected: // ������� ������ �� ������������
	CSimpleEditorView();
	DECLARE_DYNCREATE(CSimpleEditorView)
	
// ��������
public:
	CSimpleEditorDoc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����������
public:
	virtual ~CSimpleEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
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

#ifndef _DEBUG  // ���������� ������ � SimpleEditorView.cpp
inline CSimpleEditorDoc* CSimpleEditorView::GetDocument() const
   { return reinterpret_cast<CSimpleEditorDoc*>(m_pDocument); }
#endif

