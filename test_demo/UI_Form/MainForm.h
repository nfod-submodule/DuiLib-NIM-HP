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
	 * ���������ӿ��Ǳ���Ҫ��д�Ľӿڣ�������������������
	 * GetSkinFolder	�ӿ�����Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile		�ӿ�����Ҫ���ƵĴ��ڵ� xml �����ļ�
	 */
	virtual std::wstring GetSkinFolder() override { return ConfUI::Main_SkinFolder; }
	virtual std::wstring GetSkinFile() override   { return ConfUI::Main_SkinFile; }

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

	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	// �����˵�����
	void PopupMenu(POINT point);

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
	ListItemG() : m_nId(0) {}

	void InitSubControls(
		const int nId,
		const std::wstring& txt_col1,
		const std::wstring& txt_col2,
		const std::wstring& txt_col3,
		const std::wstring& txt_col4,
		const std::wstring& txt_col5);

private:
	bool OnColumn3(ui::EventArgs* args);
	bool OnColumn5(ui::EventArgs* args);
	bool OnColumn6(ui::EventArgs* args);

private:
	int m_nId;
	ui::Label*	m_column1;
	ui::Label*	m_column2;
	ui::Button*	m_column3;
	ui::Label*	m_column4;
	ui::Button*	m_column5;
	ui::Button*	m_column6;
};
