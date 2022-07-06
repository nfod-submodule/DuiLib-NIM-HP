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
	typedef std::function<void(const std::wstring& error)> Callback_Error; // ������ʾ
	typedef std::function<void()> Callback_Cancel; // ȡ����¼
	typedef std::function<void()> Callback_ShowMain; // ��ʾ������

	/**
	 * ע�ᴰ�ڵĻص�������������UI������ƴ�����Ϊ�����ڳ�ʼ��ʱ���ô˺���ע����ػص�
	 * @param[in] cb_Error		������ʾ
	 * @param[in] cb_Cancel		ȡ����¼
	 * @param[in] cb_ShowMain	��ʾ������
	 * @return void �޷���ֵ
	 */
	void RegisterCallback(
		const Callback_Error&    cb_Error,
		const Callback_Cancel&   cb_Cancel,
		const Callback_ShowMain& cb_ShowMain);

	/**
	 * ע�����ڵĻص������������˳�ʱ�����
	 * @return void �޷���ֵ
	 */
	void UnregisterCallback();

public:
	// ִ�е�¼
	bool DoLogin(const std::string& user, const std::string& pass);
	// ȡ����¼
	void DoCancel();
	// ִ�еǳ�
	void DoLogout();

private:
	// ��¼�ص�
	void CB_Login(const std::string& user, bool logined);
	void UI_Login(const std::string& user, bool logined);

private:
	// ��Ӧ���ڵĻص�����
	void Invoke_Error(const std::wstring& error);
	void Invoke_Cancel();
	void Invoke_ShowMain();

private:
	Callback_Error		m_cb_Error;
	Callback_Cancel		m_cb_Cancel;
	Callback_ShowMain	m_cb_ShowMain;

	enum EStatus {
		eStatus_NULL		// ��ʼ״̬
		, eStatus_LOGGING	// ���ڵ�¼
		, eStatus_CANCEL	// ȡ����¼
		, eStatus_LOGIN		// �Ѿ���¼
		, eStatus_LOGOUT	// �Ѿ��ǳ�
	};
	EStatus m_status;	// ��¼״̬
};
