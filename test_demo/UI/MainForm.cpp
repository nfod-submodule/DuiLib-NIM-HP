#include "stdafx.h"
#include "Resource.h"
#include "MainForm.h"
#include "ConfUI.h"

//****************************/
//-- namespace NS_MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_MainForm_BEGIN	namespace NS_MainForm {
#define NS_MainForm_END		}
#define USING_NS_MainForm	using namespace NS_MainForm

NS_MainForm_BEGIN

//-- 控件名称
CONST PWSTR WGT_btn_logout	= L"btn_logout";	// Button: 注销
CONST PWSTR WGT_btn_exit	= L"btn_exit";		// Button: 退出

NS_MainForm_END
USING_NS_MainForm;

//****************************/
//-- class MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

MainForm::MainForm()
{

}

MainForm::~MainForm()
{

}

std::wstring MainForm::GetSkinFolder()
{
	return TextUI::Main_SkinFolder;
}

std::wstring MainForm::GetSkinFile()
{
	return TextUI::Main_SkinFile;
}

std::wstring MainForm::GetWindowClassName() const
{
	return TextUI::Main_ClassName;
}

void MainForm::InitWindow()
{
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(TextUI::Main_WindowName);

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&MainForm::OnNotify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&MainForm::OnClicked, this, std::placeholders::_1));
	
	// 根据控件名称查找控件
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
	if (sSenderName == WGT_btn_logout)
	{
		;
	}
	else if (sSenderName == WGT_btn_exit)
	{
		;
	}
	return true;
}
