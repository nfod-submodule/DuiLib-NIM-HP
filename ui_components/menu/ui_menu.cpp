#include "stdafx.h"
#include "ui_menu.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class MenuWnd
//****************************/
//////////////////////////////////////////////////////////////////////////

void MenuWnd::Init(
	const std::wstring& xmlSkinFile,
	POINT base_point,
	EPopupPosType ePopup,
	bool no_focus,
	MenuElementUI* pOwner /*= NULL*/)
{
	m_xmlSkinFile = xmlSkinFile;
	m_base_point = base_point;
	m_ePopup = ePopup;
	m_no_focus = no_focus;
	m_pOwner = pOwner;

	GetMenuObserver().AddReceiver(this);

	const std::wstring& wnd_class_name = GetWindowClassName();
	this->Create(m_hParent, wnd_class_name.c_str(), WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_TOPMOST);

	// HACK: Don't deselect the parent's caption
	HWND hWndParent = GetHWND();
	while (::GetParent(hWndParent) != NULL) {
		hWndParent = ::GetParent(hWndParent);
	}
	::ShowWindow(GetHWND(), no_focus ? SW_SHOWNOACTIVATE : SW_SHOW);
	if (m_pOwner) {
		ResizeSubMenu();
	}
	else {
		ResizeMenu();
	}
	::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

void MenuWnd::Show()
{
	MONITORINFO mi = {};
	mi.cbSize = sizeof(mi);
	::GetMonitorInfo(::MonitorFromWindow(GetHWND(), MONITOR_DEFAULTTOPRIMARY), &mi);
	ui::UiRect rcWork = mi.rcWork;
	ui::UiRect monitor_rect = mi.rcMonitor;

	ui::CSize szInit = { rcWork.right - rcWork.left, rcWork.bottom - rcWork.top };
	szInit = GetRoot()->EstimateSize(szInit);
	szInit.cx -= GetShadowCorner().left + GetShadowCorner().right;
	szInit.cy -= GetShadowCorner().top + GetShadowCorner().bottom;

	switch (m_ePopup) {
	case ePopupRB:
		if (m_base_point.y + szInit.cy > monitor_rect.bottom) {
			m_base_point.y -= szInit.cy;
		}
		break;
	case ePopupRT:
		if (m_base_point.y - szInit.cy >= monitor_rect.top) {
			m_base_point.y -= szInit.cy;
		}
		break;
	default:
		//兼容老版本
		return;
	}

	ui::UiRect rc;
	rc.left = m_base_point.x;
	rc.top  = m_base_point.y;
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
		::SetForegroundWindow(GetHWND());
	}
}

ui::Control* MenuWnd::CreateControl(const std::wstring& pstrClass)
{
	if (pstrClass == L"MenuElement")
	{
		return new MenuElementUI();
	}
	return NULL;
}

void MenuWnd::InitWindow()
{
	if (m_pOwner)
	{
		m_pLayout = dynamic_cast<ui::ListBox*>(FindControl(L"submenu"));
		ASSERT(m_pLayout);
		m_pLayout->SetAutoDestroyChild(false);

		for (int i = 0; i < m_pOwner->GetSubMenuItemCount(); i++) {
			MenuElementUI* subMenuItem = dynamic_cast<MenuElementUI*>(m_pOwner->GetSubMenuItemAt(i));
			subMenuItem->SetInternVisible(true);		//add by djj 20200506
			if (subMenuItem && subMenuItem->IsVisible())
			{
				m_pLayout->Add(subMenuItem); //内部会调用subMenuItem->SetOwner(m_pLayout); 会调用SetWindows，改变了归属窗口、父控件。
			}
		}
	}
	else
	{
		m_pLayout = dynamic_cast<ui::ListBox*>(m_pRoot);
		if (m_pLayout == NULL)
		{
			//允许外面套层阴影
			if (m_pRoot->GetCount()>0)
			{
				m_pLayout = dynamic_cast<ui::ListBox*>(m_pRoot->GetItemAt(0));
			}
		}
		ASSERT(m_pLayout);
	}
}

