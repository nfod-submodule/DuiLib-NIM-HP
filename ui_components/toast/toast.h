#pragma once

#include "windows_manager/window_ex.h"
#include "windows_manager/windows_manager.h"

NS_UI_COMP_BEGIN

// 简易的提示窗口，相当于MessageBox的简化版
//****************************/
//-- class Toast
//****************************/
class Toast : public WindowEx
{
public:
	/**
	 * 在屏幕中间显示提示框
	 * @param[in] content 提示内容
	 * @param[in] duration 持续时间(毫秒),0代表一直显示
	 * @param[in] hWndParent 父窗口句柄，如果提供的话toast会显示在父窗口的中心
	 * @return void 无返回值
	 */
	static void Show(
		const std::wstring& content,
		int duration = 0,
		HWND hWndParent = NULL)
	{
		Toast* pWnd = WindowExMgr::ShowNewWindow<Toast>(
			hWndParent,
			TRUE,
			ConfUI_Components::Toast_ClassName,
			ConfUI_Components::Toast_WindowId);
		if (pWnd) {
			pWnd->SetContent(content);
			pWnd->SetDuration(duration);
		}
	}

public:
	Toast(const std::wstring& wnd_id)
		: WindowEx(
			FL_NULL,
			ConfUI_Components::Toast_SkinFolder,
			ConfUI_Components::Toast_SkinFile,
			ConfUI_Components::Toast_ClassName,
			wnd_id) {}

public:
	virtual UINT GetClassStyle() const override { return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS); }

	/**
	 * 关闭窗口
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * 初始窗口
	 */
	virtual void InitWindow() override;

	/**
	 * 窗口消息的派发函数
	 * @param[in] uMsg 消息类型
	 * @param[in] wParam 消息附加参数
	 * @param[in] lParam 消息附加参数
	 * @return LRESULT 处理结果
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	/**
	 * 设置提示内容
	 * @param[in] str 提示内容
	 * @return void	无返回值
	 */
	void SetContent(const std::wstring& str);

	/**
	 * 设置窗口的显示时长
	 * @param[in] duration 持续时间，单位毫秒
	 * @return void	无返回值
	 */
	void SetDuration(int duration);

private:
	ui::RichEdit*	m_content;
	ui::Button*		m_close_btn;
};

//****************************/
//-- class Toast_Kit
//****************************/
class Toast_Kit
{
public:
	SINGLETON_DEFINE(Toast_Kit);
	Toast_Kit() {}

public:
	/**
	 * 设置窗口的显示时长
	 * @param[in] pWnd 窗口指针
	 * @param[in] duration 持续时间，单位毫秒
	 * @return void 无返回值
	 */
	void SetDuration(
		Toast* pWnd,
		int duration);

	/**
	 * 取消窗口的显示时长（到时不再响应）
	 * @param[in] pWnd 窗口指针
	 * @return void 无返回值
	 */
	void DelDuration(
		Toast* pWnd);

private:
	/**
	 * 达到显示时长后关闭窗口
	 * @param[in] pWnd 窗口指针
	 * @return void 无返回值
	 */
	void Duration_ToClose(
		Toast* pWnd);

private:
	// map<窗口指针, 持续时间>
	std::mutex m_mutexWnd;
	std::map<Toast*, int> m_mapWnd;
};

NS_UI_COMP_END