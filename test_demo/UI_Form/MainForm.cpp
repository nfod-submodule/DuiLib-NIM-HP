#include "stdafx.h"
#include "Resource.h"
#include "MainForm.h"
#include "LoginKit.h"
#include "MenuWnd.h"
#include "MsgBox.h"

//****************************/
//-- namespace NS_MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_MainForm_BEGIN	namespace NS_MainForm {
#define NS_MainForm_END		}
#define USING_NS_MainForm	using namespace NS_MainForm

NS_MainForm_BEGIN

//-- 控件名称
CONST PWSTR WGT_closebtn2	= L"closebtn2";		// Button: 关闭（窗口右上角叉）
CONST PWSTR WGT_btn_menu	= L"btn_menu";		// Button: 菜单
CONST PWSTR WGT_btn_logout	= L"btn_logout";	// Button: 注销
CONST PWSTR WGT_btn_quit	= L"btn_quit";		// Button: 退出
CONST PWSTR WGT_opt_tab_r	= L"opt_tab_r";		// Option: 标签-红
CONST PWSTR WGT_opt_tab_g	= L"opt_tab_g";		// Option: 标签-绿
CONST PWSTR WGT_box_tabs	= L"box_tabs";		// TabBox: 标签内容

CONST INT WGT_box_tab_r_index = 0;	// 标签内容-红-索引
CONST INT WGT_box_tab_g_index = 1;	// 标签内容-绿-索引

//-- 文本内容
CONST PWSTR TXT_exit_confirm	= L"确定退出程序？";
CONST PWSTR TXT_title_hint		= L"提示";
CONST PWSTR TXT_btn_confirm		= L"确定";
CONST PWSTR TXT_btn_cancel		= L"取消";

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
	
	// 根据控件名称查找控件
	m_btn_menu   = (ui::Button*)FindControl(WGT_btn_menu);
	m_btn_logout = (ui::Button*)FindControl(WGT_btn_logout);
	m_btn_quit   = (ui::Button*)FindControl(WGT_btn_quit);
	m_opt_tab_r  = (ui::Option*)FindControl(WGT_opt_tab_r);
	m_opt_tab_g  = (ui::Option*)FindControl(WGT_opt_tab_g);
	m_box_tabs   = (ui::TabBox*)FindControl(WGT_box_tabs);

	// 默认显示：标签-绿
	m_opt_tab_g->Selected(true);
	m_box_tabs->SelectItem(WGT_box_tab_g_index);
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
	else if (sSenderName == WGT_btn_menu)
	{
		RECT rect = msg->pSender->GetPos();
		POINT point;
		point.x = rect.left - 15;
		point.y = rect.bottom + 10;
		::ClientToScreen(m_hWnd, &point);
		PopupMenu(point);
	}
	else if (sSenderName == WGT_btn_logout)
	{
		LoginKit::GetInstance()->DoLogout();
	}
	else if (sSenderName == WGT_btn_quit)
	{
		this->Close();
	}
	else if (sSenderName == WGT_opt_tab_r)
	{
		m_box_tabs->SelectItem(WGT_box_tab_r_index);
	}
	else if (sSenderName == WGT_opt_tab_g)
	{
		m_box_tabs->SelectItem(WGT_box_tab_g_index);
	}
	return true;
}

void MainForm::PopupMenu(POINT point)
{
	static CONST PWSTR XML_SkinFile = L"main_menu.xml";
	static CONST PWSTR WGT_element_about  = L"about";
	static CONST PWSTR WGT_element_logout = L"logout";
	static CONST PWSTR WGT_element_quit   = L"quit";

 	ui_comp::MenuWnd* pMenu = new ui_comp::MenuWnd();
 	pMenu->Init(XML_SkinFile, point, ui_comp::MenuWnd::RIGHT_BOTTOM);
	{
		// 注册回调-关于
		ui::EventCallback cb_about = [this](ui::EventArgs*) {
			ui_comp::MsgBox::Show(m_hWnd, nullptr, L"版本：V1.0.0", L"关于", L"知道了", L"");
			return true;
		};
		ui_comp::MenuElementUI* pAbout = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_about);
		pAbout->AttachSelect(cb_about);
		// 注册回调-注销
		ui::EventCallback cb_logout = [this](ui::EventArgs*) {
			LoginKit::GetInstance()->DoLogout();
			return true;
		};
		ui_comp::MenuElementUI* pLogout = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_logout);
		pLogout->AttachSelect(cb_logout);
		// 注册回调-退出
		ui::EventCallback cb_quit = [this](ui::EventArgs*) {
			this->Close();
			return true;
		};
		ui_comp::MenuElementUI* pQuit = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_quit);
		pQuit->AttachSelect(cb_quit);
	}
 	pMenu->Show();
}
