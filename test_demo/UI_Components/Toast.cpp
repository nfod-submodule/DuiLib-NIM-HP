#include "stdafx.h"
#include "Toast.h"
#include "ConfUI.h"

NS_UI_COMP_BEGIN

//-- 控件名称
CONST PWSTR WGT_content		= L"content";	// RichEdit: 内容
CONST PWSTR WGT_closebtn	= L"close_btn";	// Button: 关闭

//****************************/
//-- class Toast
//****************************/
//////////////////////////////////////////////////////////////////////////

void Toast::Show(HWND hWndParent, const std::wstring& content, int duration)
{
	Toast* pWnd = new Toast();
	if (pWnd) {
		HWND hWnd = pWnd->Create(hWndParent, NULL, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		if (hWnd) {
			pWnd->SetContent(content);
			pWnd->SetDuration(duration);
			pWnd->CenterWindow();
			pWnd->ShowWindow();
		}
		else {
			delete pWnd;
			pWnd = NULL;
		}
	}
}

LRESULT Toast::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_ESCAPE)
	{
		this->Close();
	}
	// 整个toast界面都在标题栏，所以要处理WM_NC消息
	else if (uMsg == WM_NCLBUTTONDBLCLK || uMsg == WM_LBUTTONDBLCLK)
	{
		this->Close();
	}
	// duilib在WM_MOUSELEAVE消息中会发送一个lparam为-1的WM_MOUSEMOVE消息
	else if ((uMsg == WM_NCMOUSEMOVE || uMsg == WM_MOUSEMOVE) && lParam != -1)
	{
		if (NULL != m_btn_close && !m_btn_close->IsVisible()) {
			m_btn_close->SetVisible(true);
		}
	}
	else if (uMsg == WM_NCMOUSELEAVE || uMsg == WM_MOUSELEAVE)
	{
		POINT point;
		::GetCursorPos(&point);
		::ScreenToClient(m_hWnd, &point);
		ui::UiRect client_rect;
		::GetClientRect(m_hWnd, &client_rect);
		// leave消息触发时，获取的鼠标坐标有可能还在client_rect范围内，会偏差1像素，这里缩减1像素
		client_rect.Deflate(ui::UiRect(1, 1, 1, 1));
		if (NULL != m_btn_close && !client_rect.IsPointIn(point)) {
			m_btn_close->SetVisible(false);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Toast::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&Toast::OnClicked, this, std::placeholders::_1));

	// 根据控件名称查找控件
	m_content   = (ui::RichEdit*)FindControl(WGT_content);
	m_btn_close = (ui::Button*)  FindControl(WGT_closebtn);
}

bool Toast::OnClicked(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_closebtn)
	{
		this->Close();
	}
	return true;
}

void Toast::SetContent(const std::wstring& content)
{
	m_content->SetText(content);
	int width = m_content->GetFixedWidth();
	ui::CSize sz = m_content->GetNaturalSize(width, 0);
	m_content->SetFixedHeight(sz.cy);
}

void Toast::SetDuration(int duration_milliseconds)
{
	if (duration_milliseconds <= 0) {
		return;
	}
	auto cb_Close = [this]() {
		this->Close();
	};
	auto task = std::bind<void>(cb_Close);
	nbase::ThreadManager::PostDelayedTask(eThread_UI, task, nbase::TimeDelta::FromMilliseconds(duration_milliseconds));
}

NS_UI_COMP_END