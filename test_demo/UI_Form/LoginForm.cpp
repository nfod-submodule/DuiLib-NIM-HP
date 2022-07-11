#include "stdafx.h"
#include "Resource.h"
#include "LoginForm.h"
#include "LoginKit.h"
#include "MainForm.h"
#include "Log4z.h"

//****************************/
//-- namespace NS_LoginForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_LoginForm_BEGIN	namespace NS_LoginForm {
#define NS_LoginForm_END	}
#define USING_NS_LoginForm	using namespace NS_LoginForm

NS_LoginForm_BEGIN

//-- 控件名称
CONST PWSTR WGT_title		= L"title";		// Label: 窗口标题
CONST PWSTR WGT_tip			= L"tip";		// Label: 提示信息
CONST PWSTR WGT_usericon	= L"usericon";	// Control: 帐号图标
CONST PWSTR WGT_passicon	= L"passicon";	// Control：密码图标
CONST PWSTR WGT_user		= L"user";		// RichEdit: 帐号
CONST PWSTR WGT_pass		= L"pass";		// RichEdit: 密码
CONST PWSTR WGT_keep		= L"keep";		// CheckBox: 记住密码
CONST PWSTR WGT_auto		= L"auto";		// CheckBox: 自动登录
CONST PWSTR WGT_regist		= L"regist";	// Button: 注册帐号
CONST PWSTR WGT_forgot		= L"forgot";	// Button: 找回密码
CONST PWSTR WGT_login		= L"login";		// Button: 登录
CONST PWSTR WGT_cancel		= L"cancel";	// Button: 取消登录

//-- 文本内容
CONST PWSTR TXT_empty			= L"";
CONST PWSTR TXT_input_user		= L"请输入帐号";
CONST PWSTR TXT_input_pass		= L"请输入密码";
CONST PWSTR TXT_login_req_fail	= L"登录请求失败";
CONST PWSTR TXT_login_ing		= L"正在登录...";
CONST PWSTR TXT_login_error		= L"登录错误";
CONST PWSTR TXT_pwd_chs_denied	= L"密码不允许含有中文字符";

NS_LoginForm_END
USING_NS_LoginForm;

//****************************/
//-- class LoginForm
//****************************/
//////////////////////////////////////////////////////////////////////////

void LoginForm::Close(UINT nRet /*= IDOK*/)
{
	// 注销窗口的回调函数
	LoginKit::GetInstance()->UnregisterCallback();
	__super::Close(nRet);
}

void LoginForm::InitWindow()
{
	// 设置图标与任务栏标题
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::Login_WindowTitle);

	// 根据控件名称查找控件
	m_title    = (ui::Label*)   FindControl(WGT_title);
	m_tip      = (ui::Label*)   FindControl(WGT_tip);
	m_usericon = (ui::Control*) FindControl(WGT_usericon);
	m_passicon = (ui::Control*) FindControl(WGT_passicon);
	m_user     = (ui::RichEdit*)FindControl(WGT_user);
	m_pass     = (ui::RichEdit*)FindControl(WGT_pass);
	m_keep     = (ui::CheckBox*)FindControl(WGT_keep);
	m_auto     = (ui::CheckBox*)FindControl(WGT_auto);
	m_regist   = (ui::Button*)  FindControl(WGT_regist);
	m_forgot   = (ui::Button*)  FindControl(WGT_forgot);
	m_login    = (ui::Button*)  FindControl(WGT_login);
	m_cancel   = (ui::Button*)  FindControl(WGT_cancel);

	// 注册窗口的回调函数
	LoginKit::GetInstance()->RegisterCallback(
		ToWeakCallback(std::bind<void>(&LoginForm::OnError, this, std::placeholders::_1)),
		ToWeakCallback(std::bind<void>(&LoginForm::OnCancel, this)),
		ToWeakCallback(std::bind<void>(&LoginForm::OnShowMain, this)));

	// 注册事件的回调函数
	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&LoginForm::OnEventAll, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&LoginForm::OnEventClick, this, std::placeholders::_1));

	// 冻结Tab键
	SetFreezeTab(true);
	// 设置控件效果（初始状态）
	SetEffect(false);
	// 设置窗口标题
	m_title->SetText(ConfUI::Login_WindowTitle);
	// 清空提示信息
	SetTip(TXT_empty, COLOR_text_default);
	// 设置默认焦点
	m_user->SetFocus();
	// 设置获取焦点后是否选择所有内容
	m_user->SetSelAllOnFocus(true);
	m_pass->SetSelAllOnFocus(true);
	// 设置限制字符数量
	m_user->SetLimitText(64);
	m_pass->SetLimitText(128);
	// 设置复选框默认选中
	m_keep->Selected(true);
	m_auto->Selected(true);
	// 设置默认帐号与密码
	m_user->SetUTF8Text(the_user);
	m_pass->SetUTF8Text(the_pass);
}

bool LoginForm::OnEventAll(ui::EventArgs* msg)
{
	switch (msg->Type)
	{
	case ui::kEventTextChange:
		return OnEventTextChange(msg->pSender->GetName());
	case ui::kEventTab:
		return OnEventTab();
	case ui::kEventReturn:
		return OnEventReturn();
	case ui::kEventSelect:
		return OnEventSelect(msg->pSender->GetName());
	case ui::kEventUnSelect:
		return OnEventUnSelect(msg->pSender->GetName());
	default:
		break;
	}
	return true;
}

