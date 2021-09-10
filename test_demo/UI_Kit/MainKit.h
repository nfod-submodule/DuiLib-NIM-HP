#pragma once

//****************************/
//-- class MainKit
//****************************/
class MainKit
{
public:
	SINGLETON_DEFINE(MainKit);
	MainKit();

	typedef std::function<void(std::wstring ProjectId, bool bAuth)> Callback_DevAuth;	// 设备授权回调

public:
	/**
	 * 注册窗口的回调函数，用来让UI组件控制窗口行为，窗口初始化时调用此函数注册相关回调
	 * @param[in] cb_DevAuth	设备授权回调函数
	 * @return void 无返回值
	 */
	void RegisterCallback(
		const Callback_DevAuth& cb_DevAuth);
	
	/**
	 * 注销窗口的回调函数，窗口退出时须调用
	 * @return void 无返回值
	 */
	void UnRegisterCallback();

public:
	/**
	 * 申请设备授权
	 * @param[in] ProjectId 项目Id
	 * @return void	无返回值
	 */
	void DoApplyDevAuth(std::wstring ProjectId);

private:
	Callback_DevAuth m_cb_DevAuth;
};
