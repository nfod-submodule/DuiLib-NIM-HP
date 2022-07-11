#pragma once

#include "ConfUI.h"

//****************************/
//-- class wnd_controls
//****************************/
class wnd_controls : public ui_comp::WindowEx
{
public:
	/**
	 * 显示窗口
	 * @param[in] hWndParent 父窗口句柄，如果提供的话会显示在父窗口的中心，且为模态
	 * @return void 无返回值
	 */
	static void Show(HWND hWndParent)
	{
		int input_number = 123;
		std::string input_string = "abc";
		ui_comp::WindowExMgr::ShowNewWindow<wnd_controls>(
			hWndParent,
			FALSE,
			ConfUI::controls_ClassName,
			ConfUI::controls_WindowId,
			input_number,
			input_string);
	}

public:
	wnd_controls(
		const std::wstring& wnd_id,
		int input_number,
		const std::string& input_string)
		: ui_comp::WindowEx(
			FL_N_LAYERED | FL_SHADOWWND,
			ConfUI::controls_SkinFolder,
			ConfUI::controls_SkinFile,
			ConfUI::controls_ClassName,
			wnd_id)
	{
		printf("[wnd_controls]\n\t input_number: %d\n\t input_string: %s\n", input_number, input_string.c_str());
	}

public:
	/**
	 * 关闭窗口
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * 初始窗口
	 */
	virtual void InitWindow() override;

private:
	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	// 错误提示
	void OnError(const std::wstring& error);

private:
	ui::Label*		m_title;
	ui::DateTime*	m_my_date;
	ui::DateTime*	m_my_time;
	ui::Button*		m_print_datetime;
};
