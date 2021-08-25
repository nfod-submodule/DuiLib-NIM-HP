#include "stdafx.h"
#include "Resource.h"
#include "LoginForm.h"
#include "ConfUI.h"

//****************************/
//-- namespace NS_LoginForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_LoginForm_BEGIN	namespace NS_LoginForm {
#define NS_LoginForm_END	}
#define USING_NS_LoginForm	using namespace NS_LoginForm

NS_LoginForm_BEGIN

//-- 控件名称
CONST PWSTR WGT_login_tip		= L"login_tip";				// Label: 提示信息
CONST PWSTR WGT_usernameicon	= L"usericon";				// Control: 帐号图标
CONST PWSTR WGT_passwordicon	= L"passwordicon";			// Control：密码图标
CONST PWSTR WGT_edit_username	= L"username";				// RichEdit: 帐号
CONST PWSTR WGT_edit_password	= L"password";				// RichEdit: 密码
CONST PWSTR WGT_cbox_remember	= L"checkbox_remember";		// CheckBox: 记住密码
CONST PWSTR WGT_cbox_autologin	= L"checkbox_autologin";	// CheckBox: 自动登录
CONST PWSTR WGT_btn_forgot		= L"forgot_password";		// Button: 忘记密码
CONST PWSTR WGT_btn_login		= L"btn_login";				// Button: 登录
CONST PWSTR WGT_btn_cancel		= L"btn_cancel";			// Button: 取消登录

//-- 文本内容
CONST PWSTR TXT_empty			= L"";
CONST PWSTR TXT_input_username	= L"请输入帐号";
CONST PWSTR TXT_input_password	= L"请输入密码";
CONST PWSTR TXT_login_ing		= L"正在登录...";
CONST PWSTR TXT_pwd_chs_denied	= L"密码不允许含有中文字符";

//-- 文本颜色
CONST PWSTR COLOR_text_default	= L"textdefaultcolor";
CONST PWSTR COLOR_red			= L"red";

NS_LoginForm_END
USING_NS_LoginForm;

//****************************/
//-- class LoginForm
//****************************/
//////////////////////////////////////////////////////////////////////////

LoginForm::LoginForm()
{

}

LoginForm::~LoginForm()
{

}

std::wstring LoginForm::GetSkinFolder()
{
	return ConfUI::Login_SkinFolder;
}

std::wstring LoginForm::GetSkinFile()
{
	return ConfUI::Login_SkinFile;
}

std::wstring LoginForm::GetWindowClassName() const
{
	return ConfUI::Login_ClassName;
}

void LoginForm::InitWindow()
{
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::Login_WindowName);

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&LoginForm::OnNotify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&LoginForm::OnClicked, this, std::placeholders::_1));

	// 根据控件名称查找控件
	m_login_tip      = (ui::Label*)   FindControl(WGT_login_tip);
	m_usernameicon   = (ui::Control*) FindControl(WGT_usernameicon);
	m_passwordicon   = (ui::Control*) FindControl(WGT_passwordicon);
	m_edit_username  = (ui::RichEdit*)FindControl(WGT_edit_username);
	m_edit_password  = (ui::RichEdit*)FindControl(WGT_edit_password);
	m_cbox_remember  = (ui::CheckBox*)FindControl(WGT_cbox_remember);
	m_cbox_autologin = (ui::CheckBox*)FindControl(WGT_cbox_autologin);
	m_btn_forgot     = (ui::Button*)  FindControl(WGT_btn_forgot);
	m_btn_login      = (ui::Button*)  FindControl(WGT_btn_login);
	m_btn_cancel     = (ui::Button*)  FindControl(WGT_btn_cancel);

	// 冻结Tab键
	SetFreezeTab(true);
	// 设置默认焦点
	m_edit_username->SetFocus();
	// 设置获取焦点后是否选择所有内容
	m_edit_username->SetSelAllOnFocus(true);
	m_edit_password->SetSelAllOnFocus(true);
	// 设置限制字符数量
	m_edit_username->SetLimitText(64);
	m_edit_password->SetLimitText(128);
	// 设置复选框默认选中
	m_cbox_remember->Selected(true);
	m_cbox_autologin->Selected(true);
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool LoginForm::OnNotify(ui::EventArgs* msg)
{
	switch (msg->Type)
	{
	case ui::kEventTextChange:
		OnEventTextChange(msg->pSender->GetName());
		break;
	case ui::kEventTab:
		OnEventTab();
		break;
	case ui::kEventReturn:
		OnEventReturn();
		break;
	default:
		break;
	}
	return true;
}

