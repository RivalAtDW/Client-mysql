
// MFCApplication3.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include "string"
#include "afxdb.h"


// CMFCApplication3App:
// Сведения о реализации этого класса: MFCApplication3.cpp
//


class CMFCApplication3App : public CWinApp
{
public:
	CMFCApplication3App();
	CWnd* GetDlg();
	
// Переопределение

	virtual BOOL InitInstance();
	static void LoadImageInForm(CLongBinary* Photo);
// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication3App theApp;
