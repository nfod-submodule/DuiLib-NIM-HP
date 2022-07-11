#include "stdafx.h"
#include "Resource.h"
#include "wnd_controls.h"
#include "wnd_controls_kit.h"

//****************************/
//-- namespace NS_wnd_controls
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_wnd_controls_BEGIN	namespace NS_wnd_controls {
#define NS_wnd_controls_END	}
#define USING_NS_wnd_controls	using namespace NS_wnd_controls

NS_wnd_controls_BEGIN

//-- 控件名称
CONST PWSTR WGT_title			= L"title";				// Label: 窗口标题
CONST PWSTR WGT_my_date			= L"my_date";			// DateTime: 日期格式
CONST PWSTR WGT_my_time			= L"my_time";			// DateTime: 时间格式
CONST PWSTR WGT_print_datetime	= L"print_datetime";	// Button: 打印

NS_wnd_controls_END
USING_NS_wnd_controls;

//****************************/
//-- class wnd_controls
//****************************/
//////////////////////////////////////////////////////////////////////////

void wnd_controls::Close(UINT nRet /*= IDOK*/)
{
	// 注销窗口的回调函数
	wnd_controls_kit::GetInstance()->UnRegisterCallback();
	__super::Close(nRet);
}

void wnd_controls::InitWindow()
{
	// 设置图标与任务栏标题
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::controls_WindowTitle);

	// 根据控件名称查找控件
	m_title          = (ui::Label*)   FindControl(WGT_title);
	m_my_date        = (ui::DateTime*)FindControl(WGT_my_date);
	m_my_time        = (ui::DateTime*)FindControl(WGT_my_time);
	m_print_datetime = (ui::Button*)  FindControl(WGT_print_datetime);

	// 注册窗口的回调函数
	wnd_controls_kit::GetInstance()->RegisterCallback(
		ToWeakCallback(std::bind<void>(&wnd_controls::OnError, this, std::placeholders::_1)));

	// 注册事件的回调函数
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&wnd_controls::OnEventClick, this, std::placeholders::_1));

	// 设置窗口标题
	m_title->SetText(ConfUI::controls_WindowTitle);
}

bool wnd_controls::OnEventClick(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_print_datetime)
	{
		const SYSTEMTIME& my_date = m_my_date->GetTime();
		const SYSTEMTIME& my_time = m_my_time->GetTime();
	}
	return true;
}

void wnd_controls::OnError(const std::wstring& error)
{
	// fix later
}
