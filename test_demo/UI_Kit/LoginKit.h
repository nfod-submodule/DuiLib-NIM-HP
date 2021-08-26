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
	 * ִ�е�¼����
	 * @param[in] username �ʺ�
	 * @param[in] password ����
	 * @return void	�޷���ֵ
	 */
	void DoLogin(const std::string& username, const std::string& password);

private:
	/**
	 * ��¼�ص�
	 * @param[in] logined �Ƿ��¼�ɹ�
	 * @param[in] username �ʺ�
	 * @return void	�޷���ֵ
	 */
	void OnLoginCallback(std::string username, bool logined);

	/**
	 * ��¼�ص���UI��
	 * @param[in] logined �Ƿ��¼�ɹ�
	 * @param[in] username �ʺ�
	 * @return void	�޷���ֵ
	 */
	void UILoginCallback(std::string username, bool logined);
};
