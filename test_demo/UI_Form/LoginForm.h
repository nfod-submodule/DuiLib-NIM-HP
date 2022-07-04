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
	 * 关闭窗口
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * 初始窗口
	 */
	virtual void InitWindow() override;

private:
	/**
	 * 处理所有控件的所有消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnEventAll(ui::EventArgs* msg);
	bool OnEventTextChange(const std::wstring& sSenderName);
	bool OnEventTab();
	bool OnEventReturn();
	bool OnEventSelect(const std::wstring& sSenderName);
	bool OnEventUnSelect(const std::wstring& sSenderName);

	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	// 错误提示
	void OnError(const std::wstring& error);
	// 取消登录
	void OnCancel();
	// 显示主窗口
	void OnShowMain();

private:
	// 执行登录
	void DoLogin();

private:
	// 设置提示信息
	void SetTip(const std::wstring& text, const std::wstring& textcolor);
	// 设置控件效果（true=正在登录 false=初始状态）
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
