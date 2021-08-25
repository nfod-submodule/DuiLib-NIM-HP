#pragma once

#include "ConfUI.h"
#include "WindowEx.h"

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui_comp::WindowEx
{
public:
	MainForm();
	~MainForm();

	/**
	 * �����ĸ��ӿ��Ǳ���Ҫ��д�Ľӿڣ������������ĸ��ӿ�����������
	 * GetSkinFolder		�ӿ�����Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�����Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô�������
	 * GetWindowId			�ӿ����ô���id
	 */
	virtual std::wstring GetSkinFolder() override			{ return ConfUI::Main_SkinFolder; }
	virtual std::wstring GetSkinFile() override				{ return ConfUI::Main_SkinFile; }
	virtual std::wstring GetWindowClassName() const override{ return ConfUI::Main_ClassName; }
	virtual std::wstring GetWindowId() const override		{ return ConfUI::Main_WindowId; }

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
	ui::Button*	m_btn_logout;
	ui::Button*	m_btn_exit;
};

