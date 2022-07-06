#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

//-- ���ڻ���
//****************************/
//-- class WindowEx
//****************************/
class WindowEx : public ui::WindowImplBase
{
protected:
	//-- ���Ʊ�ǣ�CtrlFL��
	static CONST ULONG FL_NULL		= 0;
	static CONST ULONG FL_QUIT		= 1 << 0;	// �رմ���ʱ�˳�����
	static CONST ULONG FL_ESC_CLOSE = 1 << 1;	// ��ESC���رմ���
	static CONST ULONG FL_N_LAYERED	= 1 << 2;	// �Ƿֲ㴰�ڣ�dwExStyle ^= WS_EX_LAYERED��

protected:
	WindowEx(
		const ULONG CtrlFL,
		const std::wstring& SkinFolder,
		const std::wstring& SkinFile,
		const std::wstring& ClassName,
		const std::wstring& WindowId)
	{
		m_CtrlFL     = CtrlFL;
		m_SkinFolder = SkinFolder;
		m_SkinFile   = SkinFile;
		m_ClassName  = ClassName;
		m_WindowId   = WindowId;
	}
	virtual ~WindowEx() {}

public:
	/**
	 * ���������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			Ҫ���ƵĴ��ڵ�xml�����ļ�
	 * GetWindowClassName	����Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override { return m_SkinFolder; }
	virtual std::wstring GetSkinFile()   override { return m_SkinFile; }
	virtual std::wstring GetWindowClassName() const override { return m_ClassName; }

	/**
	 * ��ȡ����id
	 */
	virtual std::wstring GetWindowId() const { return m_WindowId; };

	/**
	 * �رմ���
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * ��������
	 * @param[in] hWndParent �����ھ��
	 * @param[in] pstrName ��������
	 * @param[in] dwStyle ������ʽ
	 * @param[in] dwExStyle ������չ��ʽ
	 * @param[in] isLayeredWindow �Ƿ񴴽��ֲ㴰��
	 * @param[in] rc ����λ��
	 * @return HWND ���ھ��
	 */
	virtual HWND Create(
		HWND hWndParent,
		LPCTSTR pstrName,
		DWORD dwStyle,
		DWORD dwExStyle,
		bool isLayeredWindow = true,
		const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

	/**
	 * ���յ����ڹر���Ϣʱ������
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return ������Ϣ������
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	/**
	 * �����ڱ����ٵ���Ϣ
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
	 * @return LRESULT ������
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	/**
	 * ������Ϣ���ɷ�����
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @return LRESULT ������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

protected:
	ULONG        m_CtrlFL;		// ���Ʊ��
	std::wstring m_SkinFolder;	// ��Դ·��
	std::wstring m_SkinFile;	// �����ļ�
	std::wstring m_ClassName;	// ��������
	std::wstring m_WindowId;	// ����id
};

NS_UI_COMP_END