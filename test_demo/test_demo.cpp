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
	// �򿪿���̨
	Console::Open();
	// ��־ϵͳ
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
	// �رտ���̨
	Console::Close();
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
	std::wstring resPath = Util::GetAppDirW() + L"resources\\";
	std::wstring skin = L"skin";
	std::wstring lang = L"lang\\zh_CN";
	ui::GlobalManager::Startup(resPath, ui::CreateControlCallback(), false, skin, lang);

	// ��������
	TrayMenu::GetInstance()->Create();
	// ��ʾ��¼����
	LoginForm::Show();
}

void UIThread::Cleanup()
{
	// ��������
	TrayMenu::GetInstance()->Destroy();
	// �ͷ���Դ
	ui::GlobalManager::Shutdown();
	// ��ȫ�˳��߳�
	SetThreadWasQuitProperly(true);
	// ȡ���й��߳�
	nbase::ThreadManager::UnregisterThread();
}
