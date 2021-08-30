#include "stdafx.h"
#include "Resource.h"
#include "MainForm.h"
#include "LoginKit.h"
#include "MsgBox.h"

//****************************/
//-- namespace NS_MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_MainForm_BEGIN	namespace NS_MainForm {
#define NS_MainForm_END		}
#define USING_NS_MainForm	using namespace NS_MainForm

NS_MainForm_BEGIN

//-- �ؼ�����
CONST PWSTR WGT_closebtn2	= L"closebtn2";		// Button: �رգ��������Ͻǲ棩
CONST PWSTR WGT_btn_logout	= L"btn_logout";	// Button: ע��
CONST PWSTR WGT_btn_exit	= L"btn_exit";		// Button: �˳�

//-- �ı�����
CONST PWSTR TXT_exit_confirm	= L"ȷ���˳�����";
CONST PWSTR TXT_title_hint		= L"��ʾ";
CONST PWSTR TXT_btn_confirm		= L"ȷ��";
CONST PWSTR TXT_btn_cancel		= L"ȡ��";

NS_MainForm_END
USING_NS_MainForm;

//****************************/
//-- class MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

void MainForm::InitWindow()
{
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::Main_WindowName);

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&MainForm::OnNotify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&MainForm::OnClicked, this, std::placeholders::_1));
	
	// ���ݿؼ����Ʋ��ҿؼ�
	m_btn_logout = (ui::Button*)FindControl(WGT_btn_logout);
	m_btn_exit   = (ui::Button*)FindControl(WGT_btn_exit);
}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool MainForm::OnNotify(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	switch (msg->Type)
	{
	case ui::kEventTextChange:
		break;
	case ui::kEventTab:
		break;
	case ui::kEventReturn:
		break;
	default:
		break;
	}
	return true;
}

bool MainForm::OnClicked(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_closebtn2)
	{
		auto cb_Close = [this](ui_comp::EMsgBoxRet eRet) {
			if (eRet == ui_comp::eMsgBox_YES) {
				this->Close();
			}
		};
		ui_comp::MsgBox::Show(m_hWnd, ToWeakCallback(cb_Close), TXT_exit_confirm, TXT_title_hint, TXT_btn_confirm, TXT_btn_cancel);
	}
	else if (sSenderName == WGT_btn_logout)
	{
		LoginKit::GetInstance()->DoLogout();
	}
	else if (sSenderName == WGT_btn_exit)
	{
		this->Close();
	}
	return true;
}
