#pragma once

//-- 文本颜色
#define COLOR_text_default	L"textdefaultcolor"
#define COLOR_red			L"red"
#define COLOR_link_blue		L"link_blue"

//-- 线程标识
enum EThreadId
{
	eThread_UI = ui_comp::ThreadId::kThreadUI	// UI线程（主线程）
};

//-- 配置UI
// WindowTitle	窗口标题
// SkinFolder	资源路径
// SkinFile		描述文件
// ClassName	窗口类名
// WindowId		窗口id
namespace ConfUI
{
	// LoginForm - 登录
	static const wchar_t* Login_WindowTitle	= L"登录";
	static const wchar_t* Login_SkinFolder	= L"_ui_login";
	static const wchar_t* Login_SkinFile	= L"login.xml";
	static const wchar_t* Login_ClassName	= L"login";
	static const wchar_t* Login_WindowId	= L"login";

	// MainForm - 主窗口
	static const wchar_t* Main_WindowTitle	= L"main";
	static const wchar_t* Main_SkinFolder	= L"_ui_main";
	static const wchar_t* Main_SkinFile		= L"main.xml";
	static const wchar_t* Main_ClassName	= L"main";
	static const wchar_t* Main_WindowId		= L"main";
}
