#pragma once

#include "ConfUI.h"

//****************************/
//-- class LoginForm
//****************************/
class LoginForm : public ui_comp::WindowEx
{
public:
	static void Show()
	{
		ui_comp::WindowExMgr::ShowSingleton<LoginForm>(
			ConfUI::Login_ClassName,
			ConfUI::Login_WindowId);
	}

public:
	LoginForm(const std::wstring& wnd_id)
		: ui_comp::WindowEx(
			FL_QUIT,
			ConfUI::Login_SkinFolder,
			ConfUI::Login_SkinFile,
			ConfUI::Login_ClassName,
			wnd_id) {}

public:
	/**
	 * �رմ���
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * ��ʼ����
	 */
	virtual void InitWindow() override;

private:
	/**
	 * ע���¼���ڵĻص�����
	 * @return void	�޷���ֵ
	 */
	void RegisterCallback();

	/**
	 * �������пؼ���������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnNotify(ui::EventArgs* msg);
	void OnEventTextChange(const std::wstring& sSenderName);
	void OnEventTab();
	void OnEventReturn();

	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	/**
	 * ��Ӧ��¼����Ļص���
	 * @return void	�޷���ֵ
	 */
	void OnLoginError(int error);

	/**
	 * ��Ӧȡ����¼�Ļص������ý���ؼ�Ч��
	 * @return void	�޷���ֵ
	 */
	void OnCancelLogin();

	/**
	 * ִ�е�¼����
	 * @return void	�޷���ֵ
	 */
	void DoLogin();

	/**
	 * ������ʾ��Ϣ
	 * @param[in] text �ı�����
	 * @param[in] textcolor �ı���ɫ
	 * @return void	�޷���ֵ
	 */
	void SetLoginTip(const std::wstring& text, const std::wstring& textcolor);

private:
	ui::Label*		m_login_tip;
	ui::Control*	m_usernameicon;
	ui::Control*	m_passwordicon;
	ui::RichEdit*	m_edit_username;
	ui::RichEdit*	m_edit_password;
	ui::CheckBox*	m_cbox_remember;
	ui::CheckBox*	m_cbox_autologin;
	ui::Button*		m_btn_forgot;
	ui::Button*		m_btn_login;
	ui::Button*		m_btn_cancel;
};

