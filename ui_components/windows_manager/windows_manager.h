#pragma once

#include "window_ex.h"

NS_UI_COMP_BEGIN

//-- 窗口管理
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
	 * 创建（或激活）一个唯一存在的窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @return WindowExType* 窗口指针
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
	 * 创建一个新的窗口
	 * @param[in] hWndParent 父窗口句柄
	 * @param[in] bEnableParent 是否启用父窗口（即接受鼠标和键盘的输入）
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @return WindowExType* 窗口指针
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
	 * 注册窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @param[in] wnd 窗口指针
	 * @return bool true 成功，false 失败
	 */
	bool RegisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx* wnd);

	/**
	 * 注销窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @param[in] wnd 窗口指针
	 * @return void 无返回值
	 */
	void UnregisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx* wnd);

	/**
	 * 根据窗口类名和窗口id获取窗口（注：若存在多项，仅返回首项）
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @return WindowEx* 窗口指针
	 */
	WindowEx* GetWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id);

	/**
	 * 获取所有窗口
	 * @param[out] wnd_list 窗口列表
	 * @return void 无返回值
	 */
	void GetAllWindows(
		std::list<WindowEx*>& wnd_list);

	/**
	 * 销毁所有窗口
	 * @return void 无返回值
	 */
	void DestroyAllWindows();

	/**
	 * 退出程序（销毁所有窗口，发起终止请求）
	 * @return void 无返回值
	 */
	void PostQuit();

private:
	// 禁止窗口创建
	std::atomic<bool> m_bStopRegister;
	// 所有窗口 // map<窗口类名，multimap<窗口id，窗口指针>>
	std::mutex m_mutexWndEx;
	std::map<std::wstring, std::multimap<std::wstring, WindowEx*>> m_mapWndEx;
};

NS_UI_COMP_END