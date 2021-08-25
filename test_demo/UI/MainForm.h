#pragma once

#include "ConfUI.h"
#include "WindowEx.h"

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui_comp::WindowEx
{
public:
	MainForm();
	~MainForm();

	/**
	 * 以下四个接口是必须要覆写的接口，父类会调用这四个接口来构建窗口
	 * GetSkinFolder		接口设置要绘制的窗口皮肤资源路径
	 * GetSkinFile			接口设置要绘制的窗口的 xml 描述文件
	 * GetWindowClassName	接口设置窗口类名
	 * GetWindowId			接口设置窗口id
	 */
	virtual std::wstring GetSkinFolder() override			{ return ConfUI::Main_SkinFolder; }
	virtual std::wstring GetSkinFile() override				{ return ConfUI::Main_SkinFile; }
	virtual std::wstring GetWindowClassName() const override{ return ConfUI::Main_ClassName; }
	virtual std::wstring GetWindowId() const override		{ return ConfUI::Main_WindowId; }

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

