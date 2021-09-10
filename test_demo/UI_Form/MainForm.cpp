#include "stdafx.h"
#include "Resource.h"
#include "MainForm.h"
#include "LoginKit.h"
#include "MenuWnd.h"
#include "MsgBox.h"
#include "Toast.h"

//****************************/
//-- namespace NS_MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

#define NS_MainForm_BEGIN	namespace NS_MainForm {
#define NS_MainForm_END		}
#define USING_NS_MainForm	using namespace NS_MainForm

NS_MainForm_BEGIN

//-- �ؼ�����
CONST PWSTR WGT_closebtn2	= L"closebtn2";		// Button: �رգ��������Ͻǲ棩
CONST PWSTR WGT_btn_menu	= L"btn_menu";		// Button: �˵�
CONST PWSTR WGT_btn_logout	= L"btn_logout";	// Button: ע��
CONST PWSTR WGT_btn_quit	= L"btn_quit";		// Button: �˳�
CONST PWSTR WGT_opt_tab_r	= L"opt_tab_r";		// Option: ��ǩ-��
CONST PWSTR WGT_opt_tab_g	= L"opt_tab_g";		// Option: ��ǩ-��
CONST PWSTR WGT_box_tabs	= L"box_tabs";		// TabBox: ��ǩ����
CONST PWSTR WGT_list_r		= L"list_r";		// ListBox: �б�-��
CONST PWSTR WGT_list_g		= L"list_g";		// ListBox: �б�-��

CONST INT WGT_box_tab_r_index = 0;	// ��ǩ����-��-����
CONST INT WGT_box_tab_g_index = 1;	// ��ǩ����-��-����

//-- �ı�����
CONST PWSTR TXT_exit_confirm	= L"ȷ���˳�����";
CONST PWSTR TXT_title_hint		= L"��ʾ";
CONST PWSTR TXT_btn_confirm		= L"ȷ��";
CONST PWSTR TXT_btn_cancel		= L"ȡ��";

NS_MainForm_END
USING_NS_MainForm;

//****************************/
//-- class MainForm
//****************************/
//////////////////////////////////////////////////////////////////////////

void MainForm::InitWindow()
{
	SetIcon(IDI_TEST_DEMO);
	SetTaskbarTitle(ConfUI::Main_WindowName);

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind<bool>(&MainForm::OnNotify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind<bool>(&MainForm::OnClicked, this, std::placeholders::_1));
	
	// ���ݿؼ����Ʋ��ҿؼ�
	m_btn_menu   = (ui::Button*) FindControl(WGT_btn_menu);
	m_btn_logout = (ui::Button*) FindControl(WGT_btn_logout);
	m_btn_quit   = (ui::Button*) FindControl(WGT_btn_quit);
	m_opt_tab_r  = (ui::Option*) FindControl(WGT_opt_tab_r);
	m_opt_tab_g  = (ui::Option*) FindControl(WGT_opt_tab_g);
	m_box_tabs   = (ui::TabBox*) FindControl(WGT_box_tabs);
	m_list_r     = (ui::ListBox*)FindControl(WGT_list_r);
	m_list_g     = (ui::ListBox*)FindControl(WGT_list_g);

	// Ĭ����ʾ����ǩ-��
	m_opt_tab_g->Selected(true);
	m_box_tabs->SelectItem(WGT_box_tab_g_index);

	// ��ʼ�б�
	for (int id = 1; id <= 6; ++id)
	{
		ListItemG* pItem = new ListItemG();
		if (pItem) {
			ui::GlobalManager::FillBoxWithCache(pItem, L"_ui_main/item_g.xml");
			std::wstring txt1 = nbase::StringPrintf(L"�ش���Ŀ�з�%d��", id);
			std::wstring txt2 = L"������";
			std::wstring txt3 = L"����Ŀ¼";
			std::wstring txt4 = L"2021-12-31";
			std::wstring txt5 = L"������Ȩ";
			pItem->InitSubControls(id, txt1, txt2, txt3, txt4, txt5);
		}
		m_list_g->Add(pItem);
	}
}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool MainForm::OnNotify(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	switch (msg->Type)
	{
	case ui::kEventTextChange:
		break;
	case ui::kEventTab:
		break;
	case ui::kEventReturn:
		break;
	default:
		break;
	}
	return true;
}

