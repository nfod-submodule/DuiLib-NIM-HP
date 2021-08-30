#pragma once

#include "UIlib.h"
#include "ConfUI_Components.h"

NS_UI_COMP_BEGIN

enum MenuAlignment
{
	eMenuAlignment_Left = 1 << 1,
	eMenuAlignment_Top = 1 << 2,
	eMenuAlignment_Right = 1 << 3,
	eMenuAlignment_Bottom = 1 << 4,
};

/////////////////////////////////////////////////////////////////////////////////////
//

extern const TCHAR* const kMenuElementUIInterfaceName;// = _T("MenuElement);
class MenuElementUI;
class MenuWnd : public ui::WindowImplBase
{
public:
	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;

	enum PopupPosType
	{
		RIGHT_BOTTOM,
		RIGHT_TOP
	};

	MenuWnd(HWND hParent = NULL);
	void Init(ui::STRINGorID xml, LPCTSTR pSkinType, POINT point, PopupPosType popupPosType = RIGHT_BOTTOM, bool no_focus = false);
	std::wstring GetWindowClassName() const;

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual std::wstring GetSkinFolder() override {
		return L"menu";
	}
	virtual std::wstring GetSkinFile() override {
		return m_xml.m_lpstr;
	}

	void Show();

public:
	HWND m_hParent;
	POINT m_BasedPoint;
	PopupPosType m_popupPosType;
	ui::STRINGorID m_xml;
	std::wstring m_sType;
	bool no_focus_;
};

class ListContainerElement;
class MenuElementUI : public ui::ListContainerElement
{
	friend MenuWnd;
public:
	MenuElementUI();
	~MenuElementUI();

	virtual bool ButtonUp(ui::EventArgs& msg) override;
};

NS_UI_COMP_END