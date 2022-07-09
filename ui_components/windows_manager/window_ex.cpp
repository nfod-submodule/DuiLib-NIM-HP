#include "stdafx.h"
#include "window_ex.h"
#include "windows_manager.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class WindowEx
//****************************/
//////////////////////////////////////////////////////////////////////////

void WindowEx::Close(UINT nRet /*= IDOK*/)
{
	// 窗口关闭之前先Enable父窗口，防止父窗口隐到后面去。
	HWND hWndParent = GetWindowOwner(GetHWND());
	if (hWndParent) {
		::EnableWindow(hWndParent, TRUE);
		::SetFocus(hWndParent);
	}
	__super::Close(nRet);
}

HWND WindowEx::Create(
	HWND hWndParent,
	LPCTSTR pstrName,
	DWORD dwStyle,
	DWORD dwExStyle,
	bool isLayeredWindow /*= true*/,
	const ui::UiRect& rc /*= ui::UiRect(0, 0, 0, 0)*/)
{
	if (!WindowExMgr::GetInstance()->RegisterWindow(m_ClassName, m_WindowId, this)) {
		return NULL;
	}
	if (m_CtrlFL & FL_N_LAYERED) {
		isLayeredWindow = false;
	}
	HWND hWnd = __super::Create(hWndParent, pstrName, dwStyle, dwExStyle, isLayeredWindow, rc);
	if (m_CtrlFL & FL_SHADOWWND && !this->IsShadowAttached()) {
		if (m_pShadowWnd == nullptr) {
			m_pShadowWnd = new ShadowWnd();
			this->AddMessageFilter(m_pShadowWnd);
			m_pShadowWnd->CreateEx(this);
			::EnableWindow(m_pShadowWnd->GetHWND(), FALSE);
			if (::IsWindowVisible(hWnd)) {
				m_pShadowWnd->ShowWindow();
			}
		}
	}
	return hWnd;
}

LRESULT WindowEx::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_CtrlFL & FL_QUIT) {
		::PostQuitMessage(0L);
	}
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT WindowEx::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WindowExMgr::GetInstance()->UnregisterWindow(m_ClassName, m_WindowId, this);
	return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
}

LRESULT WindowEx::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE)
	{
		if (::IsWindowEnabled(GetHWND()) == FALSE) {
			::SetForegroundWindow(GetHWND());
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
			if (m_CtrlFL & FL_ESC_CLOSE) {
				this->Close();
			}
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

NS_UI_COMP_END