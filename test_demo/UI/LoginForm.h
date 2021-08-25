#pragma once

#include "ConfUI.h"
#include "WindowEx.h"

//****************************/
//-- class LoginForm
//****************************/
class LoginForm : public ui_comp::WindowEx
{
public:
	LoginForm();
	~LoginForm();

	/**
	 * �����ĸ��ӿ��Ǳ���Ҫ��д�Ľӿڣ������������ĸ��ӿ�����������
	 * GetSkinFolder		�ӿ�����Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�����Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô�������
	 * GetWindowId			�ӿ����ô���id
	 */
	virtual std::wstring GetSkinFolder() override			{ return ConfUI::Login_SkinFolder; }
	virtual std::wstring GetSkinFile() override				{ return ConfUI::Login_SkinFile; }
	virtual std::wstring GetWindowClassName() const override{ return ConfUI::Login_ClassName; }
	virtual std::wstring GetWindowId() const override		{ return ConfUI::Login_WindowId; }

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void InitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
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

	/**
	 * ��Ӧȡ����¼�Ļص������ý���ؼ�Ч��
	 * @return void	�޷���ֵ
	 */
	void OnCancelLogin();

private:
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

