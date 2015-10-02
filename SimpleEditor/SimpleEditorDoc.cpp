#pragma once
// SimpleEditorDoc.cpp : реализация класса CSimpleEditorDoc
//

#include "stdafx.h"

// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SimpleEditor.h"
#endif

#include "SimpleEditorDoc.h"

#include <propkey.h>
#include <Gdiplus.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSimpleEditorDoc

IMPLEMENT_DYNCREATE(CSimpleEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleEditorDoc, CDocument)
	ON_COMMAND(ID_TEST_PLUS, &CSimpleEditorDoc::OnTestPlus)
	ON_COMMAND(ID_TEST_MINUS, &CSimpleEditorDoc::OnTestMinus)
	ON_COMMAND(ID_EXPO, &CSimpleEditorDoc::OnExpo)
	ON_COMMAND(ID_CONTRAST, &CSimpleEditorDoc::OnContrast)
	ON_COMMAND(ID_SATURE, &CSimpleEditorDoc::OnSature)
	ON_COMMAND(ID_CLAR, &CSimpleEditorDoc::OnClar)
	ON_COMMAND(ID_WHITE, &CSimpleEditorDoc::OnWhite)
	ON_COMMAND(ID_SHADOW, &CSimpleEditorDoc::OnShadow)
	ON_COMMAND(ID_HUE, &CSimpleEditorDoc::OnHue)
	ON_COMMAND(ID_TEMP, &CSimpleEditorDoc::OnTemp)
	ON_UPDATE_COMMAND_UI(ID_EXPO, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_CONTRAST, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_SATURE, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_CLAR, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_WHITE, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_SHADOW, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_HUE, &CSimpleEditorDoc::OnUpdateCheck)
	ON_UPDATE_COMMAND_UI(ID_TEMP, &CSimpleEditorDoc::OnUpdateCheck)
	ON_COMMAND(ID_PLUS, &CSimpleEditorDoc::OnPlus)
	ON_COMMAND(ID_MINUS, &CSimpleEditorDoc::OnMinus)
END_MESSAGE_MAP()


// создание/уничтожение CSimpleEditorDoc

CSimpleEditorDoc::CSimpleEditorDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSimpleEditorDoc::~CSimpleEditorDoc()
{
	//if (m_spImage != nullptr)
	//	delete m_spImage;
}

BOOL CSimpleEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// сериализация CSimpleEditorDoc

void CSimpleEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSimpleEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSimpleEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSimpleEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CSimpleEditorDoc

void CSimpleEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

BOOL CSimpleEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	CStringA pathA(lpszPathName);
	try
	{
		m_spImage = make_shared<CImageEditor>(CString(lpszPathName));
		//String s(pathA);

		//m_spImage = make_shared<Mat>(imread(s));
		//cv::imwrite(String("D:\\TMP\\1.jpg"), *m_spImage);
		//m_spBitmap = make_shared<Gdiplus::Bitmap>(lpszPathName);
		//IplImage img = ;
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
	return TRUE;
}

BOOL CSimpleEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CStringA pathA(lpszPathName);
	if (m_spImage)
		m_spImage->Save(lpszPathName);
	//cvSaveImage(pathA, m_spImage.get());
	return TRUE;
}



// команды CSimpleEditorDoc


void CSimpleEditorDoc::OnTestPlus()
{
	try
	{
		if (m_spImage)
		{
			m_spImage->IncrementValues();
			this->UpdateAllViews(nullptr);
			//m_spBitmap->ApplyEffect()
		}
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}


void CSimpleEditorDoc::OnTestMinus()
{
	try
	{
		if (m_spImage)
		{
			m_spImage->DecrementValues();
			this->UpdateAllViews(nullptr);
		}
	}
	catch (CMemoryException* e)
	{
		throw;
	}
	catch (CFileException* e)
	{
		throw;
	}
	catch (CException* e)
	{
		throw;
	}
}


void CSimpleEditorDoc::OnExpo()
{
	if (m_spImage)
	{
		
		m_spImage->InverseState(ImageEditType::Expo);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnContrast()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Contrast);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnSature()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Sature);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnClar()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Clarity);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnWhite()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::White);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnShadow()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Shadow);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnHue()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Hue);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnTemp()
{
	if (m_spImage)
	{
		m_spImage->InverseState(ImageEditType::Temperature);
		this->UpdateAllViews(nullptr);
	}
}


void CSimpleEditorDoc::OnUpdateCheck(CCmdUI *pCmdUI)
{
	ImageEditType type;
	if (pCmdUI->m_nID == ID_EXPO)
		type = ImageEditType::Expo;
	else if (pCmdUI->m_nID == ID_SATURE)
		type = ImageEditType::Sature;
	else if (pCmdUI->m_nID == ID_CONTRAST)
		type = ImageEditType::Contrast;
	else if (pCmdUI->m_nID == ID_CLAR)
		type = ImageEditType::Clarity;
	else if (pCmdUI->m_nID == ID_HUE)
		type = ImageEditType::Hue;
	else if (pCmdUI->m_nID == ID_TEMP)
		type = ImageEditType::Temperature;
	else if (pCmdUI->m_nID == ID_WHITE)
		type = ImageEditType::White;
	else if (pCmdUI->m_nID == ID_SHADOW)
		type = ImageEditType::Shadow;
	if (m_spImage)
		pCmdUI->SetCheck(m_spImage->GetState(type) ? 1 : 0);
}

void CSimpleEditorDoc::OnPlus()
{
	OnTestPlus();
}


void CSimpleEditorDoc::OnMinus()
{
	OnTestMinus();
}
