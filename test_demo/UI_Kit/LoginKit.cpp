#include "stdafx.h"
#include "LoginKit.h"
#include "ConfUI.h"
#include "Log4z.h"

//****************************/
//-- class LoginKit
//****************************/
//////////////////////////////////////////////////////////////////////////

LoginKit::LoginKit()
	: m_cb_LoginError(nullptr)
	, m_cb_CancelLogin(nullptr)
	, m_cb_HideWindow(nullptr)
	, m_cb_DestroyWindow(nullptr)
	, m_cb_ShowMainWindow(nullptr)
	, m_status(eLoginStatus_NULL)
{

}

void LoginKit::RegisterCallback(
	const Callback_LoginError&     cb_LoginError,
	const Callback_CancelLogin&    cb_CancelLogin,
	const Callback_HideWindow&     cb_HideWindow,
	const Callback_DestroyWindow&  cb_DestroyWindow,
	const Callback_ShowMainWindow& cb_ShowMainWindow)
{
	m_cb_LoginError     = cb_LoginError;
	m_cb_CancelLogin    = cb_CancelLogin;
	m_cb_HideWindow     = cb_HideWindow;
	m_cb_DestroyWindow  = cb_DestroyWindow;
	m_cb_ShowMainWindow = cb_ShowMainWindow;
}

void LoginKit::DoLogin(const std::string& username, const std::string& password)
{
	LOGA_DEBUG("login start ... username = %s, password = %s", username.c_str(), password.c_str());
	m_status = eLoginStatus_LOGIN;
	m_username = username;
	m_password = password;

	// 登录验证（异步模拟）
	std::thread([this, username, password]() {
		for (int sec = 0; sec <= 2; ++sec) {
			LOGA_DEBUG("logging in ... %d s", sec);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		bool logined = 0 == username.compare("admin") && 0 == password.compare("123456");
		this->OnLoginCallback(username, logined);
	}).detach();
}

void LoginKit::CancelLogin()
{
	LOGA_DEBUG("cancel login ... username = %s, password = %s", m_username.c_str(), m_password.c_str());
	m_status = eLoginStatus_CANCEL;
}

void LoginKit::OnLoginCallback(std::string username, bool logined)
{
	LOGA_DEBUG("[cb]: username = %s, logined = %s", username.c_str(), logined ? "true" : "false");
	auto callback_ui = std::bind<void>(&LoginKit::UILoginCallback, this, username, logined);
	nbase::ThreadManager::PostTask(eThread_UI, callback_ui);
}

void LoginKit::UILoginCallback(std::string username, bool logined)
{
	LOGA_DEBUG("[ui]: username = %s, logined = %s", username.c_str(), logined ? "true" : "false");
	if (m_status == eLoginStatus_CANCEL)
	{
		m_status = eLoginStatus_NULL;
		m_username.clear();
		m_password.clear();
		LOGA_DEBUG("login cancelled");
		Invoke_CancelLogin();
	}
	else
	{
		if (logined)
		{
			m_status = eLoginStatus_SUCCESS;
			Invoke_HideWindow();
			Invoke_ShowMainWindow();
			Invoke_DestroyWindow();
		}
		else
		{
			m_status = eLoginStatus_NULL;
			m_username.clear();
			m_password.clear();
			Invoke_LoginError(123);
		}
	}
}

void LoginKit::Invoke_LoginError(int error)
{
	try {
		if (m_cb_LoginError) {
			m_cb_LoginError(error);
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_CancelLogin()
{
	try {
		if (m_cb_CancelLogin) {
			m_cb_CancelLogin();
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_HideWindow()
{
	try {
		if (m_cb_HideWindow) {
			m_cb_HideWindow();
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_DestroyWindow()
{
	try {
		if (m_cb_DestroyWindow) {
			m_cb_DestroyWindow();
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_ShowMainWindow()
{
	try {
		if (m_cb_ShowMainWindow) {
			m_cb_ShowMainWindow();
		}
	}
	catch (const std::exception&) {}
}
