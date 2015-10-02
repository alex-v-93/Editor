
// ChildFrm.h : интерфейс класса CChildFrame
//

#pragma once

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Атрибуты
public:

// Операции
public:

// Переопределение
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};
