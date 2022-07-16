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
	typedef std::function<void()> Callback_Quit; // �˳�

	/**
	 * ��������
	 * @param[in] lpClassName	��������
	 * @param[in] lpWindowName	������
	 * @param[in] lpStrRegWnd	��ע����Ϣ������
	 * @param[in] lpMenuTip		������ʾ�ı�
	 * @return true=�ɹ� false=ʧ��
	**/
	bool Create(
		LPCWSTR lpClassName  = L"Tray_ClassName",
		LPCWSTR lpWindowName = L"Tray_WindowName",
		LPCWSTR lpStrRegWnd  = L"Tray_StrRegWnd",
		LPCWSTR lpMenuTip    = L"Tray_MenuTip");

	/**
	 * ��������
	 * @return �޷���ֵ
	**/
	void Destroy();

	/**
	 * ������������
	 * @param[in] hCurrWnd	���ھ��
	 * @param[in] bLogined	�Ƿ��ѵ�¼
	 * @param[in] cb_Quit	�˳��ص�
	 * @return true=�ɹ� false=ʧ��
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
