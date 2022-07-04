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

// 消息框
//****************************/
//-- class MsgBox
//****************************/
class MsgBox : public WindowEx
{
public:
	/**
	 * 在屏幕中间显示消息框
	 * @param[in] hWndParent 父窗口句柄，如果提供的话msgbox会显示在父窗口的中心，且为模态
	 * @param[in] callback 回调函数
	 * @param[in] content  消息内容
	 * @param[in] title    窗口标题
	 * @param[in] btn_yes  确定按钮内容，如果内容为空则不显示按钮
	 * @param[in] btn_no   取消按钮内容，如果内容为空则不显示按钮
	 * @return void 无返回值
	 */
	static void Show(
		HWND hWndParent,
		MsgBoxCallback callback,
		const std::wstring& content,
		const std::wstring& title = L"提示",
		const std::wstring& btn_yes = L"确定",
		const std::wstring& btn_no = L"取消")
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
	 * 关闭窗口
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * 初始窗口
	 */
	virtual void InitWindow() override;

private:
	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
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