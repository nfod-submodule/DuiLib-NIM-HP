#pragma once

//****************************/
//-- class LoginKit
//****************************/
class LoginKit
{
public:
	SINGLETON_DEFINE(LoginKit);
	LoginKit();

public:
	typedef std::function<void(const std::wstring& error)> Callback_Error; // 错误提示
	typedef std::function<void()> Callback_Cancel; // 取消登录
	typedef std::function<void()> Callback_ShowMain; // 显示主窗口

	/**
	 * 注册窗口的回调函数，用来让UI组件控制窗口行为，窗口初始化时调用此函数注册相关回调
	 * @param[in] cb_Error		错误提示
	 * @param[in] cb_Cancel		取消登录
	 * @param[in] cb_ShowMain	显示主窗口
	 * @return void 无返回值
	 */
	void RegisterCallback(
		const Callback_Error&    cb_Error,
		const Callback_Cancel&   cb_Cancel,
		const Callback_ShowMain& cb_ShowMain);

	/**
	 * 注销窗口的回调函数，窗口退出时须调用
	 * @return void 无返回值
	 */
	void UnregisterCallback();

public:
	// 执行登录
	bool DoLogin(const std::string& user, const std::string& pass);
	// 取消登录
	void DoCancel();
	// 执行登出
	void DoLogout();

private:
	// 登录回调
	void CB_Login(const std::string& user, bool logined);
	void UI_Login(const std::string& user, bool logined);

private:
	// 响应窗口的回调函数
	void Invoke_Error(const std::wstring& error);
	void Invoke_Cancel();
	void Invoke_ShowMain();

private:
	Callback_Error		m_cb_Error;
	Callback_Cancel		m_cb_Cancel;
	Callback_ShowMain	m_cb_ShowMain;

	enum EStatus {
		eStatus_NULL		// 初始状态
		, eStatus_LOGGING	// 正在登录
		, eStatus_CANCEL	// 取消登录
		, eStatus_LOGIN		// 已经登录
		, eStatus_LOGOUT	// 已经登出
	};
	EStatus m_status;	// 登录状态
};
