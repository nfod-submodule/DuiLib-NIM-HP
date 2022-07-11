#pragma once

//****************************/
//-- class wnd_controls_kit
//****************************/
class wnd_controls_kit
{
public:
	SINGLETON_DEFINE(wnd_controls_kit);
	wnd_controls_kit();

public:
	typedef std::function<void(const std::wstring& error)> Callback_Error; // 错误提示

	/**
	 * 注册窗口的回调函数，用来让UI组件控制窗口行为，窗口初始化时调用此函数注册相关回调
	 * @param[in] cb_Error	错误提示
	 * @return void 无返回值
	 */
	void RegisterCallback(
		const Callback_Error& cb_Error);

	/**
	 * 注销窗口的回调函数，窗口退出时须调用
	 * @return void 无返回值
	 */
	void UnRegisterCallback();

private:
	// 响应窗口的回调函数
	void Invoke_Error(const std::wstring& error);

private:
	Callback_Error	m_cb_Error;
};
