#pragma once

//****************************/
//-- class MainKit
//****************************/
class MainKit
{
public:
	SINGLETON_DEFINE(MainKit);
	MainKit();

	typedef std::function<void(std::wstring ProjectId, bool bAuth)> Callback_DevAuth;	// �豸��Ȩ�ص�

public:
	/**
	 * ע�ᴰ�ڵĻص�������������UI������ƴ�����Ϊ�����ڳ�ʼ��ʱ���ô˺���ע����ػص�
	 * @param[in] cb_DevAuth	�豸��Ȩ�ص�����
	 * @return void �޷���ֵ
	 */
	void RegisterCallback(
		const Callback_DevAuth& cb_DevAuth);
	
	/**
	 * ע�����ڵĻص������������˳�ʱ�����
	 * @return void �޷���ֵ
	 */
	void UnRegisterCallback();

public:
	/**
	 * �����豸��Ȩ
	 * @param[in] ProjectId ��ĿId
	 * @return void	�޷���ֵ
	 */
	void DoApplyDevAuth(std::wstring ProjectId);

private:
	Callback_DevAuth m_cb_DevAuth;
};
