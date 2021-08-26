#include "stdafx.h"
#include "LoginKit.h"
#include "ConfUI.h"
#include "Log4z.h"

//****************************/
//-- class LoginKit
//****************************/
//////////////////////////////////////////////////////////////////////////

void LoginKit::DoLogin(const std::string& username, const std::string& password)
{
	LOGA_DEBUG("login start ... username = %s, password = %s", username.c_str(), password.c_str());
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

void LoginKit::OnLoginCallback(std::string username, bool logined)
{
	LOGA_DEBUG("[cb]: username = %s, logined = %s", username.c_str(), logined ? "true" : "false");
	auto callback_ui = std::bind<void>(&LoginKit::UILoginCallback, this, username, logined);
	nbase::ThreadManager::PostTask(eThread_UI, callback_ui);
}

void LoginKit::UILoginCallback(std::string username, bool logined)
{
	LOGA_DEBUG("[ui]: username = %s, logined = %s", username.c_str(), logined ? "true" : "false");
	// fix later
}
