#include "stdafx.h"
#include "tray_icon.h"
#include <shellapi.h>

NS_UI_COMP_BEGIN

#define	TRAYICON_ID			1
#define WM_TRAYICON_NOTIFY	(WM_USER + 1)

//****************************/
//-- namespace NS_tray_icon
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_tray_icon_BEGIN	namespace NS_tray_icon {
#define NS_tray_icon_END	}
#define USING_NS_tray_icon	using namespace NS_tray_icon

NS_tray_icon_BEGIN

// 所有托盘图标管理类 // map<窗口句柄, 管理类指针>
std::mutex g_mutexTray;
std::map<HWND, TrayIcon*> g_mapTray;

// 增
void _insert_tray(HWND hWnd, TrayIcon* pTray)
{
	std::lock_guard<std::mutex> lock(g_mutexTray);
	auto iter = g_mapTray.find(hWnd);
	if (iter == g_mapTray.end()) {
		g_mapTray.insert(std::make_pair(hWnd, pTray));
	}
}
// 删
void _delete_tray(HWND hWnd)
{
	std::lock_guard<std::mutex> lock(g_mutexTray);
	auto iter = g_mapTray.find(hWnd);
	if (iter != g_mapTray.end()) {
		g_mapTray.erase(iter);
	}
}
// 查
TrayIcon* _select_tray(HWND hWnd)
{
	std::lock_guard<std::mutex> lock(g_mutexTray);
	auto iter = g_mapTray.find(hWnd);
	if (iter != g_mapTray.end()) {
		return iter->second;
	}
	return NULL;
}

NS_tray_icon_END
USING_NS_tray_icon;

//****************************/
//-- class TrayIcon
//****************************/
//////////////////////////////////////////////////////////////////////////

TrayIcon::TrayIcon()
	: m_hWnd(NULL)
	, m_pDelegate(NULL)
	, m_uMsgID(0)
	, m_bAdded(FALSE)
	, m_hIcon(NULL)
	, m_wstrTip(L"")
{

}

TrayIcon::~TrayIcon()
{
	_delete_tray(m_hWnd);
}

void TrayIcon::Init(
	TrayIconDelegate* pDelegate,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	LPCWSTR lpStrRegWnd)
{
	if (m_hWnd) {
		return;
	}

	HINSTANCE hInstance = ::GetModuleHandleW(NULL);
	WNDCLASSW wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = NULL;
	wc.hCursor       = ::LoadCursorW(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = lpClassName;
	::RegisterClassW(&wc);

	m_hWnd = ::CreateWindowExW(NULL, lpClassName, lpWindowName, WS_POPUP | WS_CHILD, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
	m_pDelegate = pDelegate;
	m_uMsgID = ::RegisterWindowMessageW(lpStrRegWnd);

	_insert_tray(m_hWnd, this);
}

void TrayIcon::Destroy()
{
	NOTIFYICONDATAW nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATAW);
	nid.uFlags = 0;
	nid.hWnd   = m_hWnd;
	nid.uID    = TRAYICON_ID;

	::Shell_NotifyIconW(NIM_DELETE, &nid);
	_delete_tray(m_hWnd);
}

BOOL TrayIcon::SetTrayIcon(
	HICON hIcon,
	const std::wstring& wstrTip)
{
	m_hIcon = hIcon;
	m_wstrTip = wstrTip;
	return ModifyTrayIcon(TRAYICON_ID, WM_TRAYICON_NOTIFY, hIcon, wstrTip);
}

LRESULT TrayIcon::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = 1;
	switch (uMsg)
	{
	case WM_TRAYICON_NOTIFY:
		if (TRAYICON_ID == wParam)
		{
			try {
				TrayIcon* pTray = _select_tray(hWnd);
				if (pTray) {
					pTray->Proc(lParam);
				}
			}
			catch (const std::exception&) {}
		}
		break;
	default:
		if (uMsg != 0)
		{
			try {
				TrayIcon* pTray = _select_tray(hWnd);
				if (pTray && pTray->m_uMsgID == uMsg) {
					pTray->RestoreTrayIcon();
				}
			}
			catch (const std::exception&) {}
		}
		lRet = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return lRet;
}

void TrayIcon::Proc(LPARAM lParam)
{
	if (m_pDelegate == NULL) {
		return;
	}
	switch (lParam)
	{
	case WM_LBUTTONUP:
		m_pDelegate->OnLeftClick();
		break;
	case WM_LBUTTONDBLCLK:
		m_pDelegate->OnLeftDoubleClick();
		break;
	case WM_RBUTTONUP:
		m_pDelegate->OnRightClick();
		break;
	case WM_RBUTTONDBLCLK:
		m_pDelegate->OnRightDoubleClick();
		break;
	default:
		break;
	}
}

BOOL TrayIcon::RestoreTrayIcon()
{
	if (!::IsWindow(m_hWnd)) {
		return FALSE;
	}
	m_bAdded = FALSE;
	return ModifyTrayIcon(TRAYICON_ID, WM_TRAYICON_NOTIFY, m_hIcon, m_wstrTip);
}

BOOL TrayIcon::ModifyTrayIcon(
	UINT uID,
	DWORD dwMsg,
	HICON hIcon,
	const std::wstring& wstrTip)
{
	NOTIFYICONDATAW nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATAW);
	nid.hWnd   = m_hWnd;
	nid.uID    = uID;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = dwMsg;
	nid.hIcon  = hIcon;
	wcscpy_s(nid.szTip, 128, wstrTip.c_str());

	BOOL bRet = FALSE;
	if (m_bAdded) {
		bRet = ::Shell_NotifyIconW(NIM_MODIFY, &nid);
	}
	else {
		// 在极端情况下有可能会安装托盘失败，这里最多尝试2次安装
		for (int i = 0; i < 2; ++i)
		{
			if (::Shell_NotifyIconW(NIM_ADD, &nid)) {
				m_bAdded = bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

NS_UI_COMP_END