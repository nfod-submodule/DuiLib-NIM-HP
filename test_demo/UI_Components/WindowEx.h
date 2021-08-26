#pragma once

#include "UIlib.h"
#include "ConfUI_Components.h"

NS_UI_COMP_BEGIN

//-- �������
//****************************/
//-- class WindowEx
//****************************/
class WindowEx : public ui::WindowImplBase
{
protected:
	WindowEx(const std::wstring& wnd_class_name, const std::wstring& wnd_id)
		: m_wnd_class_name(wnd_class_name), m_wnd_id(wnd_id) {}
	virtual ~WindowEx() {}

public:
	/**
	 * ��ȡ���������Ľӿ�
	 * @return wstring ��������
	 */
	virtual std::wstring GetWindowClassName() const override { return m_wnd_class_name; }

	/**
	 * ��ȡ����id�Ľӿ�
	 * @return wstring ����id
	 */
	virtual std::wstring GetWindowId() const { return m_wnd_id; }

	/**
	 * ��������
	 * @param[in] hwndParent �����ھ��
	 * @param[in] pstrName ��������
	 * @param[in] dwStyle ������ʽ
	 * @param[in] dwExStyle ������չ��ʽ
	 * @param[in] isLayeredWindow �Ƿ񴴽��ֲ㴰��
	 * @param[in] rc ����λ��
	 * @return HWND ���ھ��
	 */
	virtual HWND Create(
		HWND hwndParent,
		LPCTSTR pstrName,
		DWORD dwStyle,
		DWORD dwExStyle,
		bool isLayeredWindow = true,
		const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

	/**
	 * �����ڱ����ٵ���Ϣ
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ����
	 * @param[in] lParam ����
	 * @param[out] bHandled ��Ϣ�Ƿ񱻴���
	 * @return LRESULT ������
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	/**
	 * ��������Ϣ
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ����
	 * @param[in] lParam ����
	 * @return LRESULT ������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	/**
	 * ����ESC����������Ϣ
	 * @param[out] bHandled ��Ϣ�Ƿ񱻴���
	 * @return void �޷���ֵ
	 */
	virtual void OnEsc(BOOL &bHandled);

protected:
	std::wstring m_wnd_class_name;	// ��������
	std::wstring m_wnd_id;			// ����id
};

NS_UI_COMP_END