bool LoginForm::OnEventTextChange(const std::wstring& sSenderName)
{
	if (sSenderName == WGT_user)
	{
		// 清空提示信息
		SetTip(TXT_empty, COLOR_text_default);
		// 图标正常状态
		m_usericon->SetEnabled(true);
		m_passicon->SetEnabled(true);
	}
	else if (sSenderName == WGT_pass)
	{
		// 去掉中文字符
		std::wstring pwd_fixed;
		std::wstring pwd = m_pass->GetText();
		for (size_t i = 0; i < pwd.length(); ++i) {
			if (ui::IsAsciiChar(pwd.at(i))) {
				pwd_fixed.push_back(pwd.at(i));
			}
		}
		m_pass->SetText(pwd_fixed);
		// 更新提示信息
		if (pwd == pwd_fixed) {
			SetTip(TXT_empty, COLOR_text_default);
		}
		else {
			SetTip(TXT_pwd_chs_denied, COLOR_red);
		}
		// 图标正常状态
		m_usericon->SetEnabled(true);
		m_passicon->SetEnabled(true);
	}
	return true;
}

bool LoginForm::OnEventTab()
{
	if (m_user->IsFocused())
	{
		m_pass->SetSelAll();
		m_pass->SetFocus();
	}
	else if (m_pass->IsFocused())
	{
		m_user->SetSelAll();
		m_user->SetFocus();
	}
	return true;
}

bool LoginForm::OnEventReturn()
{
	if (m_login->IsVisible() && m_login->IsEnabled())
	{
		DoLogin();
	}
	return true;
}

bool LoginForm::OnEventSelect(const std::wstring& sSenderName)
{
	if (sSenderName == WGT_auto)
	{
		m_keep->Selected(true);
	}
	return true;
}

bool LoginForm::OnEventUnSelect(const std::wstring& sSenderName)
{
	if (sSenderName == WGT_keep)
	{
		m_auto->Selected(false);
	}
	return true;
}

bool LoginForm::OnEventClick(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_login)
	{
		DoLogin();
	}
	else if (sSenderName == WGT_cancel)
	{
		LoginKit::GetInstance()->DoCancel();
	}
	return true;
}

void LoginForm::OnError(const std::wstring& error)
{
	SetEffect(false);
	SetTip(error, COLOR_red);
}

void LoginForm::OnCancel()
{
	SetEffect(false);
	SetTip(TXT_empty, COLOR_text_default);
}

void LoginForm::OnShowMain()
{
	// 隐藏登录窗口
	::ShowWindow(GetHWND(), SW_HIDE);
	// 显示主窗口
	MainForm::Show();
	// 销毁登录窗口
	::DestroyWindow(GetHWND());
}

void LoginForm::DoLogin()
{
	// 帐号
	std::string user = m_user->GetUTF8Text();
	ui::StringHelper::Trim(user);
	if (user.empty()) {
		SetTip(TXT_input_user, COLOR_red);
		m_usericon->SetEnabled(false);
		m_user->SetFocus();
		return;
	}
	// 密码
	std::string pass = m_pass->GetUTF8Text();
	ui::StringHelper::Trim(pass);
	if (pass.empty()) {
		SetTip(TXT_input_pass, COLOR_red);
		m_passicon->SetEnabled(false);
		m_pass->SetFocus();
		return;
	}

	// 取消界面焦点
	KillFocus();
	// 设置提示信息
	SetTip(TXT_login_ing, COLOR_text_default);
	// 界面控件效果（正在登录）
	SetEffect(true);

	// 登录请求
	bool bReq = LoginKit::GetInstance()->DoLogin(user, pass);
	if (!bReq) {
		// 设置提示信息
		SetTip(TXT_login_req_fail, COLOR_red);
		// 界面控件效果（初始状态）
		SetEffect(false);
	}
}

void LoginForm::SetTip(const std::wstring& text, const std::wstring& textcolor)
{
	m_tip->SetText(text);
	m_tip->SetStateTextColor(ui::kControlStateNormal, textcolor);
}

void LoginForm::SetEffect(bool bLogging)
{
	if (bLogging) {
		m_usericon->SetEnabled(true);
		m_passicon->SetEnabled(true);
		m_user->SetEnabled(false);
		m_pass->SetEnabled(false);
		m_keep->SetEnabled(false);
		m_auto->SetEnabled(false);
		m_regist->SetEnabled(false);
		m_forgot->SetEnabled(false);
		m_login->SetVisible(false);
		m_login->SetEnabled(false);
		m_cancel->SetVisible(true);
		m_cancel->SetEnabled(true);
	}
	else {
		m_usericon->SetEnabled(true);
		m_passicon->SetEnabled(true);
		m_user->SetEnabled(true);
		m_pass->SetEnabled(true);
		m_keep->SetEnabled(true);
		m_auto->SetEnabled(true);
		m_regist->SetEnabled(true);
		m_forgot->SetEnabled(true);
		m_login->SetVisible(true);
		m_login->SetEnabled(true);
		m_cancel->SetVisible(false);
		m_cancel->SetEnabled(false);
	}
}
