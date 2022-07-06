#pragma once

#include "windows_manager/window_ex.h"
#include "windows_manager/windows_manager.h"

NS_UI_COMP_BEGIN

enum EMsgBoxRet
{
	eMsgBox_YES,
	eMsgBox_NO
};

typedef std::function<void(EMsgBoxRet eRet)> MsgBoxCallback;

// ��Ϣ��
//****************************/
//-- class MsgBox
//****************************/
class MsgBox : public WindowEx
{
public:
	/**
	 * ����Ļ�м���ʾ��Ϣ��
	 * @param[in] hWndParent �����ھ��������ṩ�Ļ�msgbox����ʾ�ڸ����ڵ����ģ���Ϊģ̬
	 * @param[in] callback �ص�����
	 * @param[in] content  ��Ϣ����
	 * @param[in] title    ���ڱ���
	 * @param[in] btn_yes  ȷ����ť���ݣ��������Ϊ������ʾ��ť
	 * @param[in] btn_no   ȡ����ť���ݣ��������Ϊ������ʾ��ť
	 * @return void �޷���ֵ
	 */
	static void Show(
		HWND hWndParent,
		MsgBoxCallback callback,
		const std::wstring& content,
		const std::wstring& title = L"��ʾ",
		const std::wstring& btn_yes = L"ȷ��",
		const std::wstring& btn_no = L"ȡ��")
	{
		MsgBox* pWnd = WindowExMgr::ShowNewWindow<MsgBox>(
			hWndParent,
			FALSE,
			ConfUI_Components::MsgBox_ClassName,
			ConfUI_Components::MsgBox_WindowId);
		if (pWnd) {
			pWnd->SetCallback(callback);
			pWnd->SetContent(content);
			pWnd->SetTitle(title);
			pWnd->SetButton(btn_yes, btn_no);
		}
	}

	static void ShowEx(
		HWND hWndParent,
		MsgBoxCallback callback,
		const std::wstring& content, bool content_is_id,
		const std::wstring& title, bool title_is_id,
		const std::wstring& btn_yes, bool btn_yes_is_id,
		const std::wstring& btn_no, bool btn_no_is_id)
	{
		ui::MutiLanSupport* pML = ui::MutiLanSupport::GetInstance();
		std::wstring ws_content = content_is_id ? pML->GetStringViaID(content) : content;
		std::wstring ws_title   = title_is_id   ? pML->GetStringViaID(title)   : title;
		std::wstring ws_btn_yes = btn_yes_is_id ? pML->GetStringViaID(btn_yes) : btn_yes;
		std::wstring ws_btn_no  = btn_no_is_id  ? pML->GetStringViaID(btn_no)  : btn_no;
		MsgBox::Show(hWndParent, callback, ws_content, ws_title, ws_btn_yes, ws_btn_no);
	}

public:
	MsgBox(const std::wstring& wnd_id)
		: WindowEx(
			FL_NULL,
			ConfUI_Components::MsgBox_SkinFolder,
			ConfUI_Components::MsgBox_SkinFile,
			ConfUI_Components::MsgBox_ClassName,
			wnd_id)
		, m_callback(nullptr) {}

public:
	virtual UINT GetClassStyle() const override { return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS); }
	
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
	void SetCallback(MsgBoxCallback callback);
	void SetTitle(const std::wstring& title);
	void SetContent(const std::wstring& content);
	void SetButton(const std::wstring& btn_yes, const std::wstring& btn_no);

	void EndMsgBox(EMsgBoxRet eRet);

private:
	ui::Label*		m_title;
	ui::RichEdit*	m_content;
	ui::Button*		m_btn_yes;
	ui::Button*		m_btn_no;

	MsgBoxCallback	m_callback;
};

NS_UI_COMP_END