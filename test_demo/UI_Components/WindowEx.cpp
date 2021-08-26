#include "stdafx.h"
#include "WindowEx.h"
#include "WindowExMgr.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class WindowEx
//****************************/
//////////////////////////////////////////////////////////////////////////

HWND WindowEx::Create(
	HWND hwndParent,
	LPCTSTR pstrName,
	DWORD dwStyle,
	DWORD dwExStyle,
	bool isLayeredWindow /*= true*/,
	const ui::UiRect& rc /*= ui::UiRect(0, 0, 0, 0)*/)
{
	if (!WindowExMgr::GetInstance()->RegisterWindow(m_wnd_class_name, m_wnd_id, this)) {
		return NULL;
	}
	return __super::Create(hwndParent, pstrName, dwStyle, dwExStyle, isLayeredWindow, rc);
}

LRESULT WindowEx::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WindowExMgr::GetInstance()->UnRegisterWindow(m_wnd_class_name, m_wnd_id, this);
	return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
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

void WindowEx::OnEsc(BOOL &bHandled)
{
	bHandled = FALSE;
}

NS_UI_COMP_END