#pragma once

#include "windows_manager/window_ex.h"
#include "windows_manager/windows_manager.h"

NS_UI_COMP_BEGIN

// ���׵���ʾ���ڣ��൱��MessageBox�ļ򻯰�
//****************************/
//-- class Toast
//****************************/
class Toast : public WindowEx
{
public:
	/**
	 * ����Ļ�м���ʾ��ʾ��
	 * @param[in] content ��ʾ����
	 * @param[in] duration ����ʱ��(����),0����һֱ��ʾ
	 * @param[in] hWndParent �����ھ��������ṩ�Ļ�toast����ʾ�ڸ����ڵ�����
	 * @return void �޷���ֵ
	 */
	static void Show(
		const std::wstring& content,
		int duration = 0,
		HWND hWndParent = NULL)
	{
		Toast* pWnd = WindowExMgr::ShowNewWindow<Toast>(
			hWndParent,
			TRUE,
			ConfUI_Components::Toast_ClassName,
			ConfUI_Components::Toast_WindowId);
		if (pWnd) {
			pWnd->SetContent(content);
			pWnd->SetDuration(duration);
		}
	}

public:
	Toast(const std::wstring& wnd_id)
		: WindowEx(
			FL_NULL,
			ConfUI_Components::Toast_SkinFolder,
			ConfUI_Components::Toast_SkinFile,
			ConfUI_Components::Toast_ClassName,
			wnd_id) {}

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

	/**
	 * ������Ϣ���ɷ�����
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @return LRESULT ������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnEventClick(ui::EventArgs* msg);

private:
	/**
	 * ������ʾ����
	 * @param[in] str ��ʾ����
	 * @return void	�޷���ֵ
	 */
	void SetContent(const std::wstring& str);

	/**
	 * ���ô��ڵ���ʾʱ��
	 * @param[in] duration ����ʱ�䣬��λ����
	 * @return void	�޷���ֵ
	 */
	void SetDuration(int duration);

private:
	ui::RichEdit*	m_content;
	ui::Button*		m_close_btn;
};

//****************************/
//-- class Toast_Kit
//****************************/
class Toast_Kit
{
public:
	SINGLETON_DEFINE(Toast_Kit);
	Toast_Kit() {}

public:
	/**
	 * ���ô��ڵ���ʾʱ��
	 * @param[in] pWnd ����ָ��
	 * @param[in] duration ����ʱ�䣬��λ����
	 * @return void �޷���ֵ
	 */
	void SetDuration(
		Toast* pWnd,
		int duration);

	/**
	 * ȡ�����ڵ���ʾʱ������ʱ������Ӧ��
	 * @param[in] pWnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void DelDuration(
		Toast* pWnd);

private:
	/**
	 * �ﵽ��ʾʱ����رմ���
	 * @param[in] pWnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void Duration_ToClose(
		Toast* pWnd);

private:
	// map<����ָ��, ����ʱ��>
	std::mutex m_mutexWnd;
	std::map<Toast*, int> m_mapWnd;
};

NS_UI_COMP_END