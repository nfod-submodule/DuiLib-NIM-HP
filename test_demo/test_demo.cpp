#include "stdafx.h"
#include "test_demo.h"
#include "ConfUI.h"
#include "Console.h"
#include "Log4z.h"
#include "Util.h"
#include "TrayMenu.h"
#include "LoginForm.h"

#ifdef _DEBUG
#include "vld.h"
#endif

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	OnInit();

	do  {
		UIThread td;
		td.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	} while (0);

	OnExit();

	return 0;
}

bool OnInit()
{
	// 打开控制台
	Console::Open();
	// 日志系统
	do  {
		std::string logPathAnsi = Util::GetAppDirA() + "logs\\";
		LoggerId logid = LOG4Z_MAIN_LOGGER_ID;
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerDisplay(logid, true);
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerOutFile(logid, true);
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerMonthdir(logid, true);
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerFileLine(logid, true);
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerName(logid, "LOG");
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerPath(logid, logPathAnsi.c_str());
		zsummer::log4z::ILog4zManager::getInstance()->setLoggerLevel(logid, LOG_LEVEL_TRACE);
		zsummer::log4z::ILog4zManager::getInstance()->start();
	} while (0);
	return true;
}

void OnExit()
{
	// 关闭控制台
	Console::Close();
}

//****************************/
//-- class UIThread
//****************************/
//////////////////////////////////////////////////////////////////////////

void UIThread::Init()
{
	// 托管UI线程
	nbase::ThreadManager::RegisterThread(eThread_UI);

	// 获取资源路径，初始化全局参数
	std::wstring resPath = Util::GetAppDirW() + L"resources\\";
	std::wstring skin = L"skin";
	std::wstring lang = L"lang\\zh_CN";
	ui::GlobalManager::Startup(resPath, ui::CreateControlCallback(), false, skin, lang);

	// 创建托盘
	TrayMenu::GetInstance()->Create();
	// 显示登录窗口
	LoginForm::Show();
}

void UIThread::Cleanup()
{
	// 销毁托盘
	TrayMenu::GetInstance()->Destroy();
	// 释放资源
	ui::GlobalManager::Shutdown();
	// 安全退出线程
	SetThreadWasQuitProperly(true);
	// 取消托管线程
	nbase::ThreadManager::UnregisterThread();
}
