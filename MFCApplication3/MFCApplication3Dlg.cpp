
// MFCApplication3Dlg.cpp: файл реализации
//
//MAKELONG macro keycode
#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "sal.h"
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Client.h"
#include <locale.h>

// Диалоговое окно CAboutDlg используется для описания сведений о приложении
const HANDLE mutex = CreateMutex(nullptr, FALSE,
	_T("{1234-5678-9HKJ-JKK0}"));
//Watcher Watcher;
Client MS_SQL_Server;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Диалоговое окно CMFCApplication3Dlg

CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1000, m_progCtrl);
	DDX_Control(pDX, IDC_STATIC_image, ImageBox);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication3Dlg::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
	//ON_WM_CTLCOLOR()
ON_WM_SIZE()
END_MESSAGE_MAP()

//88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
// Обработчики сообщений CMFCApplication3Dlg



BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	ShowWindow(SW_MINIMIZE);
	ShowWindow(SW_MAXIMIZE);//во время отладки мешает
	
	



	AfterAppOpen();
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

//88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication3Dlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication3Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CMFCApplication3Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


int CMFCApplication3Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CMFCApplication3Dlg::OnClose()
{
	CMFCApplication3Dlg::BeforeClosing();
	CDialogEx::OnClose();
}


void CMFCApplication3Dlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{

	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	
}


void CMFCApplication3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (MS_SQL_Server.m_Status.GetCurrentStatus()) {
	case condition::Status::CurrentStatus::WAIT4CUSTOMER:
	{
		if (MS_SQL_Server.WatchChangesInDB())
		{
			auto mutant = MS_SQL_Server.m_Customer.GetMutableKeyCode(MS_SQL_Server.m_Customer.GetKeyCode());
			if (MS_SQL_Server.ThisUserExist(mutant))
				{
				if (MS_SQL_Server.CheckDiscountThisUserToday(MS_SQL_Server.m_Customer.GetTabNumber()))
				{
					m_progCtrl.SetRange(0, 10);
					m_progCtrl.SetPos(0);
					SetDlgItemTextW(IDC_STATICtext1, _T("Ошибка - Пользователь уже пользовался скидкой сегодня, используйте код отмены для скрытия данного сообщения"));
					MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::WAIT4CASSIER_DC);
				}
				else
				{
					MS_SQL_Server.GetUserData(MS_SQL_Server.m_Customer.GetMutableKeyCode((MS_SQL_Server.m_Customer.GetKeyCode())));
					auto data = MS_SQL_Server.m_Customer.GetUserData();
					SetDlgItemTextW(IDC_STATICtext1, data);
					CImage CImg;
					CImg.Load(_T("client.jpg"));
					if (ImageBox.GetBitmap() == NULL)
						ImageBox.SetBitmap(HBITMAP(CImg));
					/* Then, later:
					 delete( _m_pCStatic_A );
					 delete( _m_pCStatic_B );
					 */



					m_progCtrl.SetRange(0, 600);
					m_progCtrl.SetPos(0);
					MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::WAIT4CASSIER_AD);
				}
			}
			else
			{
				CString str = _T("Пользователя с таким пропуском не существует. Обратитесь к системному администратору.");
				SetDlgItemTextW(IDC_STATICtext1, str);
				MS_SQL_Server.Aborting(str, false);
			}

		}//иначе нет изменений, не делаем ничего, ждем их
	}
	break;

	//предложение кассиру удалить запись о скидке сегодня
	case condition::Status::CurrentStatus::WAIT4CASSIER_DC:
	{
		auto cassierChoise = MS_SQL_Server.GetLatestCode();
		//10 секунд для решения
		short int i = 0;
		m_progCtrl.SetRange(0, 10);
		while ( cassierChoise != MS_SQL_Server.NOCODE)
		{
			if (i == 10) {
			
				cassierChoise = MS_SQL_Server.NOCODE;
				m_progCtrl.SetRange(0, 600);
				break;
			}
			Sleep(1000);
			++i;
			m_progCtrl.SetPos(m_progCtrl.GetPos() + 1);
			cassierChoise = MS_SQL_Server.GetLatestCode();
		}
		if (cassierChoise == MS_SQL_Server.NOCODE) {

			m_progCtrl.SetRange(0, 600);
			m_progCtrl.SetPos(0);
			//MS_SQL_Server.m_Status.ChangeCurrentStatus(Client::Status::CurrentStatus::WAIT4CUSTOMER); 
			CString str = _T("Отказ кассира");
			SetDlgItemTextW(IDC_STATICtext1, str);
			MS_SQL_Server.Aborting(str, false);
			
		}
	}
	break;
	//подтверждение или отказ предоставлять скидку
	case condition::Status::CurrentStatus::WAIT4CASSIER_AD: {
		//if Pos >=600...
		constexpr auto YesCode = 524296;
		constexpr auto NoCode = 589833;
		auto latestCode = MS_SQL_Server.GetLatestCode();

		switch (latestCode)
		{
		case YesCode:
		{
			CString SqlDate = file::Log::GetTimeNow('.');
			
			CString sqlAdd = _T("INSERT INTO [FSI-Test].[dbo].[Discounts] ([TabNumber], EventTime) VALUES (") + MS_SQL_Server.m_Customer.GetTabNumber() + _T(", '") + SqlDate + _T("')");
			try
			{
				file::Log::WriteLog(_T("EXECUTING... :") + sqlAdd);
				MS_SQL_Server.ExecuteSQL(sqlAdd);
			}
			catch (CDBException& e)

			{
				file::Log::WriteLog(e.m_strError);
				e.Delete();
				AfxMessageBox(_T("Ошибка выборки данных, обратитесь к системному администратору"));
			}
			m_progCtrl.SetPos(0);
			SetDlgItemTextW(IDC_STATICtext1, _T("Скидка подтверждена"));
			SetDlgItemTextW(IDC_STATIC_text0, _T(""));
			MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::MESSAGEDELAY);
		}
		break;
		case NoCode:
		{
			CString str = _T("\tСкидка не предоставлена по решению кассира");
			SetDlgItemTextW(IDC_STATICtext1, str);
			MS_SQL_Server.Aborting(str, false);
			m_progCtrl.SetPos(0);
			MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::MESSAGEDELAY);

		}
		break;
		default:
		{

			if (m_progCtrl.GetPos() < 600) {
				m_progCtrl.SetPos(m_progCtrl.GetPos() + 1);
			}
			else
			{
				try
				{
					CString str = _T("Скидка не предоставлена по решению кассира");
					SetDlgItemTextW(IDC_STATICtext1, str);
					MS_SQL_Server.Aborting(str, false);
					m_progCtrl.SetPos(0);
					//auto status = MS_SQL_Server.GetStatus();
					MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::MESSAGEDELAY);
				}
				catch (CDBException& e)
				{
					file::Log::WriteLog(e.m_strError);
					e.Delete();
				}
			}
		}
		break;
		}
	}	break;

	case condition::Status::CurrentStatus::MESSAGEDELAY:
	{
		if (ImageBox.GetBitmap() != NULL)
			ImageBox.SetBitmap(NULL);
		m_progCtrl.SetRange(0, 3);
		m_progCtrl.SetPos(0);

		for (size_t i = 0; i < 3; i++)
		{
			m_progCtrl.SetPos(m_progCtrl.GetPos() + 1);
			Sleep(1000);

		}
		m_progCtrl.SetRange(0, 600);
		m_progCtrl.SetPos(0);
		CString str = _T("Ожидание клиента");
		SetDlgItemTextW(IDC_STATICtext1, str);
		
		MS_SQL_Server.m_Status.ChangeCurrentStatus(condition::Status::CurrentStatus::WAIT4CUSTOMER);
	}
	break;
	case condition::Status::CurrentStatus::STRESSQUIT:
	{
		///_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(9554);
		//_CrtSetBreakAlloc(9553);
		//_CrtSetBreakAlloc(9552);

		BeforeClosing();
		PostQuitMessage(3);
	}
	break;
	default:
		break;

	}	
}


