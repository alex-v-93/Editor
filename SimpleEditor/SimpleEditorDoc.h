
// SimpleEditorDoc.h : интерфейс класса CSimpleEditorDoc
//


#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "ImageEditor.h"
class CSimpleEditorDoc : public CDocument
{
protected: // создать только из сериализации
	CSimpleEditorDoc();
	DECLARE_DYNCREATE(CSimpleEditorDoc)
	shared_ptr<CImageEditor> m_spImage;
	std::shared_ptr<Bitmap> m_spBitmap;
// Атрибуты
public:

// Операции
public:
	shared_ptr<Mat> GetImage() { return m_spImage->GetImage(); }
	
	Bitmap* GetBitmap() { return m_spBitmap.get(); }

// Переопределение
public:
	//virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSimpleEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName) override;

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName) override;
#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);



#endif // SHARED_HANDLERS
public:
	afx_msg void OnTestPlus();
	afx_msg void OnTestMinus();
	afx_msg void OnExpo();
	afx_msg void OnContrast();
	afx_msg void OnSature();
	afx_msg void OnClar();
	afx_msg void OnWhite();
	afx_msg void OnShadow();
	afx_msg void OnHue();
	afx_msg void OnTemp();
	afx_msg void OnUpdateCheck(CCmdUI *pCmdUI);
	afx_msg void OnPlus();
	afx_msg void OnMinus();
};
