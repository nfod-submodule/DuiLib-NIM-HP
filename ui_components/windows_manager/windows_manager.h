#pragma once

#include "window_ex.h"

NS_UI_COMP_BEGIN

//-- ���ڹ���
//****************************/
//-- class WindowExMgr
//****************************/
class WindowExMgr
{
private:
	WindowExMgr& operator=(const WindowExMgr&) = delete;
	WindowExMgr(const WindowExMgr&) = delete;
	WindowExMgr();
	~WindowExMgr();
public:
	static WindowExMgr* GetInstance();

	/**
	 * �������򼤻һ��Ψһ���ڵĴ���
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowExType* ����ָ��
	 */
	template<typename WindowExType, typename... TInstanceParams>
	static WindowExType* ShowSingleton(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		const TInstanceParams&... params)
	{
		WindowEx* pWndEx = WindowExMgr::GetInstance()->GetWindow(wnd_class_name, wnd_id);
		if (pWndEx)
		{
			WindowExType* pWndExT = (WindowExType*)pWndEx;
			if (!pWndExT) {
				return NULL;
			}
			pWndExT->ActiveWindow();
			return pWndExT;
		}
		else
		{
			WindowExType* pWndExT = new WindowExType(wnd_id, params...);
			pWndEx = (WindowEx*)pWndExT;
			if (!pWndEx || 0 != wnd_class_name.compare(pWndEx->GetWindowClassName()) ||
				!pWndEx->Create(NULL, wnd_class_name.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0)) {
				if (pWndExT) {
					delete pWndExT;
					pWndExT = NULL;
				}
				return NULL;
			}
			pWndEx->CenterWindow();
			pWndEx->ShowWindow();
			return pWndExT;
		}
	}

	/**
	 * ����һ���µĴ���
	 * @param[in] hWndParent �����ھ��
	 * @param[in] bEnableParent �Ƿ����ø����ڣ����������ͼ��̵����룩
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowExType* ����ָ��
	 */
	template<typename WindowExType, typename... TInstanceParams>
	static WindowExType* ShowNewWindow(
		HWND hWndParent,
		BOOL bEnableParent,
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		const TInstanceParams&... params)
	{
		WindowExType* pWndExT = new WindowExType(wnd_id, params...);
		WindowEx* pWndEx = (WindowEx*)pWndExT;
		if (!pWndEx || 0 != wnd_class_name.compare(pWndEx->GetWindowClassName()) ||
			!pWndEx->Create(hWndParent, wnd_class_name.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0)) {
			if (pWndExT) {
				delete pWndExT;
				pWndExT = NULL;
			}
			return NULL;
		}
		if (hWndParent) {
			::EnableWindow(hWndParent, bEnableParent);
		}
		pWndEx->CenterWindow();
		pWndEx->ShowWindow();
		return pWndExT;
	}

public:
	/**
	 * ע�ᴰ��
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return bool true �ɹ���false ʧ��
	 */
	bool RegisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx* wnd);

	/**
	 * ע������
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void UnregisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx* wnd);

	/**
	 * ���ݴ��������ʹ���id��ȡ���ڣ�ע�������ڶ�����������
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowEx* ����ָ��
	 */
	WindowEx* GetWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id);

	/**
	 * ��ȡ���д���
	 * @param[out] wnd_list �����б�
	 * @return void �޷���ֵ
	 */
	void GetAllWindows(
		std::list<WindowEx*>& wnd_list);

	/**
	 * �������д���
	 * @return void �޷���ֵ
	 */
	void DestroyAllWindows();

	/**
	 * �˳������������д��ڣ�������ֹ����
	 * @return void �޷���ֵ
	 */
	void PostQuit();

private:
	// ��ֹ���ڴ���
	std::atomic<bool> m_bStopRegister;
	// ���д��� // map<����������multimap<����id������ָ��>>
	std::mutex m_mutexWndEx;
	std::map<std::wstring, std::multimap<std::wstring, WindowEx*>> m_mapWndEx;
};

NS_UI_COMP_END