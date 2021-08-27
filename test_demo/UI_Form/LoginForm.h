#pragma once

#include "ConfUI.h"
#include "WindowEx.h"

//****************************/
//-- class LoginForm
//****************************/
class LoginForm : public ui_comp::WindowEx
{
public:
	LoginForm(const std::wstring& wnd_id = ConfUI::Login_WindowId)
		: ui_comp::WindowEx(ConfUI::Login_ClassName, wnd_id) {}
	~LoginForm() {}

	/**
	 * 以下两个接口是必须要覆写的接口，父类会调用来构建窗口
	 * GetSkinFolder	接口设置要绘制的窗口皮肤资源路径
	 * GetSkinFile		接口设置要绘制的窗口的 xml 描述文件
	 */
	virtual std::wstring GetSkinFolder() override { return ConfUI::Login_SkinFolder; }
	virtual std::wstring GetSkinFile() override   { return ConfUI::Login_SkinFile; }

	/**
	 * 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	 */
	virtual void InitWindow() override;

	/**
	 * 收到 WM_CLOSE 消息时该函数会被调用
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	/**
	 * 注册登录窗口的回调函数
	 * @return void	无返回值
	 */
	void RegisterCallback();

	/**
	 * 处理所有控件的所有消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnNotify(ui::EventArgs* msg);
	void OnEventTextChange(const std::wstring& sSenderName);
	void OnEventTab();
	void OnEventReturn();

	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	/**
	 * 响应登录错误的回调，
	 * @return void	无返回值
	 */
	void OnLoginError(int error);

	/**
	 * 响应取消登录的回调，重置界面控件效果
	 * @return void	无返回值
	 */
	void OnCancelLogin();

	/**
	 * 执行登录操作
	 * @return void	无返回值
	 */
	void DoLogin();

	/**
	 * 设置提示信息
	 * @param[in] text 文本内容
	 * @param[in] textcolor 文本颜色
	 * @return void	无返回值
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

