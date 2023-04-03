
// MFCApplication3.cpp: определяет поведение классов для приложения.

#pragma warning( push )
#pragma warning( disable : 4002)
// Your function
#pragma warning( pop ) 
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE(HWND);

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "resource.h"	
#include "afxdb.h"
#include "odbcinst.h"
#include <time.h>
#include "Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CMFCApplication3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CMFCApplication3App
CMFCApplication3App::CMFCApplication3App()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CWnd* CMFCApplication3App::GetDlg()
{
	return m_pMainWnd;
}

// Единственный объект CMFCApplication3App
CMFCApplication3App theApp;
// Инициализация CMFCApplication3App
BOOL CMFCApplication3App::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;
	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры

	SetRegistryKey(_T("MORION"));
	CMFCApplication3Dlg dlg;
	m_pMainWnd = &dlg;
	/**/
	INT_PTR nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	
	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

void CMFCApplication3App::LoadImageInForm(CLongBinary* Photo)
{
	CComPtr<IStream> pStream;
	IPicture* m_IPicture = NULL;
	try {
		}
	catch (CDBException& e)
	{
		AfxMessageBox(e.m_strError);
	}

	if (m_IPicture)
	{
		m_IPicture->Release();
		m_IPicture = NULL;
		//pStream->Release();
	}
}