void CMFCApplication3Dlg::OnSize(UINT nType, int cx, int cy)
{
	CMFCApplication3Dlg::ImRunAlready();
	CDialogEx::OnSize(nType, cx, cy);
}

//здесь изменяется начальное состояние формы сразу после запуска
bool CMFCApplication3Dlg::AfterAppOpen()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	SetDlgItemTextW(IDC_STATIC_text0, _T("\tДобро пожаловать"));
	SetDlgItemTextW(IDC_STATICtext1, _T("\tОжидание клиента"));
	MS_SQL_Server.ConnectToDB();
	SetTimer(ID_TIMER_1, 1000, nullptr);
	return false;
}

//манипуляции, необходимые для выполнения перед выходом из программы
bool CMFCApplication3Dlg::BeforeClosing()
{
	ReleaseMutex(mutex);
	CloseHandle(mutex);
	MS_SQL_Server.DisconnectFromDB();
	return false;
}

//если приложение уже запущено, то выведется окно с уведомлением и программа завершит свою работу -
//не будет возможности одновременной работы нескольких экземпляров программы
bool CMFCApplication3Dlg::ImRunAlready()
{
	DWORD result = WaitForSingleObject(mutex, 0);
	if (result != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("Возможна работа только одной копии приложения"));
		PostQuitMessage(2);
	}
	return false;
}