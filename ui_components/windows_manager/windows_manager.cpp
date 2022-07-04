#include "stdafx.h"
#include "windows_manager.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class WindowExMgr
//****************************/
//////////////////////////////////////////////////////////////////////////

WindowExMgr::WindowExMgr()
	: m_bStopRegister(false)
{
	m_mapWndEx.clear();
}

WindowExMgr::~WindowExMgr()
{
	m_mapWndEx.clear();
}

WindowExMgr* WindowExMgr::GetInstance()
{
	static WindowExMgr _instance;
	return &_instance;
}

bool WindowExMgr::RegisterWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id,
	WindowEx* wnd)
{
	if (m_bStopRegister) {
		wprintf(L"The window <class name: %s, id: %s, wnd: %p> register stopped !\n", wnd_class_name.c_str(), wnd_id.c_str(), wnd);
		return false;
	}
	std::lock_guard<std::mutex> lock(m_mutexWndEx);
	auto iter1 = m_mapWndEx.find(wnd_class_name);
	if (iter1 != m_mapWndEx.end())
	{
		auto er = iter1->second.equal_range(wnd_id);
		for (auto iter2 = er.first; iter2 != er.second; ++iter2)
		{
			if (iter2->second == wnd) {
				wprintf(L"The window <class name: %s, id: %s, wnd: %p> has already registered !\n", wnd_class_name.c_str(), wnd_id.c_str(), wnd);
				return false;
			}
		}
		iter1->second.insert(std::make_pair(wnd_id, wnd));
	}
	else
	{
		std::multimap<std::wstring, WindowEx*> item;
		item.insert(std::make_pair(wnd_id, wnd));
		m_mapWndEx[wnd_class_name] = item;
	}
	ui::GlobalManager::AddPreMessage(wnd);
	return true;
}

void WindowExMgr::UnregisterWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id,
	WindowEx* wnd)
{
	std::lock_guard<std::mutex> lock(m_mutexWndEx);
	auto iter1 = m_mapWndEx.find(wnd_class_name);
	if (iter1 != m_mapWndEx.end())
	{
		auto er = iter1->second.equal_range(wnd_id);
		for (auto iter2 = er.first; iter2 != er.second; ++iter2)
		{
			if (iter2->second == wnd) {
				ui::GlobalManager::RemovePreMessage(wnd);
				iter1->second.erase(iter2);
				break;
			}
		}
		if (iter1->second.empty()) {
			m_mapWndEx.erase(iter1);
		}
	}
}

WindowEx* WindowExMgr::GetWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id)
{
	std::lock_guard<std::mutex> lock(m_mutexWndEx);
	auto iter1 = m_mapWndEx.find(wnd_class_name);
	if (iter1 != m_mapWndEx.end())
	{
		auto iter2 = iter1->second.find(wnd_id);
		if (iter2 != iter1->second.end())
		{
			WindowEx* wnd = (WindowEx*)(iter2->second);
			if (wnd && ::IsWindow(wnd->GetHWND())) {
				return wnd;
			}
		}
	}
	return NULL;
}

void WindowExMgr::GetAllWindows(
	std::list<WindowEx*>& wnd_list)
{
	wnd_list.clear();
	std::lock_guard<std::mutex> lock(m_mutexWndEx);
	for (auto iter1 = m_mapWndEx.begin(); iter1 != m_mapWndEx.end(); ++iter1)
	{
		for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); ++iter2)
		{
			WindowEx* wnd = (WindowEx*)(iter2->second);
			if (wnd && ::IsWindow(wnd->GetHWND())) {
				wnd_list.push_back(wnd);
			}
		}
	}
}

void WindowExMgr::DestroyAllWindows()
{
	// 设置禁止
	m_bStopRegister = true;
	// 获取所有
	std::list<WindowEx*> wnd_list;
	GetAllWindows(wnd_list);
	// 销毁所有
	for (auto iter = wnd_list.begin(); iter != wnd_list.end(); ++iter)
	{
		WindowEx* wnd = (WindowEx*)(*iter);
		if (wnd && ::IsWindow(wnd->GetHWND())) {
			::DestroyWindow(wnd->GetHWND());
		}
	}
	// 取消禁止
	m_bStopRegister = false;
}

NS_UI_COMP_END