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
	typedef std::function<void(const std::wstring& error)> Callback_Error; // ������ʾ
	typedef std::function<void(const std::wstring& ProjectId, bool bAuth)> Callback_DevAuth; // �豸��Ȩ�ص�

	/**
	 * ע�ᴰ�ڵĻص�������������UI������ƴ�����Ϊ�����ڳ�ʼ��ʱ���ô˺���ע����ػص�
	 * @param[in] cb_Error		������ʾ
	 * @param[in] cb_DevAuth	�豸��Ȩ�ص�����
	 * @return void �޷���ֵ
	 */
	void RegisterCallback(
		const Callback_Error&   cb_Error,
		const Callback_DevAuth& cb_DevAuth);

	/**
	 * ע�����ڵĻص������������˳�ʱ�����
	 * @return void �޷���ֵ
	 */
	void UnregisterCallback();

public:
	// �����豸��Ȩ
	void DoApplyDevAuth(const std::wstring& ProjectId);

private:
	// ��Ӧ���ڵĻص�����
	void Invoke_Error(const std::wstring& error);
	void Invoke_DevAuth(const std::wstring& ProjectId, bool bAuth);

private:
	Callback_Error		m_cb_Error;
	Callback_DevAuth	m_cb_DevAuth;
};
