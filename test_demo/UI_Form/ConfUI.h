#pragma once

//-- 线程标识
enum EThreadId
{
	eThread_UI	// UI线程（主线程）
};

//-- 配置
namespace ConfUI
{
	// LoginForm - 登录窗口
	static const wchar_t* Login_WindowName	= L"登录";
	static const wchar_t* Login_SkinFolder	= L"_ui_login";
	static const wchar_t* Login_SkinFile	= L"login.xml";
	static const wchar_t* Login_ClassName	= L"LoginForm";
	static const wchar_t* Login_WindowId	= L"12345678901234567890123456789012-LOGIN";

	// MainForm - 主窗口
	static const wchar_t* Main_WindowName	= L"main";
	static const wchar_t* Main_SkinFolder	= L"_ui_main";
	static const wchar_t* Main_SkinFile		= L"main.xml";
	static const wchar_t* Main_ClassName	= L"MainForm";
	static const wchar_t* Main_WindowId		= L"12345678901234567890123456789012-MAIN";
}
