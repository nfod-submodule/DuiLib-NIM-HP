#include "stdafx.h"
#include "ui_menu.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class MenuWnd
//****************************/
//////////////////////////////////////////////////////////////////////////

ui::Control* MenuWnd::CreateControl(const std::wstring& pstrClass)
{
	if (pstrClass == L"MenuElement") {
		return new MenuElementUI();
	}
	return NULL;
}

LRESULT MenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KILLFOCUS)
	{
		Close();
		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_ESCAPE) {
			Close();
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MenuWnd::Init(const std::wstring& xmlSkinFile, POINT basedPoint, EPopupPosType popupPosType, bool no_focus)
{
	m_xmlSkinFile = xmlSkinFile;
	m_basedPoint = basedPoint;
	m_popupPosType = popupPosType;
	m_no_focus = no_focus;

	__super::Create(m_hParent, L"MENUWND", WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_TOPMOST, true, ui::UiRect());
	// HACK: Don't deselect the parent's caption
	HWND hWndParent = m_hWnd;
	while (::GetParent(hWndParent) != NULL) {
		hWndParent = ::GetParent(hWndParent);
	}
	::ShowWindow(m_hWnd, no_focus ? SW_SHOWNOACTIVATE : SW_SHOW);
	::SetWindowPos(m_hWnd, NULL, m_basedPoint.x, m_basedPoint.y, 0, 0, SWP_NOSIZE | (no_focus ? SWP_NOACTIVATE : 0));
	::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

void MenuWnd::Show()
{
	MONITORINFO monitor_info = {}; monitor_info.cbSize = sizeof(monitor_info);
	::GetMonitorInfo(::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTOPRIMARY), &monitor_info);
	ui::UiRect rcWork = monitor_info.rcWork;
	ui::UiRect monitor_rect = monitor_info.rcMonitor;

	ui::CSize szInit = { rcWork.right - rcWork.left, rcWork.bottom - rcWork.top };
	szInit = GetRoot()->EstimateSize(szInit);
	szInit.cx -= GetShadowCorner().left + GetShadowCorner().right;
	szInit.cy -= GetShadowCorner().top  + GetShadowCorner().bottom;

	switch (m_popupPosType) {
	case ePopupRB:
		if (m_basedPoint.y + szInit.cy > monitor_rect.bottom) {
			m_basedPoint.y -= szInit.cy;
		}
		break;
	case ePopupRT:
		if (m_basedPoint.y - szInit.cy >= monitor_rect.top) {
			m_basedPoint.y -= szInit.cy;
		}
		break;
	}

	ui::UiRect rc;
	rc.left = m_basedPoint.x;
	rc.top  = m_basedPoint.y;
	if (rc.top < monitor_rect.top) {
		rc.top = monitor_rect.top;
	}
	if (rc.left > monitor_rect.right - szInit.cx) {
		rc.left = monitor_rect.right - szInit.cx;
	}
	if (rc.left < monitor_rect.left) {
		rc.left = monitor_rect.left;
	}
	rc.right = rc.left + szInit.cx;
	rc.bottom = rc.top + szInit.cy;

	SetPos(rc, false, SWP_SHOWWINDOW | (m_no_focus ? SWP_NOACTIVATE : 0), HWND_TOPMOST, false);
	if (m_no_focus == false) {
		SetForegroundWindow(m_hWnd);
	}
}

NS_UI_COMP_END