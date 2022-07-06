#pragma once

#include "ConfUI.h"

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui_comp::WindowEx
{
public:
	static void SingletonShow()
	{
		ui_comp::WindowExMgr::ShowSingleton<MainForm>(
			ConfUI::Main_ClassName,
			ConfUI::Main_WindowId);
	}

public:
	MainForm(const std::wstring& wnd_id)
		: ui_comp::WindowEx(
			FL_QUIT,
			ConfUI::Main_SkinFolder,
			ConfUI::Main_SkinFile,
			ConfUI::Main_ClassName,
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
	 * ע�ᴰ�ڵĻص�����
	 * @return void	�޷���ֵ
	 */
	void RegisterCallback();

	/**
	 * �������пؼ���������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnNotify(ui::EventArgs* msg);

	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	// �����˵�����
	void PopupMenu(POINT point);

	/**
	 * ��Ӧ�豸��Ȩ�ص�
	 * @param[in] ProjectId ��ĿId
	 * @param[in] bAuth �Ƿ�����Ȩ
	 * @return void	�޷���ֵ
	 */
	void OnDevAuth(std::wstring ProjectId, bool bAuth);

private:
	ui::Button*	m_btn_menu;
	ui::Button*	m_btn_logout;
	ui::Button*	m_btn_quit;
	ui::Option* m_opt_tab_r;
	ui::Option* m_opt_tab_g;
	ui::TabBox* m_box_tabs;
	ui::Combo*   m_combo_r;
	ui::ListBox* m_list_r;
	ui::ListBox* m_list_g;
};

//****************************/
//-- class ListItemG
//****************************/
class ListItemG : public ui::ListContainerElement
{
public:
	ListItemG() : m_bDevAuth(false) {}

	void InitSubControls(
		const std::wstring& project_id,
		const std::wstring& project_name,
		const std::wstring& project_mgr,
		const std::vector<std::wstring>& working_dirs,
		const std::wstring& expire_date,
		bool bDevAuth);

	const std::wstring& GetProjectId() const { return m_project_id; }
	void SetWorkingDir(const std::vector<std::wstring>& working_dirs);
	void SetDeviceAuth(bool bDevAuth);

private:
	bool OnWorkingDir(ui::EventArgs* args);
	bool OnDeviceAuth(ui::EventArgs* args);
	bool OnProjectDel(ui::EventArgs* args);

private:
	std::wstring m_project_id;
	std::vector<std::wstring> m_working_dirs;
	bool m_bDevAuth;

	ui::Label*   m_lbl_project_name;
	ui::Label*   m_lbl_project_mgr;
	ui::Button*  m_btn_working_dir;
	ui::Label*   m_lbl_expire_date;
	ui::Button*  m_btn_device_auth;
	ui::Button*  m_btn_project_del;
};
