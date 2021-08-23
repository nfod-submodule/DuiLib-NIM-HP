#include "stdafx.h"
#include "test_demo.h"
#include "ConfUI.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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
