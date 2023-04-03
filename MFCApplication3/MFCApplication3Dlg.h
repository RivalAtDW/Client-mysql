
// MFCApplication3Dlg.h: файл заголовка
//

#pragma once
constexpr auto ID_TIMER_1 = 200;

// Диалоговое окно CMFCApplication3Dlg


#include "Client.h"
//extern CMFCApplication3Dlg* pFrame;

#include <atlbase.h>


class CMFCApplication3Dlg : public CDialogEx
{
// Создание
public:
	HRESULT DrawJpg(CDC& hdc, CComPtr<IPicture>& m_pPicture, int CtrlId);
	CComPtr<IPicture> m_pPicture;
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// стандартный конструктор
	BOOL InitInstance();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
// Реализация
protected:

	HICON m_hIcon;
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	

	static bool ImRunAlready();
	//getting data about Employees, transformate these  keycode for comparison, and [mb in another method] after check count of Employees 
	//calculate whether new employees have appeared and add him
	bool AfterAppOpen();
	//correct closure of all entities
	static bool BeforeClosing();
	//помнить текущего пользователя
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CProgressCtrl m_progCtrl;
	CStatic ImageBox;
};
