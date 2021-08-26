#pragma once

#include "UIlib.h"
#include "ConfUI_Components.h"

NS_UI_COMP_BEGIN

//-- 窗体基类
//****************************/
//-- class WindowEx
//****************************/
class WindowEx : public ui::WindowImplBase
{
protected:
	WindowEx(const std::wstring& wnd_class_name, const std::wstring& wnd_id)
		: m_wnd_class_name(wnd_class_name), m_wnd_id(wnd_id) {}
	virtual ~WindowEx() {}

public:
	/**
	 * 获取窗口类名的接口
	 * @return wstring 窗口类名
	 */
	virtual std::wstring GetWindowClassName() const override { return m_wnd_class_name; }

	/**
	 * 获取窗口id的接口
	 * @return wstring 窗口id
	 */
	virtual std::wstring GetWindowId() const { return m_wnd_id; }

	/**
	 * 创建窗口
	 * @param[in] hwndParent 父窗口句柄
	 * @param[in] pstrName 窗口名称
	 * @param[in] dwStyle 窗口样式
	 * @param[in] dwExStyle 窗口扩展样式
	 * @param[in] isLayeredWindow 是否创建分层窗口
	 * @param[in] rc 窗口位置
	 * @return HWND 窗口句柄
	 */
	virtual HWND Create(
		HWND hwndParent,
		LPCTSTR pstrName,
		DWORD dwStyle,
		DWORD dwExStyle,
		bool isLayeredWindow = true,
		const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

	/**
	 * 处理窗口被销毁的消息
	 * @param[in] uMsg 消息
	 * @param[in] wParam 参数
	 * @param[in] lParam 参数
	 * @param[out] bHandled 消息是否被处理
	 * @return LRESULT 处理结果
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	/**
	 * 处理窗口消息
	 * @param[in] uMsg 消息
	 * @param[in] wParam 参数
	 * @param[in] lParam 参数
	 * @return LRESULT 处理结果
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	/**
	 * 处理ESC键单击的消息
	 * @param[out] bHandled 消息是否被处理
	 * @return void 无返回值
	 */
	virtual void OnEsc(BOOL &bHandled);

protected:
	std::wstring m_wnd_class_name;	// 窗口类名
	std::wstring m_wnd_id;			// 窗口id
};

NS_UI_COMP_END