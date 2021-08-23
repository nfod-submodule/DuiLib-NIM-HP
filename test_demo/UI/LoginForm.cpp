#include "stdafx.h"
#include "LoginForm.h"
#include "ConfUI.h"

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
	return TextUI::Login_SkinFolder;
}

std::wstring LoginForm::GetSkinFile()
{
	return TextUI::Login_SkinFile;
}

std::wstring LoginForm::GetWindowClassName() const
{
	return TextUI::Login_ClassName;
}

void LoginForm::InitWindow()
{
	SetTaskbarTitle(TextUI::Login_WindowName);
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
