#pragma once

//-- 线程标识
enum EThreadId
{
	eThread_UI	// UI线程（主线程）
};

//-- 文本配置
namespace TextUI
{
	// LoginForm - 登录窗口
	extern const wchar_t* Login_SkinFolder;
	extern const wchar_t* Login_SkinFile;
	extern const wchar_t* Login_ClassName;
	extern const wchar_t* Login_WindowName;
}
