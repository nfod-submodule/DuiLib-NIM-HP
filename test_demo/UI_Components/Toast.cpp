#include "stdafx.h"
#include "Toast.h"
#include "ConfUI.h"

NS_UI_COMP_BEGIN

//-- �ؼ�����
CONST PWSTR WGT_content		= L"content";	// RichEdit: ����
CONST PWSTR WGT_closebtn	= L"close_btn";	// Button: �ر�

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
	// ����toast���涼�ڱ�����������Ҫ����WM_NC��Ϣ
	else if (uMsg == WM_NCLBUTTONDBLCLK || uMsg == WM_LBUTTONDBLCLK)
	{
		this->Close();
	}
	// duilib��WM_MOUSELEAVE��Ϣ�лᷢ��һ��lparamΪ-1��WM_MOUSEMOVE��Ϣ
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
		// leave��Ϣ����ʱ����ȡ����������п��ܻ���client_rect��Χ�ڣ���ƫ��1���أ���������1����
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

	// ���ݿؼ����Ʋ��ҿؼ�
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