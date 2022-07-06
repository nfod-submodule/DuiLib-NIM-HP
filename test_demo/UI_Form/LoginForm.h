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
	 * �������пؼ���������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnEventAll(ui::EventArgs* msg);
	bool OnEventTextChange(const std::wstring& sSenderName);
	bool OnEventTab();
	bool OnEventReturn();
	bool OnEventSelect(const std::wstring& sSenderName);
	bool OnEventUnSelect(const std::wstring& sSenderName);

	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	// ������ʾ
	void OnError(const std::wstring& error);
	// ȡ����¼
	void OnCancel();
	// ��ʾ������
	void OnShowMain();

private:
	// ִ�е�¼
	void DoLogin();

private:
	// ������ʾ��Ϣ
	void SetTip(const std::wstring& text, const std::wstring& textcolor);
	// ���ÿؼ�Ч����true=���ڵ�¼ false=��ʼ״̬��
	void SetEffect(bool bLogging);

private:
	ui::Label*		m_title;
	ui::Label*		m_tip;
	ui::Control*	m_usericon;
	ui::Control*	m_passicon;
	ui::RichEdit*	m_user;
	ui::RichEdit*	m_pass;
	ui::CheckBox*	m_keep;
	ui::CheckBox*	m_auto;
	ui::Button*		m_regist;
	ui::Button*		m_forgot;
	ui::Button*		m_login;
	ui::Button*		m_cancel;
};
