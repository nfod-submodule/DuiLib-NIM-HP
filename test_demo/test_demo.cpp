#include "stdafx.h"
#include "test_demo.h"
#include "ConfUI.h"
#include "Util.h"
#include "LoginForm.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	do  {
		UIThread td;
		td.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	} while (0);

	return 0;
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
	// 设置使用本地文件夹作为资源（也可以使用资源中的压缩包作为资源）
	// 默认皮肤使用 resources\\themes\\default
	// 默认语言使用 resources\\lang\\zh_CN
	// 如需修改请指定 Startup 最后两个参数
	std::wstring resPath = Util::GetAppDir() + L"resources\\";
	ui::GlobalManager::Startup(resPath, ui::CreateControlCallback(), false);

	// 登录窗口
	LoginForm* window = new LoginForm();
	window->Create(NULL, NULL, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void UIThread::Cleanup()
{
	// 释放资源
	ui::GlobalManager::Shutdown();
	// 安全退出线程
	SetThreadWasQuitProperly(true);
	// 取消托管线程
	nbase::ThreadManager::UnregisterThread();
}
