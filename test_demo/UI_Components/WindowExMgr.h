#pragma once

#include "WindowEx.h"

NS_UI_COMP_BEGIN

//-- 窗体管理
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
	 * 创建（或激活）一个唯一存在的窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @return WindowType* 窗口指针
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
	 * 根据窗口类名和id注册窗口
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
	 * 根据窗口类名和id注销窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @param[in] wnd 窗口指针
	 * @return void 无返回值
	 */
	void UnRegisterWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id,
		WindowEx *wnd);

	/**
	 * 根据窗口类名和id获取窗口
	 * @param[in] wnd_class_name 窗口类名
	 * @param[in] wnd_id 窗口id
	 * @return WindowEx* 窗口指针
	 */
	WindowEx* GetWindow(
		const std::wstring& wnd_class_name,
		const std::wstring& wnd_id);

	/**
	 * 根据窗口类名获取对应的所有窗口
	 * @param[out] wnd_list 窗口列表
	 * @param[in] classname 窗口类名
	 * @return void 无返回值
	 */
	void GetWindowsByClassName(std::list<WindowEx*>& wnd_list, LPCWSTR class_name);

	/**
	 * 获取所有窗口获取窗口
	 * @param[out] wnd_list 窗口列表
	 * @return void 无返回值
	 */
	void GetAllWindows(std::list<WindowEx*>& wnd_list);

	/**
	 * 销毁所有窗口
	 * @return void 无返回值
	 */
	void DestroyAllWindows();

	/**
	 * 设置禁止窗口创建
	 * @param[in] stop 是否禁止窗口创建
	 * @return void 无返回值
	 */
	inline void SetStopRegister(bool stop = true) { stop_register_ = stop; }

	/**
	 * 是否禁止窗口创建
	 * @return bool true 禁止，false 不禁止
	 */
	inline bool IsStopRegister() { return stop_register_; }

private:
	bool stop_register_; // 禁止窗口创建
	// 所有窗口 // map<窗口类名，map<窗口id，窗口指针>>
	std::map<std::wstring, std::map<std::wstring, WindowEx*>> windows_map_;
};

NS_UI_COMP_END