void MenuWnd::OnFinalMessage(HWND hWnd)
{
	Window::OnFinalMessage(hWnd);
	RemoveObserver();
	DetouchOwner();
	ReapObjects(GetRoot());
	delete this;
}

LRESULT MenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
 	case WM_KILLFOCUS:
 	{
		HWND hFocusWnd = (HWND)wParam;

		BOOL bInMenuWindowList = FALSE;
		ContextMenuParam param;
		param.hWnd = GetHWND();

		ContextMenuObserver::Iterator<BOOL, ContextMenuParam> iterator(GetMenuObserver());
		ReceiverImplBase<BOOL, ContextMenuParam>* pReceiver = iterator.next();
		while (pReceiver != NULL) {
			MenuWnd* pContextMenu = dynamic_cast<MenuWnd*>(pReceiver);
			if (pContextMenu != NULL && pContextMenu->GetHWND() == hFocusWnd) {
				bInMenuWindowList = TRUE;
				break;
			}
			pReceiver = iterator.next();
		}

		if (!bInMenuWindowList) {
			param.wParam = eMenuCloseAll;
			GetMenuObserver().RBroadcast(param);

			return 0;
		}
	}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE || wParam == VK_LEFT)
			Close();
		else if (wParam == VK_RIGHT)
		{
			if (m_pLayout)
			{
				int index = m_pLayout->GetCurSel();
				MenuElementUI* pItem = dynamic_cast<MenuElementUI*>(m_pLayout->GetItemAt(index));
				if (pItem)
				{
					pItem->CheckSubMenuItem();
				}
			}
		}
		else if (wParam == VK_RETURN || wParam == VK_SPACE)
		{
			if (m_pLayout)
			{
				int index = m_pLayout->GetCurSel();
				MenuElementUI* pItem = dynamic_cast<MenuElementUI*>(m_pLayout->GetItemAt(index));
				if (pItem)
				{
					if (!pItem->CheckSubMenuItem())
					{
						ContextMenuParam param;
						param.hWnd = m_hWnd;
						param.wParam = eMenuCloseAll;
						MenuWnd::GetMenuObserver().RBroadcast(param);
					}
				}
			}
		}
		break;
	case WM_RBUTTONDOWN:
	case WM_CONTEXTMENU:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		return 0L;

	default:
		break;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

ContextMenuObserver& MenuWnd::GetMenuObserver()
{
	static ContextMenuObserver s_context_menu_observer;
	return s_context_menu_observer;
}

BOOL MenuWnd::Receive(ContextMenuParam param)
{
	switch (param.wParam)
	{
	case eMenuCloseAll:
		Close();
		break;
	case eMenuCloseThis:
	{
		HWND hParent = GetParent(m_hWnd);
		while (hParent != NULL)
		{
			if (hParent == param.hWnd)
			{
				Close();
				break;
			}
			hParent = GetParent(hParent);
		}
	}
		break;
	default:
		break;
	}

	return TRUE;
}

void MenuWnd::DetouchOwner()
{
	if (m_pOwner)
	{
		m_pLayout->SelectItem(-1);

		for (int i = 0; i < m_pOwner->GetSubMenuItemCount(); i++) {
			MenuElementUI* pItem = static_cast<MenuElementUI*>(m_pOwner->GetSubMenuItemAt(i));
			if (pItem)
			{
				pItem->SetWindow(nullptr, nullptr, false);
			}
		}

		m_pLayout->RemoveAll();
		m_pOwner->m_pSubWindow = NULL;
		//m_pOwner->m_uButtonState &= ~UISTATE_PUSHED;  这里可能需要替换，暂时注释
		m_pOwner->Invalidate();
		m_pOwner = NULL;
	}
}