bool MainForm::OnClicked(ui::EventArgs* msg)
{
	std::wstring sSenderName = msg->pSender->GetName();
	if (sSenderName == WGT_closebtn2)
	{
		auto cb_Close = [this](ui_comp::EMsgBoxRet eRet) {
			if (eRet == ui_comp::eMsgBox_YES) {
				this->Close();
			}
		};
		ui_comp::MsgBox::Show(m_hWnd, ToWeakCallback(cb_Close), TXT_exit_confirm, TXT_title_hint, TXT_btn_confirm, TXT_btn_cancel);
	}
	else if (sSenderName == WGT_btn_menu)
	{
		RECT rect = msg->pSender->GetPos();
		POINT point;
		point.x = rect.left - 15;
		point.y = rect.bottom + 10;
		::ClientToScreen(m_hWnd, &point);
		PopupMenu(point);
	}
	else if (sSenderName == WGT_btn_logout)
	{
		LoginKit::GetInstance()->DoLogout();
	}
	else if (sSenderName == WGT_btn_quit)
	{
		this->Close();
	}
	else if (sSenderName == WGT_opt_tab_r)
	{
		m_box_tabs->SelectItem(WGT_box_tab_r_index);
	}
	else if (sSenderName == WGT_opt_tab_g)
	{
		m_box_tabs->SelectItem(WGT_box_tab_g_index);
	}
	return true;
}

void MainForm::PopupMenu(POINT point)
{
	static CONST PWSTR XML_SkinFile = L"main_menu.xml";
	static CONST PWSTR WGT_element_about  = L"about";
	static CONST PWSTR WGT_element_logout = L"logout";
	static CONST PWSTR WGT_element_quit   = L"quit";

 	ui_comp::MenuWnd* pMenu = new ui_comp::MenuWnd();
 	pMenu->Init(XML_SkinFile, point, ui_comp::MenuWnd::RIGHT_BOTTOM);
	{
		// ע��ص�-����
		ui::EventCallback cb_about = [this](ui::EventArgs*) {
			ui_comp::MsgBox::Show(m_hWnd, nullptr, L"�汾��V1.0.0", L"����", L"֪����", L"");
			return true;
		};
		ui_comp::MenuElementUI* pAbout = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_about);
		pAbout->AttachSelect(cb_about);
		// ע��ص�-ע��
		ui::EventCallback cb_logout = [this](ui::EventArgs*) {
			LoginKit::GetInstance()->DoLogout();
			return true;
		};
		ui_comp::MenuElementUI* pLogout = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_logout);
		pLogout->AttachSelect(cb_logout);
		// ע��ص�-�˳�
		ui::EventCallback cb_quit = [this](ui::EventArgs*) {
			this->Close();
			return true;
		};
		ui_comp::MenuElementUI* pQuit = (ui_comp::MenuElementUI*)pMenu->FindControl(WGT_element_quit);
		pQuit->AttachSelect(cb_quit);
	}
 	pMenu->Show();
}

//****************************/
//-- class ListItemG
//****************************/
//////////////////////////////////////////////////////////////////////////

void ListItemG::InitSubControls(
	const int nId,
	const std::wstring& txt_col1,
	const std::wstring& txt_col2,
	const std::wstring& txt_col3,
	const std::wstring& txt_col4,
	const std::wstring& txt_col5)
{
	m_column1 = (ui::Label*) FindSubControl(L"column1");
	m_column2 = (ui::Label*) FindSubControl(L"column2");
	m_column3 = (ui::Button*)FindSubControl(L"column3");
	m_column4 = (ui::Label*) FindSubControl(L"column4");
	m_column5 = (ui::Button*)FindSubControl(L"column5");
	m_column6 = (ui::Button*)FindSubControl(L"column6");

	m_nId = nId;
	m_column1->SetText(txt_col1);
	m_column2->SetText(txt_col2);
	m_column3->SetText(txt_col3);
	m_column4->SetText(txt_col4);
	m_column5->SetText(txt_col5);

	m_column3->SetStateTextColor(ui::kControlStateHot, L"link_blue");
	m_column5->SetStateTextColor(ui::kControlStateHot, L"link_blue");

	m_column3->AttachClick(std::bind<bool>(&ListItemG::OnColumn3, this, std::placeholders::_1));
	m_column5->AttachClick(std::bind<bool>(&ListItemG::OnColumn5, this, std::placeholders::_1));
	m_column6->AttachClick(std::bind<bool>(&ListItemG::OnColumn6, this, std::placeholders::_1));
}

bool ListItemG::OnColumn3(ui::EventArgs* args)
{
	ui_comp::MsgBox::Show(this->GetWindow()->GetHWND(), nullptr, L"���������豸��Ȩ��", L"��ʾ", L"֪����", L"");
	return true;
}

bool ListItemG::OnColumn5(ui::EventArgs* args)
{
	std::wstring content = nbase::StringPrintf(L"[Id=%d] �ѷ����豸��Ȩ���룬�����ĵȴ���", m_nId);
	ui_comp::Toast::Show(this->GetWindow()->GetHWND(), content, 3000);
	return true;
}

bool ListItemG::OnColumn6(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent ? parent->Remove(this) : false;
}
