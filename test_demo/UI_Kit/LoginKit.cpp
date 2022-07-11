#include "stdafx.h"
#include "LoginKit.h"
#include "LoginForm.h"
#include "Log4z.h"

//****************************/
//-- class LoginKit
//****************************/
//////////////////////////////////////////////////////////////////////////

LoginKit::LoginKit()
	: m_status(eStatus_NULL)
{
	UnregisterCallback();
}

void LoginKit::RegisterCallback(
	const Callback_Error&    cb_Error,
	const Callback_Cancel&   cb_Cancel,
	const Callback_ShowMain& cb_ShowMain)
{
	m_cb_Error    = cb_Error;
	m_cb_Cancel   = cb_Cancel;
	m_cb_ShowMain = cb_ShowMain;
}

void LoginKit::UnregisterCallback()
{
	m_cb_Error    = nullptr;
	m_cb_Cancel   = nullptr;
	m_cb_ShowMain = nullptr;
}

bool LoginKit::DoLogin(const std::string& user, const std::string& pass)
{
	LOGA_DEBUG("login start ... user: %s, pass: %s", user.c_str(), pass.c_str());
	// 登录状态（正在登录）
	m_status = eStatus_LOGGING;
	// 登录验证（异步模拟）
	std::thread([this, user, pass]() {
		for (int sec = 0; sec <= 2; ++sec) {
			LOGA_DEBUG("logging in ... %d second", sec);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		bool logined = 0 == user.compare(the_user) && 0 == pass.compare(the_pass);
		this->CB_Login(user, logined);
	}).detach();
	return true;
}

void LoginKit::DoCancel()
{
	LOGA_DEBUG("cancel login ...");
	m_status = eStatus_CANCEL;
}

void LoginKit::DoLogout()
{
	LOGA_DEBUG("logout start ...");
	if (m_status == eStatus_LOGOUT) {
		return;
	}
	auto task = [this]()
	{
		LOGA_DEBUG("logging out ...");
		// 销毁所有窗口
		ui_comp::WindowExMgr::GetInstance()->DestroyAllWindows();
		// 重置数据
		m_status = eStatus_NULL;
		// 显示登录窗口
		LoginForm::Show();
	};
	nbase::ThreadManager::PostDelayedTask(eThread_UI, task, nbase::TimeDelta::FromMilliseconds(100));
}

void LoginKit::CB_Login(const std::string& user, bool logined)
{
	LOGA_DEBUG("[cb]: user: %s, logined: %s", user.c_str(), logined ? "true" : "false");
	auto task = std::bind<void>(&LoginKit::UI_Login, this, user, logined);
	nbase::ThreadManager::PostTask(eThread_UI, task);
}

void LoginKit::UI_Login(const std::string& user, bool logined)
{
	LOGA_DEBUG("[ui]: user: %s, logined: %s", user.c_str(), logined ? "true" : "false");
	if (m_status == eStatus_CANCEL)
	{
		LOGA_DEBUG("login cancelled");
		m_status = eStatus_NULL;
		Invoke_Cancel();
	}
	else if (logined)
	{
		LOGA_DEBUG("logined, show main window");
		m_status = eStatus_LOGIN;
		Invoke_ShowMain();
	}
	else
	{
		LOGA_DEBUG("login error");
		m_status = eStatus_NULL;
		Invoke_Error(L"登录失败");
	}
}

void LoginKit::Invoke_Error(const std::wstring& error)
{
	try {
		if (m_cb_Error) {
			m_cb_Error(error);
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_Cancel()
{
	try {
		if (m_cb_Cancel) {
			m_cb_Cancel();
		}
	}
	catch (const std::exception&) {}
}

void LoginKit::Invoke_ShowMain()
{
	try {
		if (m_cb_ShowMain) {
			m_cb_ShowMain();
		}
	}
	catch (const std::exception&) {}
}
