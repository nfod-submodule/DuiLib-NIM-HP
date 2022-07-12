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

//-- �ؼ�����
CONST PWSTR WGT_title		= L"title";		// Label: ���ڱ���
CONST PWSTR WGT_tip			= L"tip";		// Label: ��ʾ��Ϣ
CONST PWSTR WGT_usericon	= L"usericon";	// Control: �ʺ�ͼ��
CONST PWSTR WGT_passicon	= L"passicon";	// Control������ͼ��
CONST PWSTR WGT_user		= L"user";		// RichEdit: �ʺ�
CONST PWSTR WGT_pass		= L"pass";		// RichEdit: ����
CONST PWSTR WGT_keep		= L"keep";		// CheckBox: ��ס����
CONST PWSTR WGT_auto		= L"auto";		// CheckBox: �Զ���¼
CONST PWSTR WGT_regist		= L"regist";	// Button: ע���ʺ�
CONST PWSTR WGT_forgot		= L"forgot";	// Button: �һ�����
CONST PWSTR WGT_login		= L"login";		// Button: ��¼
CONST PWSTR WGT_cancel		= L"cancel";	// Button: ȡ����¼

//-- �ı�����
CONST PWSTR TXT_empty			= L"";
CONST PWSTR TXT_input_user		= L"�������ʺ�";
CONST PWSTR TXT_input_pass		= L"����������";
CONST PWSTR TXT_login_req_fail	= L"��¼����ʧ��";
CONST PWSTR TXT_login_ing		= L"���ڵ�¼...";
CONST PWSTR TXT_login_error		= L"��¼����";
CONST PWSTR TXT_pwd_chs_denied	= L"���벻�����������ַ�";

NS_LoginForm_END
USING_NS_LoginForm;

//****************************/
//-- class LoginForm
//****************************/
//////////////////////////////////////////////////////////////////////////

void LoginForm::Close(UINT nRet /*= IDOK*/)
{
	// ע�����ڵĻص�����
	LoginKit::GetInstance()->UnregisterCallback();
	__super::Close(nRet);
}

void LoginForm::InitWindow()
{
	// ����ͼ��������������
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::Login_WindowTitle);

	// ���ݿؼ����Ʋ��ҿؼ�
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

	// ע�ᴰ�ڵĻص�����
	LoginKit::GetInstance()->RegisterCallback(
		ToWeakCallback(std::bind<void>(&LoginForm::OnError, this, std::placeholders::_1)),
		ToWeakCallback(std::bind<void>(&LoginForm::OnCancel, this)),
		ToWeakCallback(std::bind<void>(&LoginForm::OnShowMain, this)));

	// ע���¼��Ļص�����
	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&LoginForm::OnEventAll, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&LoginForm::OnEventClick, this, std::placeholders::_1));

	// ����Tab��
	SetFreezeTab(true);
	// ���ÿؼ�Ч������ʼ״̬��
	SetEffect(false);
	// ���ô��ڱ���
	m_title->SetText(ConfUI::Login_WindowTitle);
	// �����ʾ��Ϣ
	SetTip(TXT_empty, COLOR_text_default);
	// ����Ĭ�Ͻ���
	m_user->SetFocus();
	// ���û�ȡ������Ƿ�ѡ����������
	m_user->SetSelAllOnFocus(true);
	m_pass->SetSelAllOnFocus(true);
	// ���������ַ�����
	m_user->SetLimitText(64);
	m_pass->SetLimitText(128);
	// ���ø�ѡ��Ĭ��ѡ��
	m_keep->Selected(true);
	m_auto->Selected(true);
	// ����Ĭ���ʺ�������
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
		// �����ʾ��Ϣ
		SetTip(TXT_empty, COLOR_text_default);
		// ͼ������״̬
		m_usericon->SetEnabled(true);
		m_passicon->SetEnabled(true);
	}
	else if (sSenderName == WGT_pass)
	{
		// ȥ�������ַ�
		std::wstring pwd_fixed;
		std::wstring pwd = m_pass->GetText();
		for (size_t i = 0; i < pwd.length(); ++i) {
			if (ui::IsAsciiChar(pwd.at(i))) {
				pwd_fixed.push_back(pwd.at(i));
			}
		}
		m_pass->SetText(pwd_fixed);
		// ������ʾ��Ϣ
		if (pwd == pwd_fixed) {
			SetTip(TXT_empty, COLOR_text_default);
		}
		else {
			SetTip(TXT_pwd_chs_denied, COLOR_red);
		}
		// ͼ������״̬
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
	// ���ص�¼����
	::ShowWindow(GetHWND(), SW_HIDE);
	// ��ʾ������
	MainForm::Show();
	// ���ٵ�¼����
	::DestroyWindow(GetHWND());
}

void LoginForm::DoLogin()
{
	// �ʺ�
	std::string user = m_user->GetUTF8Text();
	ui::StringHelper::Trim(user);
	if (user.empty()) {
		SetTip(TXT_input_user, COLOR_red);
		m_usericon->SetEnabled(false);
		m_user->SetFocus();
		return;
	}
	// ����
	std::string pass = m_pass->GetUTF8Text();
	ui::StringHelper::Trim(pass);
	if (pass.empty()) {
		SetTip(TXT_input_pass, COLOR_red);
		m_passicon->SetEnabled(false);
		m_pass->SetFocus();
		return;
	}

	// ȡ�����潹��
	KillFocus();
	// ������ʾ��Ϣ
	SetTip(TXT_login_ing, COLOR_text_default);
	// ����ؼ�Ч�������ڵ�¼��
	SetEffect(true);

	// ��¼����
	bool bReq = LoginKit::GetInstance()->DoLogin(user, pass);
	if (!bReq) {
		// ������ʾ��Ϣ
		SetTip(TXT_login_req_fail, COLOR_red);
		// ����ؼ�Ч������ʼ״̬��
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
