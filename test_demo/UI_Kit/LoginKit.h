#pragma once

//****************************/
//-- class LoginKit
//****************************/
class LoginKit
{
public:
	SINGLETON_DEFINE(LoginKit);
	LoginKit();

	typedef std::function<void(int error)> Callback_LoginError;	// ��¼����ص�
	typedef std::function<void()> Callback_CancelLogin;			// ȡ����¼�ص�
	typedef std::function<void()> Callback_HideWindow;			// ���ص�¼����
	typedef std::function<void()> Callback_DestroyWindow;		// ���ٵ�¼����
	typedef std::function<void()> Callback_ShowMainWindow;		// ��ʾ������
	
	enum ELoginStatus
	{
		eLoginStatus_NULL		// ��ʼ״̬
		, eLoginStatus_LOGIN	// ���ڵ�¼
		, eLoginStatus_CANCEL	// ȡ����¼
		, eLoginStatus_SUCCESS	// �Ѿ���¼
		, eLoginStatus_EXIT		// �˳���¼
	};

public:
	/**
	 * ע�ᴰ�ڵĻص�������������UI������ƴ�����Ϊ�����ڳ�ʼ��ʱ���ô˺���ע����ػص�
	 * @param[in] cb_LoginError		֪ͨ��¼���󲢷��ش���ԭ��Ļص�����
	 * @param[in] cb_CancelLogin	֪ͨȡ����¼�Ļص�����
	 * @param[in] cb_HideWindow		֪ͨ���ص�¼���ڵĻص�����
	 * @param[in] cb_DestroyWindow	֪ͨ���ٵ�¼���ڵĻص�����
	 * @param[in] cb_ShowMainWindow	֪ͨ��ʾ�����ڵĻص�����
	 * @return void �޷���ֵ
	 */
	void RegisterCallback(
		const Callback_LoginError&     cb_LoginError,
		const Callback_CancelLogin&    cb_CancelLogin,
		const Callback_HideWindow&     cb_HideWindow,
		const Callback_DestroyWindow&  cb_DestroyWindow,
		const Callback_ShowMainWindow& cb_ShowMainWindow);

	/**
	 * ע�����ڵĻص������������˳�ʱ�����
	 * @return void �޷���ֵ
	 */
	void UnregisterCallback();

	/**
	 * ִ�е�¼
	 * @param[in] username �ʺ�
	 * @param[in] password ����
	 * @return void	�޷���ֵ
	 */
	void DoLogin(const std::string& username, const std::string& password);
	
	/**
	 * ȡ����¼
	 * @return void	�޷���ֵ
	 */
	void CancelLogin();
	
	/**
	 * ע����¼
	 * @return void	�޷���ֵ
	 */
	void DoLogout();

private:
	/**
	 * ��¼�ص�
	 * @param[in] username �ʺ�
	 * @param[in] logined �Ƿ��¼�ɹ�
	 * @return void	�޷���ֵ
	 */
	void OnLoginCallback(std::string username, bool logined);
	void UILoginCallback(std::string username, bool logined);

private:
	// ֪ͨ��Ӧ��¼���ڵĻص�����
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

	ELoginStatus m_status;		// ��¼״̬
	std::string  m_username;	// �ʺ�
	std::string  m_password;	// ����
};
