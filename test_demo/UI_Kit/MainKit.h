#pragma once

//****************************/
//-- class MainKit
//****************************/
class MainKit
{
public:
	SINGLETON_DEFINE(MainKit);
	MainKit();

public:
	typedef std::function<void(const std::wstring& error)> Callback_Error; // 错误提示
	typedef std::function<void(const std::wstring& ProjectId, bool bAuth)> Callback_DevAuth; // 设备授权回调

	/**
	 * 注册窗口的回调函数，用来让UI组件控制窗口行为，窗口初始化时调用此函数注册相关回调
	 * @param[in] cb_Error		错误提示
	 * @param[in] cb_DevAuth	设备授权回调函数
	 * @return void 无返回值
	 */
	void RegisterCallback(
		const Callback_Error&   cb_Error,
		const Callback_DevAuth& cb_DevAuth);

	/**
	 * 注销窗口的回调函数，窗口退出时须调用
	 * @return void 无返回值
	 */
	void UnregisterCallback();

public:
	// 申请设备授权
	void DoApplyDevAuth(const std::wstring& ProjectId);

private:
	// 响应窗口的回调函数
	void Invoke_Error(const std::wstring& error);
	void Invoke_DevAuth(const std::wstring& ProjectId, bool bAuth);

private:
	Callback_Error		m_cb_Error;
	Callback_DevAuth	m_cb_DevAuth;
};
