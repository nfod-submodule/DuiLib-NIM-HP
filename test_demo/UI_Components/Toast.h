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
	 * 在屏幕中间显示一个提示框
	 * @param[in] hWndParent 父窗口句柄，如果提供的话toast会显示在父窗口的中心
	 * @param[in] content 提示内容
	 * @param[in] duration 持续时间(毫秒),0代表一直显示
	 * @return void 无返回值
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