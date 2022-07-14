#pragma once

//****************************/
//-- class TrayMenu
//****************************/
class TrayMenu : public ui_comp::TrayIconDelegate
{
public:
	SINGLETON_DEFINE(TrayMenu);
	TrayMenu();
	~TrayMenu();

public:
	typedef std::function<void()> Callback_Quit; // 退出

	/**
	 * 创建托盘
	 * @param[in] lpClassName	窗口类名
	 * @param[in] lpWindowName	窗口名
	 * @param[in] lpStrRegWnd	被注册消息的名字
	 * @param[in] lpMenuTip		托盘提示文本
	 * @return true=成功 false=失败
	**/
	bool Create(
		LPCWSTR lpClassName  = L"Tray_ClassName",
		LPCWSTR lpWindowName = L"Tray_WindowName",
		LPCWSTR lpStrRegWnd  = L"Tray_StrRegWnd",
		LPCWSTR lpMenuTip    = L"Tray_MenuTip");

	/**
	 * 销毁托盘
	 * @return 无返回值
	**/
	void Destroy();

	/**
	 * 更新托盘设置
	 * @param[in] hCurrWnd	窗口句柄
	 * @param[in] bLogined	是否已登录
	 * @param[in] cb_Quit	退出回调
	 * @return true=成功 false=失败
	**/
	bool Update(
		HWND hCurrWnd,
		bool bLogined,
		const Callback_Quit& cb_Quit);

private:
	virtual void OnLeftClick();
	virtual void OnLeftDoubleClick() {}
	virtual void OnRightClick();
	virtual void OnRightDoubleClick() {}

private:
	void PopupMenu0(POINT point);
	void PopupMenu1(POINT point);

private:
	bool Cb_ActiveWnd(ui::EventArgs*);
	bool Cb_Website(ui::EventArgs*);
	bool Cb_About(ui::EventArgs*);
	bool Cb_Logout(ui::EventArgs*);
	bool Cb_Quit(ui::EventArgs*);

private:
	void ActiveWnd();
	void Invoke_Quit();

private:
	ui_comp::TrayIcon* m_pTray;
	HWND m_hCurrWnd;
	bool m_bLogined;
	Callback_Quit m_cb_Quit;
};
