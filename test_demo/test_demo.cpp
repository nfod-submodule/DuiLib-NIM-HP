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
	// �й�UI�߳�
	nbase::ThreadManager::RegisterThread(eThread_UI);
}

void UIThread::Cleanup()
{
	// �ͷ���Դ
	ui::GlobalManager::Shutdown();
	// ��ȫ�˳��߳�
	SetThreadWasQuitProperly(true);
	// ȡ���й��߳�
	nbase::ThreadManager::UnregisterThread();
}
