#pragma once

#include "ConfUI_Components.h"

NS_UI_COMP_BEGIN

enum EMsgBoxRet { eMsgBox_YES, eMsgBox_NO };
typedef std::function<void(EMsgBoxRet eRet)> MsgBoxCallback; 

//****************************/
//-- class MsgBox
//****************************/
class MsgBox : public ui::WindowImplBase
{
public:
	/**
	 * 在屏幕中间显示一个消息框
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
		const std::wstring& btn_no = L"取消");

public:
	MsgBox() : m_callback(nullptr) {}

	virtual std::wstring GetSkinFolder() override { return ConfUI_Components::MsgBox_SkinFolder; }
	virtual std::wstring GetSkinFile() override { return ConfUI_Components::MsgBox_SkinFile; }
	virtual std::wstring GetWindowClassName() const override { return ConfUI_Components::MsgBox_ClassName; }
	virtual UINT GetClassStyle() const override { return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS); }

	virtual void Close(UINT nRet = IDOK) override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual void OnEsc(BOOL &bHandled);

	virtual void InitWindow() override;

private:
	bool OnClicked(ui::EventArgs* msg);

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