void LoginForm::OnEventTextChange(const std::wstring& sSenderName)
{
	if (sSenderName == WGT_edit_username)
	{
		// 清空提示信息
		SetLoginTip(TXT_empty, COLOR_text_default);
		// 图标正常状态
		m_usernameicon->SetEnabled(true);
		m_passwordicon->SetEnabled(true);
	}
	else if (sSenderName == WGT_edit_password)
	{
		// 去掉中文字符
		std::wstring pwd_fixed;
		std::wstring pwd = m_edit_password->GetText();
		for (size_t i = 0; i < pwd.length(); ++i) {
			if (ui::IsAsciiChar(pwd.at(i))) {
				pwd_fixed.push_back(pwd.at(i));
			}
		}
		m_edit_password->SetText(pwd_fixed);
		// 更新提示信息
		if (pwd == pwd_fixed) {
			SetLoginTip(TXT_empty, COLOR_text_default);
		}
		else {
			SetLoginTip(TXT_pwd_chs_denied, COLOR_red);
		}
		// 图标正常状态
		m_usernameicon->SetEnabled(true);
		m_passwordicon->SetEnabled(true);
	}
}

void LoginForm::OnEventTab()
{
	if (m_edit_username->IsFocused())
	{
		m_edit_password->SetSelAll();
		m_edit_password->SetFocus();
	}
	else if (m_edit_password->IsFocused())
	{
		m_edit_username->SetSelAll();
		m_edit_username->SetFocus();
	}
}

void LoginForm::OnEventReturn()
{
	if (m_btn_login->IsVisible() && m_btn_login->IsEnabled())
	{
		DoLogin();
	}
}

bool LoginForm::OnClicked(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_btn_login)
	{
		DoLogin();
	}
	else if (sSenderName == WGT_btn_cancel)
	{
		OnCancelLogin();
	}
	return true;
}

void LoginForm::OnCancelLogin()
{
	// 界面控件效果
	SetLoginTip(TXT_empty, COLOR_text_default);
	m_usernameicon->SetEnabled(true);
	m_passwordicon->SetEnabled(true);
	m_edit_username->SetEnabled(true);
	m_edit_password->SetEnabled(true);
	m_cbox_remember->SetEnabled(true);
	m_cbox_autologin->SetEnabled(true);
	m_btn_forgot->SetEnabled(true);
	m_btn_login->SetVisible(true);
	m_btn_login->SetEnabled(true);
	m_btn_cancel->SetVisible(false);
	m_btn_cancel->SetEnabled(false);
	// 设置默认焦点
	m_edit_username->SetFocus();
}

void LoginForm::DoLogin()
{
	std::string username = m_edit_username->GetUTF8Text();
	ui::StringHelper::Trim(username);
	if (username.empty()) {
		SetLoginTip(TXT_input_username, COLOR_red);
		m_usernameicon->SetEnabled(false);
		m_edit_username->SetFocus();
		return;
	}
	std::string password = m_edit_password->GetUTF8Text();
	ui::StringHelper::Trim(password);
	if (password.empty()) {
		SetLoginTip(TXT_input_password, COLOR_red);
		m_passwordicon->SetEnabled(false);
		m_edit_password->SetFocus();
		return;
	}

	// 取消界面焦点
	KillFocus();
	// 界面控件效果
	SetLoginTip(TXT_login_ing, COLOR_text_default);
	m_usernameicon->SetEnabled(true);
	m_passwordicon->SetEnabled(true);
	m_edit_username->SetEnabled(false);
	m_edit_password->SetEnabled(false);
	m_cbox_remember->SetEnabled(false);
	m_cbox_autologin->SetEnabled(false);
	m_btn_forgot->SetEnabled(false);
	m_btn_login->SetVisible(false);
	m_btn_login->SetEnabled(false);
	m_btn_cancel->SetVisible(true);
	m_btn_cancel->SetEnabled(true);
}

void LoginForm::SetLoginTip(const std::wstring& text, const std::wstring& textcolor)
{
	m_login_tip->SetText(text);
	m_login_tip->SetStateTextColor(ui::kControlStateNormal, textcolor);
}
