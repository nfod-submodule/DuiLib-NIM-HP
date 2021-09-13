#pragma once

#include "ConfUI.h"
#include "WindowExMgr.h"

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui_comp::WindowEx
{
public:
	static void SingletonShow() {
		ui_comp::WindowExMgr::GetInstance()->SingletonShow<MainForm>(ConfUI::Main_ClassName, ConfUI::Main_WindowId);
	}
public:
	MainForm(const std::wstring& wnd_id = ConfUI::Main_WindowId)
		: ui_comp::WindowEx(ConfUI::Main_ClassName, wnd_id) {}
	~MainForm() {}

	/**
	 * 以下两个接口是必须要覆写的接口，父类会调用来构建窗口
	 * GetSkinFolder	接口设置要绘制的窗口皮肤资源路径
	 * GetSkinFile		接口设置要绘制的窗口的 xml 描述文件
	 */
	virtual std::wstring GetSkinFolder() override { return ConfUI::Main_SkinFolder; }
	virtual std::wstring GetSkinFile() override   { return ConfUI::Main_SkinFile; }

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
	 * 注册窗口的回调函数
	 * @return void	无返回值
	 */
	void RegisterCallback();

	/**
	 * 处理所有控件的所有消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnNotify(ui::EventArgs* msg);

	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	// 弹出菜单窗口
	void PopupMenu(POINT point);

	/**
	 * 响应设备授权回调
	 * @param[in] ProjectId 项目Id
	 * @param[in] bAuth 是否已授权
	 * @return void	无返回值
	 */
	void OnDevAuth(std::wstring ProjectId, bool bAuth);

private:
	ui::Button*	m_btn_menu;
	ui::Button*	m_btn_logout;
	ui::Button*	m_btn_quit;
	ui::Option* m_opt_tab_r;
	ui::Option* m_opt_tab_g;
	ui::TabBox* m_box_tabs;
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
