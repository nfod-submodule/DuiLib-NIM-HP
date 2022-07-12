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
	typedef std::function<void(const std::wstring& error)> Callback_Error; // ������ʾ

	/**
	 * ע�ᴰ�ڵĻص�������������UI������ƴ�����Ϊ�����ڳ�ʼ��ʱ���ô˺���ע����ػص�
	 * @param[in] cb_Error	������ʾ
	 * @return void �޷���ֵ
	 */
	void RegisterCallback(
		const Callback_Error& cb_Error);

	/**
	 * ע�����ڵĻص������������˳�ʱ�����
	 * @return void �޷���ֵ
	 */
	void UnRegisterCallback();

private:
	// ��Ӧ���ڵĻص�����
	void Invoke_Error(const std::wstring& error);

private:
	Callback_Error	m_cb_Error;
};
