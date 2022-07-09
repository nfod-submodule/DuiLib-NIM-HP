#include "stdafx.h"
#include "shadow_wnd.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class ShadowWnd
//****************************/
//////////////////////////////////////////////////////////////////////////

HWND ShadowWnd::CreateEx(Window* pWndBase)
{
	m_pWndBase = pWndBase;
	return Window::Create(NULL, ConfUI_Components::Shadow_ClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW, true);
}

LRESULT ShadowWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pWndBase == NULL ||
		m_pWndBase->GetHWND() == NULL) {
		return FALSE;
	}

	switch (uMsg)
	{
	case WM_ERASEBKGND:
	case WM_PAINT:
	case WM_MOVE:
	case WM_ACTIVATE:
	case WM_NCACTIVATE:
		if (::IsWindowVisible(m_pWndBase->GetHWND())) {
			RECT rc;
			::GetWindowRect(m_pWndBase->GetHWND(), &rc);
			this->SetPos(rc, false, SWP_SHOWWINDOW | SWP_NOACTIVATE, m_pWndBase->GetHWND());
		}
		break;
	case WM_CLOSE:
		this->ShowWindow(false, false);
		this->Close(0);
		break;
	case WM_SHOWWINDOW:
		this->ShowWindow(wParam == 0 ? false : true, false);
		break;
	default:
		break;
	}

	bHandled = FALSE;
	return FALSE;
}

NS_UI_COMP_END