#pragma once

//****************************/
//-- class LoginKit
//****************************/
class LoginKit
{
public:
	SINGLETON_DEFINE(LoginKit);
	LoginKit() {};
	~LoginKit() {};

public:
	/**
	 * 执行登录操作
	 * @param[in] username 帐号
	 * @param[in] password 密码
	 * @return void	无返回值
	 */
	void DoLogin(const std::string& username, const std::string& password);

private:
	/**
	 * 登录回调
	 * @param[in] logined 是否登录成功
	 * @param[in] username 帐号
	 * @return void	无返回值
	 */
	void OnLoginCallback(std::string username, bool logined);

	/**
	 * 登录回调（UI）
	 * @param[in] logined 是否登录成功
	 * @param[in] username 帐号
	 * @return void	无返回值
	 */
	void UILoginCallback(std::string username, bool logined);
};
