#pragma once

//****************************/
//-- class LoginKit
//****************************/
class LoginKit
{
public:
	SINGLETON_DEFINE(LoginKit);
	LoginKit();

	typedef std::function<void(int error)> Callback_LoginError;	// 登录错误回调
	typedef std::function<void()> Callback_CancelLogin;			// 取消登录回调
	typedef std::function<void()> Callback_HideWindow;			// 隐藏登录窗口
	typedef std::function<void()> Callback_DestroyWindow;		// 销毁登录窗口
	typedef std::function<void()> Callback_ShowMainWindow;		// 显示主窗口
	
	enum ELoginStatus
	{
		eLoginStatus_NULL		// 初始状态
		, eLoginStatus_LOGIN	// 正在登录
		, eLoginStatus_CANCEL	// 取消登录
		, eLoginStatus_SUCCESS	// 已经登录
		, eLoginStatus_EXIT		// 退出登录
	};

public:
	/**
	 * 注册窗口的回调函数，用来让UI组件控制窗口行为，窗口初始化时调用此函数注册相关回调
	 * @param[in] cb_LoginError		通知登录错误并返回错误原因的回调函数
	 * @param[in] cb_CancelLogin	通知取消登录的回调函数
	 * @param[in] cb_HideWindow		通知隐藏登录窗口的回调函数
	 * @param[in] cb_DestroyWindow	通知销毁登录窗口的回调函数
	 * @param[in] cb_ShowMainWindow	通知显示主窗口的回调函数
	 * @return void 无返回值
	 */
	void RegisterCallback(
		const Callback_LoginError&     cb_LoginError,
		const Callback_CancelLogin&    cb_CancelLogin,
		const Callback_HideWindow&     cb_HideWindow,
		const Callback_DestroyWindow&  cb_DestroyWindow,
		const Callback_ShowMainWindow& cb_ShowMainWindow);

	/**
	 * 注销窗口的回调函数，窗口退出时须调用
	 * @return void 无返回值
	 */
	void UnregisterCallback();

	/**
	 * 执行登录
	 * @param[in] username 帐号
	 * @param[in] password 密码
	 * @return void	无返回值
	 */
	void DoLogin(const std::string& username, const std::string& password);
	
	/**
	 * 取消登录
	 * @return void	无返回值
	 */
	void CancelLogin();
	
	/**
	 * 注销登录
	 * @return void	无返回值
	 */
	void DoLogout();

private:
	/**
	 * 登录回调
	 * @param[in] username 帐号
	 * @param[in] logined 是否登录成功
	 * @return void	无返回值
	 */
	void OnLoginCallback(std::string username, bool logined);
	void UILoginCallback(std::string username, bool logined);

private:
	// 通知响应登录窗口的回调函数
	void Invoke_LoginError(int error);
	void Invoke_CancelLogin();
	void Invoke_HideWindow();
	void Invoke_DestroyWindow();
	void Invoke_ShowMainWindow();

private:
	Callback_LoginError     m_cb_LoginError;
	Callback_CancelLogin    m_cb_CancelLogin;
	Callback_HideWindow     m_cb_HideWindow;
	Callback_DestroyWindow  m_cb_DestroyWindow;
	Callback_ShowMainWindow m_cb_ShowMainWindow;

	ELoginStatus m_status;		// 登录状态
	std::string  m_username;	// 帐号
	std::string  m_password;	// 密码
};
