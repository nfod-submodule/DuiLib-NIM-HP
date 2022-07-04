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
	: m_cb_DevAuth(nullptr)
{

}

void MainKit::RegisterCallback(
	const Callback_DevAuth& cb_DevAuth)
{
	m_cb_DevAuth = cb_DevAuth;
}

void MainKit::UnregisterCallback()
{
	m_cb_DevAuth = nullptr;
}

void MainKit::DoApplyDevAuth(std::wstring ProjectId)
{
	// 设备授权（异步模拟）
	std::thread([this, ProjectId]() {
		for (int sec = 0; sec <= 2; ++sec) {
			LOGW_DEBUG(L"[Id=%s] Applying for Device Authorization ... %d s", ProjectId.c_str(), sec);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		auto cb_task = [this, ProjectId]() {
			LOGW_DEBUG(L"[Id=%s] Device Authorized", ProjectId.c_str());
			try {
				if (m_cb_DevAuth) {
					m_cb_DevAuth(ProjectId, true);
				}
			}
			catch (const std::exception&) {}
		};
		nbase::ThreadManager::PostTask(eThread_UI, std::bind<void>(cb_task));
	}).detach();
}
