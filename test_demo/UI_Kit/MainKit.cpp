#include "stdafx.h"
#include "MainKit.h"
#include "ConfUI.h"
#include "Log4z.h"
#include "MainForm.h"

//****************************/
//-- class MainKit
//****************************/
//////////////////////////////////////////////////////////////////////////

MainKit::MainKit()
{
	UnregisterCallback();
}

void MainKit::RegisterCallback(
	const Callback_Error&   cb_Error,
	const Callback_DevAuth& cb_DevAuth)
{
	m_cb_Error   = cb_Error;
	m_cb_DevAuth = cb_DevAuth;
}

void MainKit::UnregisterCallback()
{
	m_cb_Error   = nullptr;
	m_cb_DevAuth = nullptr;
}

void MainKit::DoApplyDevAuth(const std::wstring& ProjectId)
{
	// 设备授权（异步模拟）
	std::thread([this, ProjectId]() {
		for (int sec = 0; sec <= 2; ++sec) {
			LOGW_DEBUG(L"[Id=%s] Applying for Device Authorization ... %d second", ProjectId.c_str(), sec);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		bool bAuth = true;
		LOGW_DEBUG(L"[Id=%s] Device Authorized: %s", ProjectId.c_str(), bAuth ? L"true" : L"false");
		auto task = std::bind<void>(&MainKit::Invoke_DevAuth, this, ProjectId, bAuth);
		nbase::ThreadManager::PostTask(eThread_UI, task);
	}).detach();
}

void MainKit::Invoke_Error(const std::wstring& error)
{
	try {
		if (m_cb_Error) {
			m_cb_Error(error);
		}
	}
	catch (const std::exception&) {}
}

void MainKit::Invoke_DevAuth(const std::wstring& ProjectId, bool bAuth)
{
	try {
		if (m_cb_DevAuth) {
			m_cb_DevAuth(ProjectId, bAuth);
		}
	}
	catch (const std::exception&) {}
}
