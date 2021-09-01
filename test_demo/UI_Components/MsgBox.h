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
	 * ����Ļ�м���ʾһ����Ϣ��
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
		const std::wstring& btn_no = L"ȡ��");

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