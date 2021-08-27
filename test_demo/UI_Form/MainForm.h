#pragma once

#include "ConfUI.h"
#include "WindowExMgr.h"

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui_comp::WindowEx
{
public:
	static void SingletonShow() {
		ui_comp::WindowExMgr::GetInstance()->SingletonShow<MainForm>(ConfUI::Main_ClassName, ConfUI::Main_WindowId);
	}
public:
	MainForm(const std::wstring& wnd_id = ConfUI::Main_WindowId)
		: ui_comp::WindowEx(ConfUI::Main_ClassName, wnd_id) {}
	~MainForm() {}

	/**
	 * 以下两个接口是必须要覆写的接口，父类会调用来构建窗口
	 * GetSkinFolder	接口设置要绘制的窗口皮肤资源路径
	 * GetSkinFile		接口设置要绘制的窗口的 xml 描述文件
	 */
	virtual std::wstring GetSkinFolder() override { return ConfUI::Main_SkinFolder; }
	virtual std::wstring GetSkinFile() override   { return ConfUI::Main_SkinFile; }

	/**
	 * 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	 */
	virtual void InitWindow() override;

	/**
	 * 收到 WM_CLOSE 消息时该函数会被调用
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	/**
	 * 处理所有控件的所有消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnNotify(ui::EventArgs* msg);

	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	ui::Button*	m_btn_logout;
	ui::Button*	m_btn_exit;
};

