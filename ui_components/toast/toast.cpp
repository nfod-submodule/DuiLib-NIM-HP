#include "stdafx.h"
#include "toast.h"

NS_UI_COMP_BEGIN

//****************************/
//-- namespace NS_Toast
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_Toast_BEGIN	namespace NS_Toast {
#define NS_Toast_END	}
#define USING_NS_Toast	using namespace NS_Toast

NS_Toast_BEGIN

//-- 控件名称
CONST PWSTR WGT_content		= L"content";	// RichEdit: 提示内容
CONST PWSTR WGT_close_btn	= L"close_btn";	// Button: 关闭按钮

NS_Toast_END
USING_NS_Toast;

//****************************/
//-- class Toast
//****************************/
//////////////////////////////////////////////////////////////////////////

void Toast::Close(UINT nRet /*= IDOK*/)
{
	// 取消窗口的显示时长（到时不再响应）
	Toast_Kit::GetInstance()->DelDuration(this);
	__super::Close(nRet);
}

void Toast::InitWindow()
{
	// 根据控件名称查找控件
	m_content   = (ui::RichEdit*)FindControl(WGT_content);
	m_close_btn = (ui::Button*)  FindControl(WGT_close_btn);

	// 注册事件的回调函数
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&Toast::OnEventClick, this, std::placeholders::_1));
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
		if (m_close_btn != NULL && !m_close_btn->IsVisible()) {
			m_close_btn->SetVisible(true);
		}
	}
	else if (uMsg == WM_NCMOUSELEAVE || uMsg == WM_MOUSELEAVE)
	{
		POINT pt;
		::GetCursorPos(&pt);
		::ScreenToClient(m_hWnd, &pt);
		ui::UiRect client_rect;
		::GetClientRect(m_hWnd, &client_rect);
		// leave消息触发时，获取的鼠标坐标有可能还在client_rect范围内，会偏差1像素，这里缩减1像素
		client_rect.Deflate(ui::UiRect(1, 1, 1, 1));
		if (m_close_btn != NULL && !client_rect.IsPointIn(pt)) {
			m_close_btn->SetVisible(false);
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool Toast::OnEventClick(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_close_btn)
	{
		this->Close();
	}
	return true;
}

void Toast::SetContent(const std::wstring& str)
{
	m_content->SetText(str);
	int width = m_content->GetFixedWidth();
	ui::CSize sz = m_content->GetNaturalSize(width, 0);
	m_content->SetFixedHeight(sz.cy);
}

void Toast::SetDuration(int duration)
{
	// 设置窗口的显示时长
	Toast_Kit::GetInstance()->SetDuration(this, duration);
}

//****************************/
//-- class Toast_Kit
//****************************/
//////////////////////////////////////////////////////////////////////////

void Toast_Kit::SetDuration(
	Toast* pWnd,
	int duration)
{
	if (pWnd == NULL || duration <= 0) {
		return;
	}
	do  {
		std::lock_guard<std::mutex> lock(m_mutexWnd);
		auto iter = m_mapWnd.find(pWnd);
		if (iter != m_mapWnd.end()) {
			return;
		}
		m_mapWnd.insert(std::make_pair(pWnd, duration));
	} while (0);
	auto task = [this, pWnd]()
	{
		Duration_ToClose(pWnd);
	};
	nbase::ThreadManager::PostDelayedTask(kThreadUI, task, nbase::TimeDelta::FromMilliseconds(duration));
}

void Toast_Kit::DelDuration(
	Toast* pWnd)
{
	std::lock_guard<std::mutex> lock(m_mutexWnd);
	auto iter = m_mapWnd.find(pWnd);
	if (iter != m_mapWnd.end()) {
		m_mapWnd.erase(iter);
	}
}

void Toast_Kit::Duration_ToClose(
	Toast* pWnd)
{
	if (pWnd == NULL) {
		return;
	}
	do  {
		std::lock_guard<std::mutex> lock(m_mutexWnd);
		auto iter = m_mapWnd.find(pWnd);
		if (iter == m_mapWnd.end()) {
			return;
		}
		m_mapWnd.erase(iter);
	} while (0);
	try {
		if (pWnd) {
			pWnd->Close();
		}
	}
	catch (const std::exception&) {}
}

NS_UI_COMP_END