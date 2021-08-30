#include "stdafx.h"
#include "MsgBox.h"
#include "ConfUI.h"

NS_UI_COMP_BEGIN

//-- �ؼ�����
CONST PWSTR WGT_title		= L"title";		// Label: ����
CONST PWSTR WGT_content		= L"content";	// RichEdit: ����
CONST PWSTR WGT_btn_yes		= L"btn_yes";	// Button����
CONST PWSTR WGT_btn_no		= L"btn_no";	// Button: ��
CONST PWSTR WGT_closebtn	= L"closebtn";	// Button: �رգ��������Ͻǲ棩

//****************************/
//-- class MsgBox
//****************************/
//////////////////////////////////////////////////////////////////////////

void MsgBox::Show(
	HWND hwnd,
	MsgBoxCallback callback,
	const std::wstring& content,
	const std::wstring& title /*= L"��ʾ"*/,
	const std::wstring& btn_yes /*= L"ȷ��"*/,
	const std::wstring& btn_no /*= L"ȡ��"*/)
{
	MsgBox* pWndMB = new MsgBox();
	if (pWndMB) {
		HWND hWndMB = pWndMB->Create(hwnd, NULL, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		if (hWndMB) {
			pWndMB->SetCallback(callback);
			pWndMB->SetTitle(title);
			pWndMB->SetContent(content);
			pWndMB->SetButton(btn_yes, btn_no);
			::EnableWindow(hwnd, FALSE);
			pWndMB->CenterWindow();
			pWndMB->ShowWindow();
		}
		else {
			delete pWndMB;
			pWndMB = NULL;
		}
	}
}

void MsgBox::Close(UINT nRet)
{
	// ��ʾ��ر�֮ǰ��Enable�����ڣ���ֹ��������������ȥ��
	HWND hWndParent = GetWindowOwner(m_hWnd);
	if (hWndParent)
	{
		::EnableWindow(hWndParent, TRUE);
		::SetFocus(hWndParent);
	}
	__super::Close(nRet);
}

LRESULT MsgBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MsgBox::OnEsc(BOOL &bHandled)
{
	bHandled = TRUE;
	EndMsgBox(eMsgBox_NO);
}

void MsgBox::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&MsgBox::OnClicked, this, std::placeholders::_1));

	// ���ݿؼ����Ʋ��ҿؼ�
	m_title   = (ui::Label*)   FindControl(WGT_title);
	m_content = (ui::RichEdit*)FindControl(WGT_content);
	m_btn_yes = (ui::Button*)  FindControl(WGT_btn_yes);
	m_btn_no  = (ui::Button*)  FindControl(WGT_btn_no);
}

bool MsgBox::OnClicked(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_btn_yes)
	{
		EndMsgBox(eMsgBox_YES);
	}
	else if (sSenderName == WGT_btn_no)
	{
		EndMsgBox(eMsgBox_NO);
	}
	else if (sSenderName == WGT_closebtn)
	{
		EndMsgBox(eMsgBox_NO);
	}
	return true;
}

void MsgBox::SetCallback(MsgBoxCallback callback)
{
	m_callback = callback;
}

void MsgBox::SetTitle(const std::wstring& title)
{
	m_title->SetText(title);
}

void MsgBox::SetContent(const std::wstring& content)
{
	m_content->SetText(content);
	int width = m_content->GetFixedWidth();
	ui::CSize sz = m_content->GetNaturalSize(width, 0);
	m_content->SetFixedHeight(sz.cy);
}

void MsgBox::SetButton(const std::wstring& btn_yes, const std::wstring& btn_no)
{
	if (btn_yes.empty()) {
		m_btn_yes->SetVisible(false);
	}
	else {
		m_btn_yes->SetText(btn_yes);
		m_btn_yes->SetVisible(true);
		m_btn_yes->SetFocus();
	}

	if (btn_no.empty()) {
		m_btn_no->SetVisible(false);
	}
	else {
		m_btn_no->SetText(btn_no);
		m_btn_no->SetVisible(true);
		if (btn_yes.empty()) {
			m_btn_no->SetFocus();
		}
	}
}

void MsgBox::EndMsgBox(EMsgBoxRet eRet)
{
	this->Close(0);
	if (m_callback) {
		auto task = std::bind<void>(m_callback, eRet);
		nbase::ThreadManager::PostTask(eThread_UI, task);
	}
}

NS_UI_COMP_END