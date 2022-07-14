#include "stdafx.h"
#include "Resource.h"
#include "TrayMenu.h"
#include "LoginKit.h"

//****************************/
//-- namespace NS_TrayMenu
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_TrayMenu_BEGIN	namespace NS_TrayMenu {
#define NS_TrayMenu_END		}
#define USING_NS_TrayMenu	using namespace NS_TrayMenu

NS_TrayMenu_BEGIN

//-- 控件名称
CONST PWSTR XML0_SkinFile	= L"tray_menu0.xml";
CONST PWSTR WGT0_login		= L"login";			// menu_element: 登录
CONST PWSTR WGT0_website	= L"website";		// menu_element: 访问官网
CONST PWSTR WGT0_quit		= L"quit";			// menu_element: 退出

CONST PWSTR XML1_SkinFile	= L"tray_menu1.xml";
CONST PWSTR WGT1_about		= L"about";			// menu_element: 关于
CONST PWSTR WGT1_logout		= L"logout";		// menu_element: 注销
CONST PWSTR WGT1_quit		= L"quit";			// menu_element: 退出

NS_TrayMenu_END
USING_NS_TrayMenu;

//****************************/
//-- class TrayMenu
//****************************/
//////////////////////////////////////////////////////////////////////////

TrayMenu::TrayMenu()
	: m_pTray(NULL)
	, m_hCurrWnd(NULL)
	, m_bLogined(false)
	, m_cb_Quit(NULL)
{

}

TrayMenu::~TrayMenu()
{
	Destroy();
}

bool TrayMenu::Create(
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	LPCWSTR lpStrRegWnd,
	LPCWSTR lpMenuTip)
{
	if (m_pTray == NULL)
	{
		m_pTray = new ui_comp::TrayIcon();
		if (m_pTray == NULL)
		{
			return false;
		}
		HICON hIcon = (HICON)::LoadIconW(::GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_TEST_DEMO));
		m_pTray->Init(this, lpClassName, lpWindowName, lpStrRegWnd);
		if (m_pTray->SetTrayIcon(hIcon, lpMenuTip) == FALSE)
		{
			m_pTray->Destroy();
			delete m_pTray;
			m_pTray = NULL;
			return false;
		}
	}
	return true;
}

void TrayMenu::Destroy()
{
	if (m_pTray)
	{
		m_pTray->Destroy();
		delete m_pTray;
		m_pTray = NULL;
	}
	m_hCurrWnd = NULL;
	m_bLogined = false;
	m_cb_Quit = NULL;
}

bool TrayMenu::Update(
	HWND hCurrWnd,
	bool bLogined,
	const Callback_Quit& cb_Quit)
{
	if (m_pTray == NULL) {
		return false;
	}
	m_hCurrWnd = hCurrWnd;
	m_bLogined = bLogined;
	m_cb_Quit = cb_Quit;
	return true;
}

void TrayMenu::OnLeftClick()
{
	ActiveWnd();
}

void TrayMenu::OnRightClick()
{
	if (::IsWindow(m_hCurrWnd))
	{
		POINT point;
		::GetCursorPos(&point);
		m_bLogined ? PopupMenu1(point) : PopupMenu0(point);
	}
}

void TrayMenu::PopupMenu0(POINT point)
{
 	ui_comp::MenuWnd* pMenu = new ui_comp::MenuWnd();
 	pMenu->Init(XML0_SkinFile, point, ui_comp::MenuWnd::ePopupRT);
	{
		ui_comp::MenuElementUI* pLogin   = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT0_login);
		ui_comp::MenuElementUI* pWebsite = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT0_website);
		ui_comp::MenuElementUI* pQuit    = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT0_quit);

		pLogin->AttachSelect(std::bind<bool>(&TrayMenu::Cb_ActiveWnd, this, std::placeholders::_1));
		pWebsite->AttachSelect(std::bind<bool>(&TrayMenu::Cb_Website, this, std::placeholders::_1));
		pQuit->AttachSelect(std::bind<bool>(&TrayMenu::Cb_Quit, this, std::placeholders::_1));
	}
 	pMenu->Show();
}

void TrayMenu::PopupMenu1(POINT point)
{
 	ui_comp::MenuWnd* pMenu = new ui_comp::MenuWnd();
 	pMenu->Init(XML1_SkinFile, point, ui_comp::MenuWnd::ePopupRT);
	{
		ui_comp::MenuElementUI* pAbout  = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT1_about);
		ui_comp::MenuElementUI* pLogout = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT1_logout);
		ui_comp::MenuElementUI* pQuit   = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT1_quit);

		pAbout->AttachSelect(std::bind<bool>(&TrayMenu::Cb_About, this, std::placeholders::_1));
		pLogout->AttachSelect(std::bind<bool>(&TrayMenu::Cb_Logout, this, std::placeholders::_1));
		pQuit->AttachSelect(std::bind<bool>(&TrayMenu::Cb_Quit, this, std::placeholders::_1));
	}
 	pMenu->Show();
}

bool TrayMenu::Cb_ActiveWnd(ui::EventArgs*)
{
	ActiveWnd();
	return true;
}

bool TrayMenu::Cb_Website(ui::EventArgs*)
{
	ui_comp::MsgBox::Show(nullptr, nullptr, L"官网", L"提示", L"知道了", L"");
	return true;
}

bool TrayMenu::Cb_About(ui::EventArgs*)
{
	ui_comp::MsgBox::Show(nullptr, nullptr, L"关于", L"提示", L"知道了", L"");
	return true;
}

bool TrayMenu::Cb_Logout(ui::EventArgs*)
{
	LoginKit::GetInstance()->DoLogout();
	return true;
}

bool TrayMenu::Cb_Quit(ui::EventArgs*)
{
	Invoke_Quit();
	return true;
}

void TrayMenu::ActiveWnd()
{
	HWND hWnd = m_hCurrWnd;
	if (::IsWindow(hWnd))
	{
		HWND hEnabledPopup = ::GetWindow(hWnd, GW_ENABLEDPOPUP);
		if (hEnabledPopup && ::IsWindow(hEnabledPopup))
		{
			if (::IsWindowVisible(hEnabledPopup) == FALSE) {
				::ShowWindow(hEnabledPopup, SW_SHOW);
			}
			::SetForegroundWindow(hEnabledPopup);
			::BringWindowToTop(hEnabledPopup);
			::SendMessage(hEnabledPopup, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else if (::IsWindowEnabled(hWnd))
		{
			if (::IsWindowVisible(hWnd) == FALSE) {
				::ShowWindow(hWnd, SW_SHOW);
			}
			::SetForegroundWindow(hWnd);
			::BringWindowToTop(hWnd);
			::SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
	}
}

void TrayMenu::Invoke_Quit()
{
	try {
		if (m_cb_Quit && ::IsWindow(m_hCurrWnd)) {
			m_cb_Quit();
		}
	}
	catch (const std::exception&) {}
}
