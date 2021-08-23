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
	// �й�UI�߳�
	nbase::ThreadManager::RegisterThread(eThread_UI);

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	// ����ʹ�ñ����ļ�����Ϊ��Դ��Ҳ����ʹ����Դ�е�ѹ������Ϊ��Դ��
	// Ĭ��Ƥ��ʹ�� resources\\themes\\default
	// Ĭ������ʹ�� resources\\lang\\zh_CN
	// �����޸���ָ�� Startup �����������
	std::wstring resPath = Util::GetAppDir() + L"resources\\";
	ui::GlobalManager::Startup(resPath, ui::CreateControlCallback(), false);

	// ��¼����
	LoginForm* window = new LoginForm();
	window->Create(NULL, NULL, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
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
