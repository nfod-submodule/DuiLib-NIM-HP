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
	eMenuAlignment_I = 1 << 5	// Intelligent ���ܵķ�ֹ���ڱ�
};

enum EMenuCloseType
{
	eMenuCloseThis,	// �����ڹرյ�ǰ����Ĳ˵����ڣ��磺�������ʱ
	eMenuCloseAll	// �ر����в˵����ڣ���ʧȥ����ʱ
};

/**
 * ���ӹر��¼��Ĵ��ݡ�
 * ���ĳһ�˵�����ȡ�ò˵����ھ����֪ͨ�ò˵����ڿ��Թر��Ӳ˵�����
 * ��ĳ�Ӳ˵���Ŀ�ĸ����ڵ��ڸô��ڣ����Ӳ˵��ر�
 * ���ڲ˵��ĸ��ӹ�ϵ�����Զ��ر�����������˵�����
 * ������¼�������ƿ���ԭ��Duilib��MenuDemo������Redrain��Menu���ܸ��ã�֧�ֲ˵���ѡ��������δʵ��
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
	// ָ����point���ڲ˵����ĸ�λ��
	// 1.--.2	��1���� 2���ϣ�
	// |    |
	// 3.--.4	��3���� 4���£�
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

	// ��ʼ
	void Init(
		const std::wstring& xmlSkinFile,
		POINT base_point,
		EPopupPosType ePopup = ePopupLT,
		bool no_focus = false,
		MenuElementUI* pOwner = NULL);

	// ��ʾ
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
	// ���µ����˵��Ĵ�С
	void ResizeMenu();
	// ���µ����Ӳ˵��Ĵ�С
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