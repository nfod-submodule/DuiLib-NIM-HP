#pragma once

#include "ConfUI_Components.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class Toast
//****************************/
class Toast : public ui::WindowImplBase
{
public:
	/**
	 * ����Ļ�м���ʾһ����ʾ��
	 * @param[in] hWndParent �����ھ��������ṩ�Ļ�toast����ʾ�ڸ����ڵ�����
	 * @param[in] content ��ʾ����
	 * @param[in] duration ����ʱ��(����),0����һֱ��ʾ
	 * @return void �޷���ֵ
	 */
	static void Show(HWND hWndParent, const std::wstring& content, int duration = 0);

public:
	Toast() {};

	virtual std::wstring GetSkinFolder() override { return ConfUI_Components::Toast_SkinFolder; }
	virtual std::wstring GetSkinFile() override { return ConfUI_Components::Toast_SkinFile; }
	virtual std::wstring GetWindowClassName() const override { return ConfUI_Components::Toast_ClassName; }
	virtual UINT GetClassStyle() const override { return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS); }

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	virtual void InitWindow() override;

private:
	bool OnClicked(ui::EventArgs* msg);

	void SetContent(const std::wstring& content);
	void SetDuration(int duration_milliseconds);

private:
	ui::RichEdit*	m_content;
	ui::Button*		m_btn_close;
};

NS_UI_COMP_END