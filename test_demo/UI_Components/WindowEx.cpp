#include "stdafx.h"
#include "WindowEx.h"
#include "WindowExMgr.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class WindowEx
//****************************/
//////////////////////////////////////////////////////////////////////////

WindowEx::WindowEx()
{

}

WindowEx::~WindowEx()
{

}

HWND WindowEx::Create(
	HWND hwndParent,
	LPCTSTR pstrName,
	DWORD dwStyle,
	DWORD dwExStyle,
	bool isLayeredWindow /*= true*/,
	const ui::UiRect& rc /*= ui::UiRect(0, 0, 0, 0)*/)
{
	if (!RegisterWnd()) {
		return NULL;
	}
	HWND hwnd = __super::Create(hwndParent, pstrName, dwStyle, dwExStyle, isLayeredWindow, rc);
	ASSERT(hwnd);
	return hwnd;
}

LRESULT WindowEx::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UnRegisterWnd();
	return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
}

void WindowEx::OnEsc(BOOL &bHandled)
{
	bHandled = FALSE;
}

LRESULT WindowEx::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE)
	{
		if (::IsWindowEnabled(m_hWnd) == FALSE) {
			::SetForegroundWindow(m_hWnd);
			return FALSE;
		}
	}
	else if (uMsg == WM_KILLFOCUS)
	{
		KillFocus();
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_ESCAPE)
		{
			BOOL bHandled = FALSE;
			OnEsc(bHandled);
			if (!bHandled) {
				this->Close();
			}
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool WindowEx::RegisterWnd()
{
	std::wstring wnd_class_name = GetWindowClassName();
	std::wstring wnd_id = GetWindowId();
	return WindowExMgr::GetInstance()->RegisterWindow(wnd_class_name, wnd_id, this);
}

void WindowEx::UnRegisterWnd()
{
	std::wstring wnd_class_name = GetWindowClassName();
	std::wstring wnd_id = GetWindowId();
	WindowExMgr::GetInstance()->UnRegisterWindow(wnd_class_name, wnd_id, this);
}

NS_UI_COMP_END