void MenuWnd::ResizeMenu()
{
	ui::Control* pRoot = GetRoot();
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	//点击在哪里，以哪里的屏幕为主
	::GetMonitorInfo(::MonitorFromPoint(m_base_point, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	ui::UiRect rcWork = oMonitor.rcWork;

	ui::CSize szAvailable = { rcWork.right - rcWork.left, rcWork.bottom - rcWork.top };
	szAvailable = pRoot->EstimateSize(szAvailable);   //这里带上了阴影窗口
	SetInitSize(szAvailable.cx, szAvailable.cy);
	ui::UiRect rcCorner = GetShadowCorner();
	ui::CSize szInit=szAvailable;
	szInit.cx -= rcCorner.left + rcCorner.right;
	szInit.cy -= rcCorner.top + rcCorner.bottom; //这里去掉阴影窗口，即用户的视觉有效面积 szInit<=szAvailable
	
	ui::CPoint point = m_base_point;  //这里有个bug，由于坐标点与包含在窗口内，会直接出发mouseenter导致出来子菜单，偏移1个像素
	if (m_ePopup & eMenuAlignment_R)
	{
		point.x += -szAvailable.cx + rcCorner.right + rcCorner.left;
		point.x -= 1;
	}
	else if (m_ePopup & eMenuAlignment_L)
	{
		point.x += 1;
	}
	if (m_ePopup & eMenuAlignment_B)
	{
		point.y += -szAvailable.cy + rcCorner.bottom + rcCorner.top;
		point.y += 1;
	}
	else if (m_ePopup & eMenuAlignment_T)
	{
		point.y += 1;
	}
	if (m_ePopup&eMenuAlignment_I)
	{
		if (point.x < rcWork.left)
		{
			point.x = rcWork.left;
		}
		else if (point.x + szInit.cx> rcWork.right)
		{
			point.x = rcWork.right - szInit.cx;
		}
		if (point.y < rcWork.top)
		{
			point.y = rcWork.top ;
		}
		else if (point.y + szInit.cy > rcWork.bottom)
		{
			point.y = rcWork.bottom - szInit.cy;
		}
	}
	if (!m_no_focus)
	{
		SetForegroundWindow(m_hWnd);
		SetFocus(m_pLayout);
	}
	SetWindowPos(m_hWnd, HWND_TOPMOST, point.x - rcCorner.left, point.y-rcCorner.top,
		szAvailable.cx, szAvailable.cy,
		SWP_SHOWWINDOW | (m_no_focus ? SWP_NOACTIVATE : 0));
}

void MenuWnd::ResizeSubMenu()
{
	// Position the popup window in absolute space
	RECT rcOwner = m_pOwner->GetPos();
	RECT rc = rcOwner;

	int cxFixed = 0;
	int cyFixed = 0;

	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromPoint(m_base_point, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	ui::UiRect rcWork = oMonitor.rcWork;
	ui::CSize szAvailable = { rcWork.right - rcWork.left, rcWork.bottom - rcWork.top };

	for (int it = 0; it < m_pLayout->GetCount(); it++) {
		//取子菜单项中的最大值作为菜单项
		MenuElementUI* pItem = dynamic_cast<MenuElementUI*>(m_pLayout->GetItemAt(it));
		if (pItem)
		{
			SIZE sz = pItem->EstimateSize(szAvailable);
			cyFixed += sz.cy;

			if (cxFixed < sz.cx)
				cxFixed = sz.cx;
		}
	}
	ui::UiRect rcCorner = GetShadowCorner();
	RECT rcWindow;
	GetWindowRect(m_pOwner->GetWindow()->GetHWND(), &rcWindow);
	//去阴影
	{
		rcWindow.left += rcCorner.left;
		rcWindow.right -= rcCorner.right;
		rcWindow.top += rcCorner.top;
		rcWindow.bottom -=  rcCorner.bottom;
	}

	::MapWindowRect(m_pOwner->GetWindow()->GetHWND(), HWND_DESKTOP, &rc);
	
	rc.left = rcWindow.right;
	rc.right = rc.left + cxFixed;
	rc.bottom = rc.top + cyFixed;

	bool bReachBottom = false;
	bool bReachRight = false;
	LONG chRightAlgin = 0;
	LONG chBottomAlgin = 0;

	RECT rcPreWindow = { 0 };
	ContextMenuObserver::Iterator<BOOL, ContextMenuParam> iterator(GetMenuObserver());
	ReceiverImplBase<BOOL, ContextMenuParam>* pReceiver = iterator.next();
	while (pReceiver != NULL) {
		MenuWnd* pContextMenu = dynamic_cast<MenuWnd*>(pReceiver);
		if (pContextMenu != NULL) {
			GetWindowRect(pContextMenu->GetHWND(), &rcPreWindow);  //需要减掉阴影

			bReachRight = (rcPreWindow.left + rcCorner.left) >= rcWindow.right;
			bReachBottom = (rcPreWindow.top + rcCorner.top) >= rcWindow.bottom;
			if (pContextMenu->GetHWND() == m_pOwner->GetWindow()->GetHWND()
				|| bReachBottom || bReachRight)
				break;
		}
		pReceiver = iterator.next();
	}
	if (bReachBottom)
	{
		rc.bottom = rcWindow.top;
		rc.top = rc.bottom - cyFixed;
	}

	if (bReachRight)
	{
		rc.right = rcWindow.left;
		rc.left = rc.right - cxFixed;
	}

	if (rc.bottom > rcWork.bottom)
	{
		rc.bottom = rc.top;
		rc.top = rc.bottom - cyFixed;
	}

	if (rc.right > rcWork.right)
	{
		rc.right = rcWindow.left;
		rc.left = rc.right - cxFixed;
	}

	if (rc.top < rcWork.top)
	{
		rc.top = rcOwner.top;
		rc.bottom = rc.top + cyFixed;
	}

	if (rc.left < rcWork.left)
	{
		rc.left = rcWindow.right;
		rc.right = rc.left + cxFixed;
	}

	SetWindowPos(m_hWnd, HWND_TOPMOST, rc.left-rcCorner.left, rc.top-rcCorner.top,
		rc.right - rc.left, rc.bottom - rc.top,
		SWP_SHOWWINDOW);

	SetForegroundWindow(m_hWnd);
	SetFocus(m_pLayout);
}

//****************************/
//-- class MenuElementUI
//****************************/
//////////////////////////////////////////////////////////////////////////

MenuElementUI::MenuElementUI()
	: m_pSubWindow(nullptr)
{
	m_bMouseChildEnabled = false;
}

MenuElementUI::~MenuElementUI()
{
	if (m_child_menus.size() > 0)
	{
		for (size_t i = 0; i < m_child_menus.size(); i++)
		{
			delete m_child_menus[i];
		}
		m_child_menus.clear();
	}
}

bool MenuElementUI::Add(Control* pControl)
{
	MenuElementUI *pMenuItem = dynamic_cast<MenuElementUI*>(pControl);
	if (!pMenuItem)
		return __super::Add(pControl);
	if (std::find(m_child_menus.cbegin(), m_child_menus.cend(), pMenuItem) != m_child_menus.cend())
	{
		assert(0);
		return false;
	}
	m_child_menus.push_back(pMenuItem);
	return true;
}

bool MenuElementUI::AddSubMenuItem(MenuElementUI* pMenuItem)
{
	if (pMenuItem == NULL) return false;
	if (std::find(m_child_menus.cbegin(), m_child_menus.cend(), pMenuItem) != m_child_menus.cend())
	{
		assert(0);
		return false;
	}
	m_child_menus.push_back(pMenuItem);
	return true;
}

bool MenuElementUI::AddSubMenuItemAt(MenuElementUI* pMenuItem, std::size_t iIndex)
{
	if (pMenuItem == NULL) return false;
	if (iIndex < 0 || iIndex > m_child_menus.size()) {
		ASSERT(FALSE);
		return false;
	}
	if (std::find(m_child_menus.cbegin(), m_child_menus.cend(), pMenuItem) != m_child_menus.cend())
	{
		assert(0);
		return false;
	}
	m_child_menus.insert(m_child_menus.begin() + iIndex, pMenuItem);
	return true;
}

bool MenuElementUI::RemoveSubMenuItem(MenuElementUI* pMenuItem)
{
	if (pMenuItem == NULL) return false;

	for (auto it = m_child_menus.begin(); it != m_child_menus.end(); it++) {
		if (*it == pMenuItem) {
			delete pMenuItem;			//
			m_child_menus.erase(it);
			return true;
		}
	}
	return false;
}

bool MenuElementUI::RemoveSubMenuItemAt(std::size_t iIndex)
{
	if (iIndex < 0 || iIndex >= m_child_menus.size()) return false;
	return RemoveSubMenuItem(m_child_menus[iIndex]);
}

bool MenuElementUI::RemoveAllSubMenuItem()
{
	for (auto it = m_child_menus.begin(); it != m_child_menus.end(); it++)
	{
		delete (*it);
	}
	m_child_menus.clear();
	return true;
}

MenuElementUI* MenuElementUI::GetSubMenuItemAt(std::size_t iIndex) const
{
	if (iIndex < 0 || iIndex >= m_child_menus.size()) return nullptr;
	return m_child_menus[iIndex];
}

bool MenuElementUI::ButtonUp(ui::EventArgs& msg)
{
	std::weak_ptr<nbase::WeakFlag> weakFlag = m_pWindow->GetWeakFlag();
	bool ret = __super::ButtonUp(msg);
	if (ret && !weakFlag.expired()) {
		//这里处理下如果有子菜单则显示子菜单
		if (!CheckSubMenuItem())
		{
			ContextMenuParam param;
			param.hWnd = GetWindow()->GetHWND();
			param.wParam = eMenuCloseAll;
			MenuWnd::GetMenuObserver().RBroadcast(param);
		}
	}

	return ret;
}

bool MenuElementUI::MouseEnter(ui::EventArgs& msg)
{
	std::weak_ptr<nbase::WeakFlag> weakFlag = m_pWindow->GetWeakFlag();
	bool ret = __super::MouseEnter(msg);
	if (ret && !weakFlag.expired()) {
		//这里处理下如果有子菜单则显示子菜单
		if (!CheckSubMenuItem())
		{
			ContextMenuParam param;
			param.hWnd = GetWindow()->GetHWND();
			param.wParam = eMenuCloseThis;
			MenuWnd::GetMenuObserver().RBroadcast(param);
			//m_pOwner->SelectItem(GetIndex(), true);  有些老版本attachselect会触发
			//这里得把之前选中的置为未选中
			m_pOwner->SelectItem(-1, false);
		}
	}

	return ret;
}

void MenuElementUI::PaintChild(ui::IRenderContext* pRender, const ui::UiRect& rcPaint)
{
	ui::UiRect rcTemp;
	if (!::IntersectRect(&rcTemp, &rcPaint, &m_rcItem)) return;

	for (auto it = m_items.begin(); it != m_items.end(); it++) {
		//尝试转CMenuElementUI
		MenuElementUI* subMenuItem = dynamic_cast<MenuElementUI*>(*it);
		if (subMenuItem)
		{
			continue;
		}
		Control* pControl = *it;
		if (!pControl->IsVisible()) continue;
		pControl->AlphaPaint(pRender, rcPaint);
	}
}

bool MenuElementUI::CheckSubMenuItem()
{
	bool hasSubMenu = m_child_menus.size() > 0;
	if (hasSubMenu)
	{
		m_pOwner->SelectItem(GetIndex(), true);
		CreateMenuWnd();
	}
	return hasSubMenu;
}

void MenuElementUI::CreateMenuWnd()
{
#if 0
	if (m_pSubWindow)
		return;
#else		//add by djj 20200506 快速切换子菜单情况下, 可以使子菜单弹出及时
	if (m_pSubWindow)
	{
		if (m_pSubWindow->IsClosing())
		{
			m_pSubWindow->DetouchOwner();
		}
		else
		{
			return;
		}
	}
#endif
	m_pSubWindow = new MenuWnd(GetWindow()->GetHWND());

	ContextMenuParam param;
	param.hWnd =GetWindow()->GetHWND();
	param.wParam = eMenuCloseThis;
	MenuWnd::GetMenuObserver().RBroadcast(param);

	m_pSubWindow->Init(_T("submenu.xml"), ui::CPoint(), MenuWnd::ePopupRB, false, this);
}

NS_UI_COMP_END