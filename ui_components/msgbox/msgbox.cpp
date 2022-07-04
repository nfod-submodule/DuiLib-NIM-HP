#include "stdafx.h"
#include "msgbox.h"

NS_UI_COMP_BEGIN

//****************************/
//-- namespace NS_MsgBox
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_MsgBox_BEGIN	namespace NS_MsgBox {
#define NS_MsgBox_END	}
#define USING_NS_MsgBox	using namespace NS_MsgBox

NS_MsgBox_BEGIN

//-- 控件名称
CONST PWSTR WGT_title		= L"title";		// Label: 标题
CONST PWSTR WGT_content		= L"content";	// RichEdit: 内容
CONST PWSTR WGT_btn_yes		= L"btn_yes";	// Button：是
CONST PWSTR WGT_btn_no		= L"btn_no";	// Button: 否
CONST PWSTR WGT_closebtn	= L"closebtn";	// Button: 关闭（窗口右上角叉）

NS_MsgBox_END
USING_NS_MsgBox;

//****************************/
//-- class MsgBox
//****************************/
//////////////////////////////////////////////////////////////////////////

void MsgBox::Close(UINT nRet /*= IDOK*/)
{
	__super::Close(nRet);
}

void MsgBox::InitWindow()
{
	// 根据控件名称查找控件
	m_title   = (ui::Label*)   FindControl(WGT_title);
	m_content = (ui::RichEdit*)FindControl(WGT_content);
	m_btn_yes = (ui::Button*)  FindControl(WGT_btn_yes);
	m_btn_no  = (ui::Button*)  FindControl(WGT_btn_no);

	// 注册事件的回调函数
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&MsgBox::OnEventClick, this, std::placeholders::_1));
}

bool MsgBox::OnEventClick(ui::EventArgs* msg)
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
	::SetWindowTextW(m_hWnd, title.c_str());
}

void MsgBox::SetContent(const std::wstring& content)
{
	m_content->SetText(content);
	int width = m_content->GetFixedWidth();
	ui::CSize sz = m_content->GetNaturalSize(width, 0);
	m_content->SetFixedHeight(sz.cy, false);
}

void MsgBox::SetButton(const std::wstring& btn_yes, const std::wstring& btn_no)
{
	if (btn_yes.empty()) {
		m_btn_yes->SetVisible(false);
	}
	else {
		m_btn_yes->SetVisible(true);
		m_btn_yes->SetText(btn_yes);
		m_btn_yes->SetFocus();
	}

	if (btn_no.empty()) {
		m_btn_no->SetVisible(false);
	}
	else {
		m_btn_no->SetVisible(true);
		m_btn_no->SetText(btn_no);
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
		nbase::ThreadManager::PostTask(kThreadUI, task);
	}
}

NS_UI_COMP_END