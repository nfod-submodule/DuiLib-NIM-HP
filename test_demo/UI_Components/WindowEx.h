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
public:
	WindowEx();
	virtual ~WindowEx();

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
	/**
	 * 获取窗口类名的接口
	 * @return wstring 窗口类名
	 */
	virtual std::wstring GetWindowClassName(void) const = 0;

	/**
	 * 获取窗口id的接口
	 * @return wstring 窗口id
	 */
	virtual std::wstring GetWindowId(void) const = 0;
};

NS_UI_COMP_END