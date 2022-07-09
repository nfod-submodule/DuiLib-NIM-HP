#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class MenuElementUI
//****************************/
class MenuElementUI : public ui::ListContainerElement
{
public:
	MenuElementUI() { m_bMouseChildEnabled = false; }

	virtual bool ButtonUp(ui::EventArgs& msg) override
	{
		std::weak_ptr<nbase::WeakFlag> weakFlag = m_pWindow->GetWeakFlag();
		bool bRet = __super::ButtonUp(msg);
		if (bRet && !weakFlag.expired()) {
			m_pWindow->Close();
		}
		return bRet;
	}
};

//****************************/
//-- class MenuWnd
//****************************/
class MenuWnd : public ui::WindowImplBase
{
public:
	enum EPopupPosType { RIGHT_BOTTOM, RIGHT_TOP };
	MenuWnd(HWND hParent = NULL) : m_hParent(hParent), m_popupPosType(RIGHT_BOTTOM), m_no_focus(false) {}

	virtual std::wstring GetSkinFolder() override { return L"ui_comp_menuwnd"; }
	virtual std::wstring GetSkinFile() override { return m_xmlSkinFile; }
	virtual std::wstring GetWindowClassName() const override { return L"menuwnd"; }

	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	void Init(const std::wstring& xmlSkinFile, POINT basedPoint, EPopupPosType popupPosType = RIGHT_BOTTOM, bool no_focus = false);
	void Show();

public:
	HWND m_hParent;
	std::wstring m_xmlSkinFile;
	POINT m_basedPoint;
	EPopupPosType m_popupPosType;
	bool m_no_focus;
};

NS_UI_COMP_END