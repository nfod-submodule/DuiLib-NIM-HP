#pragma once

#include "windows_manager/window_ex.h"
#include "windows_manager/windows_manager.h"

NS_UI_COMP_BEGIN

enum EMenuAlignment
{
	eMenuAlignment_L = 1 << 1,	// Left
	eMenuAlignment_T = 1 << 2,	// Top
	eMenuAlignment_R = 1 << 3,	// Right
	eMenuAlignment_B = 1 << 4,	// Bottom
	eMenuAlignment_I = 1 << 5	// Intelligent 智能的防止被遮蔽
};

enum EMenuCloseType
{
	eMenuCloseThis,	// 适用于关闭当前级别的菜单窗口，如：鼠标移入时
	eMenuCloseAll	// 关闭所有菜单窗口，如失去焦点时
};

/**
 * 增加关闭事件的传递。
 * 点击某一菜单，获取该菜单窗口句柄，通知该菜单窗口可以关闭子菜单项了
 * 即某子菜单项目的父窗口等于该窗口，该子菜单关闭
 * 由于菜单的父子关系，会自动关闭其所有子孙菜单窗口
 * 这里的事件传递设计拷贝原生Duilib的MenuDemo，不过Redrain的Menu功能更好，支持菜单复选，这里暂未实现
**/
#include "observer_impl_base.hpp" // copy from menuDemo
struct ContextMenuParam
{
	EMenuCloseType wParam;
	HWND hWnd;
};
typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;

//****************************/
//-- class MenuWnd
//****************************/
class MenuElementUI;
class MenuWnd : public ui::WindowImplBase, public ContextMenuReceiver
{
	friend class MenuElementUI;
public:
	// 指定的point属于菜单的哪个位置
	// 1.--.2	（1左上 2右上）
	// |    |
	// 3.--.4	（3左下 4右下）
	enum EPopupPosType
	{
		ePopupRB = eMenuAlignment_R | eMenuAlignment_B | eMenuAlignment_I,
		ePopupRT = eMenuAlignment_R | eMenuAlignment_T | eMenuAlignment_I,
		ePopupLB = eMenuAlignment_L | eMenuAlignment_B | eMenuAlignment_I,
		ePopupLT = eMenuAlignment_L | eMenuAlignment_T | eMenuAlignment_I
	};

public:
	MenuWnd(HWND hParent = NULL)
		: m_hParent(hParent)
		, m_xmlSkinFile(L"")
		, m_base_point({ 0, 0 })
		, m_ePopup(ePopupLT)
		, m_no_focus(false)
		, m_pOwner(NULL)
		, m_pLayout(NULL) {}

	// 初始
	void Init(
		const std::wstring& xmlSkinFile,
		POINT base_point,
		EPopupPosType ePopup = ePopupLT,
		bool no_focus = false,
		MenuElementUI* pOwner = NULL);

	// 显示
	void Show();

private:
	virtual std::wstring GetSkinFolder() override { return L"ui_comp_menu"; }
	virtual std::wstring GetSkinFile()   override { return m_xmlSkinFile; }
	virtual std::wstring GetWindowClassName() const override { return L"menu"; }
	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;

private:
	virtual void InitWindow() override;
	virtual void OnFinalMessage(HWND hWnd) override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	static ContextMenuObserver& GetMenuObserver();
	BOOL Receive(ContextMenuParam param) override;

	void DetouchOwner();
	// 重新调整菜单的大小
	void ResizeMenu();
	// 重新调整子菜单的大小
	void ResizeSubMenu();

private:
	HWND m_hParent;
	std::wstring m_xmlSkinFile;
	POINT m_base_point;
	EPopupPosType m_ePopup;
	bool m_no_focus;
	MenuElementUI* m_pOwner;
	ui::ListBox* m_pLayout;
};

//****************************/
//-- class MenuElementUI
//****************************/
class MenuElementUI : public ui::ListContainerElement
{
	friend MenuWnd;
public:
	MenuElementUI();
	~MenuElementUI();

	virtual bool ButtonUp(ui::EventArgs& msg) override;
	virtual bool MouseEnter(ui::EventArgs& msg) override;

	virtual void PaintChild(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;

	bool CheckSubMenuItem();

	virtual bool AddSubMenuItem(MenuElementUI* pMenuItem);
	virtual bool AddSubMenuItemAt(MenuElementUI* pMenuItem, std::size_t iIndex);
	virtual bool RemoveSubMenuItem(MenuElementUI* pMenuItem);
	virtual bool RemoveSubMenuItemAt(std::size_t iIndex);
	virtual bool RemoveAllSubMenuItem();
	virtual MenuElementUI* GetSubMenuItemAt(std::size_t iIndex) const;
	virtual int GetSubMenuItemCount() const { return (int)m_child_menus.size(); };

	virtual bool Add(Control* pControl) override;

private:
	void CreateMenuWnd();
	MenuWnd* m_pSubWindow;

protected:
	std::vector<MenuElementUI*> m_child_menus;
};

NS_UI_COMP_END