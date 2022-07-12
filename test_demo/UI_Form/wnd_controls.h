#pragma once

#include "ConfUI.h"

//****************************/
//-- class wnd_controls
//****************************/
class wnd_controls : public ui_comp::WindowEx
{
public:
	/**
	 * ��ʾ����
	 * @param[in] hWndParent �����ھ��������ṩ�Ļ�����ʾ�ڸ����ڵ����ģ���Ϊģ̬
	 * @return void �޷���ֵ
	 */
	static void Show(HWND hWndParent)
	{
		int input_number = 123;
		std::string input_string = "abc";
		ui_comp::WindowExMgr::ShowNewWindow<wnd_controls>(
			hWndParent,
			FALSE,
			ConfUI::controls_ClassName,
			ConfUI::controls_WindowId,
			input_number,
			input_string);
	}

public:
	wnd_controls(
		const std::wstring& wnd_id,
		int input_number,
		const std::string& input_string)
		: ui_comp::WindowEx(
			FL_N_LAYERED | FL_SHADOWWND,
			ConfUI::controls_SkinFolder,
			ConfUI::controls_SkinFile,
			ConfUI::controls_ClassName,
			wnd_id)
	{
		printf("[wnd_controls]\n\t input_number: %d\n\t input_string: %s\n", input_number, input_string.c_str());
	}

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
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	// ������ʾ
	void OnError(const std::wstring& error);

private:
	ui::Label*		m_title;
	ui::DateTime*	m_my_date;
	ui::DateTime*	m_my_time;
	ui::Button*		m_print_datetime;
};
