#pragma once

#include "WindowEx.h"

NS_UI_COMP_BEGIN

// map<����������map<����id������ָ��>>  ���ͬһ��ֻ��һ�����ڣ�ʹ��������Ϊid
typedef std::map<std::wstring, std::map<std::wstring, WindowEx*>> WindowsMap;
// list<����ָ��>
typedef std::list<WindowEx*> WindowList;

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
	 * @param[in] wnd_id ����id
	 * @return WindowType* ����ָ��
	 */
	template<typename WindowType, typename... TInstanceParams>
	static WindowType* SingletonShow(const std::wstring& wnd_id, const TInstanceParams&... params)
	{
		std::wstring wnd_class_name = wnd_id;
		WindowType* window = (WindowType*)WindowExMgr::GetInstance()->GetWindow(wnd_class_name, wnd_id);
		if (window == nullptr) {
			window = new WindowType(params...);
			window->Create(NULL, wnd_class_name, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
			window->CenterWindow();
			window->ShowWindow();
		}
		else {
			window->ActiveWindow();
		}
		return window;
	}

	/**
	 * ���ݴ���������idע�ᴰ��
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return bool true �ɹ���false ʧ��
	 */
	bool RegisterWindow(const std::wstring wnd_class_name, const std::wstring wnd_id, WindowEx *wnd);

	/**
	 * ���ݴ���������idע������
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void UnRegisterWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id, WindowEx *wnd);

	/**
	 * ���ݴ���������id��ȡ����
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowEx* ����ָ��
	 */
	WindowEx* GetWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id);

	/**
	 * ��ȡ���д��ڻ�ȡ����
	 * @return WindowList �����б�
	 */
	WindowList GetAllWindows();

	/**
	 * ���ݴ���������ȡ��Ӧ�����д���
	 * @param[in] classname ��������
	 * @return WindowList �����б�
	 */
	WindowList GetWindowsByClassName(LPCTSTR classname);

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
	void SetStopRegister(bool stop = true) { stop_register_ = stop; }

	/**
	 * �Ƿ��ֹ���ڴ���
	 * @return bool true ��ֹ��false ����ֹ
	 */
	bool IsStopRegister() { return stop_register_; }

private:
	WindowsMap	windows_map_;	// ���д���
	bool		stop_register_;	// ��ֹ���ڴ���
};

NS_UI_COMP_END