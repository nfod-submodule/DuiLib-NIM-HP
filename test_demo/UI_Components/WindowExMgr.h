#pragma once

#include "WindowEx.h"

NS_UI_COMP_BEGIN

//-- �������
//****************************/
//-- class WindowExMgr
//****************************/
class WindowExMgr
{
public:
	SINGLETON_DEFINE(WindowExMgr);
	WindowExMgr();
	virtual ~WindowExMgr();

	/**
	 * �������򼤻һ��Ψһ���ڵĴ���
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowType* ����ָ��
	 */
	template<typename WindowType, typename... TInstanceParams>
	static WindowType* SingletonShow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		const TInstanceParams&... params)
	{
		WindowType* pWndExT = NULL;
		WindowEx* pWndEx = WindowExMgr::GetInstance()->GetWindow(wnd_class_name, wnd_id);
		if (pWndEx)
		{
			pWndExT = (WindowType*)pWndEx;
			if (pWndExT) {
				pWndExT->ActiveWindow();
			}
		}
		else
		{
			pWndExT = new WindowType(wnd_id, params...);
			pWndEx = (WindowEx*)pWndExT;
			if (pWndExT && pWndEx && 0 == wnd_class_name.compare(pWndEx->GetWindowClassName())) {
				pWndExT->Create(NULL, NULL, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
				pWndExT->CenterWindow();
				pWndExT->ShowWindow();
			}
			else if (pWndExT) {
				delete pWndExT;
				pWndExT = NULL;
			}
		}
		return pWndExT;
	}

	/**
	 * ���ݴ���������idע�ᴰ��
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
	 * ���ݴ���������idע������
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void UnRegisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx *wnd);

	/**
	 * ���ݴ���������id��ȡ����
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowEx* ����ָ��
	 */
	WindowEx* GetWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id);

	/**
	 * ���ݴ���������ȡ��Ӧ�����д���
	 * @param[out] wnd_list �����б�
	 * @param[in] classname ��������
	 * @return void �޷���ֵ
	 */
	void GetWindowsByClassName(std::list<WindowEx*>& wnd_list, LPCWSTR class_name);

	/**
	 * ��ȡ���д��ڻ�ȡ����
	 * @param[out] wnd_list �����б�
	 * @return void �޷���ֵ
	 */
	void GetAllWindows(std::list<WindowEx*>& wnd_list);

	/**
	 * �������д���
	 * @return void �޷���ֵ
	 */
	void DestroyAllWindows();

	/**
	 * ���ý�ֹ���ڴ���
	 * @param[in] stop �Ƿ��ֹ���ڴ���
	 * @return void �޷���ֵ
	 */
	inline void SetStopRegister(bool stop = true) { stop_register_ = stop; }

	/**
	 * �Ƿ��ֹ���ڴ���
	 * @return bool true ��ֹ��false ����ֹ
	 */
	inline bool IsStopRegister() { return stop_register_; }

private:
	bool stop_register_; // ��ֹ���ڴ���
	// ���д��� // map<����������map<����id������ָ��>>
	std::map<std::wstring, std::map<std::wstring, WindowEx*>> windows_map_;
};

NS_UI_COMP_END