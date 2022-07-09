#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

// 一个叠加到基础窗口周围的窗口，带有 WS_EX_LAYERED 属性来实现阴影效果
//****************************/
//-- class ShadowWnd
//****************************/
class ShadowWnd : public ui::WindowImplBase
{
public:
	ShadowWnd() : m_pWndBase(nullptr) {}

	virtual std::wstring GetSkinFolder() override { return ConfUI_Components::Shadow_SkinFolder; }
	virtual std::wstring GetSkinFile()   override { return ConfUI_Components::Shadow_SkinFile; }
	virtual std::wstring GetWindowClassName() const override { return ConfUI_Components::Shadow_ClassName; }

	virtual HWND CreateEx(Window* pWndBase);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

private:
	Window*	m_pWndBase;
};

NS_UI_COMP_END