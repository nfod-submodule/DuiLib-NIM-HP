#include "stdafx.h"
#include "WindowExMgr.h"

NS_UI_COMP_BEGIN

//****************************/
//-- class WindowExMgr
//****************************/
//////////////////////////////////////////////////////////////////////////

WindowExMgr::WindowExMgr()
{
	stop_register_ = false;
	windows_map_.clear();
}

WindowExMgr::~WindowExMgr()
{
	windows_map_.clear();
}

bool WindowExMgr::RegisterWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id,
	WindowEx* wnd)
{
	if (IsStopRegister())
	{
		assert(!stop_register_);
		return false;
	}
	auto iter1 = windows_map_.find(wnd_class_name);
	if (iter1 != windows_map_.end())
	{
		auto iter2 = iter1->second.find(wnd_id);
		if (iter2 != iter1->second.end()) {
			wprintf(L"The window <class name: %s, id: %s> has already registered !", wnd_class_name.c_str(), wnd_id.c_str());
		}
		iter1->second[wnd_id] = wnd;
	}
	else
	{
		std::map<std::wstring, WindowEx*> subitem_map_; // map<´°¿Úid£¬´°¿ÚÖ¸Õë>
		subitem_map_[wnd_id] = wnd;
		windows_map_[wnd_class_name] = subitem_map_;
	}
	return true;
}

void WindowExMgr::UnRegisterWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id,
	WindowEx* wnd)
{
	auto iter1 = windows_map_.find(wnd_class_name);
	if (iter1 != windows_map_.end())
	{
		auto iter2 = iter1->second.find(wnd_id);
		if (iter2 != iter1->second.end())
		{
			iter1->second.erase(iter2);
		}
	}
}

WindowEx* WindowExMgr::GetWindow(
	const std::wstring& wnd_class_name,
	const std::wstring& wnd_id)
{
	auto iter1 = windows_map_.find(wnd_class_name);
	if (iter1 != windows_map_.end())
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

void WindowExMgr::GetWindowsByClassName(std::list<WindowEx*>& wnd_list, LPCWSTR class_name)
{
	wnd_list.clear();
	if (class_name == nullptr) {
		return;
	}
	auto iter1 = windows_map_.find(class_name);
	if (iter1 != windows_map_.end())
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

void WindowExMgr::GetAllWindows(std::list<WindowEx*>& wnd_list)
{
	for (auto iter1 = windows_map_.begin(); iter1 != windows_map_.end(); ++iter1)
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
	SetStopRegister();
	std::list<WindowEx*> wnd_list;
	GetAllWindows(wnd_list);
	for (auto iter = wnd_list.begin(); iter != wnd_list.end(); ++iter)
	{
		WindowEx* wnd = (WindowEx*)(*iter);
		if (wnd && ::IsWindow(wnd->GetHWND())) {
			::DestroyWindow(wnd->GetHWND());
		}
	}
}

NS_UI_COMP_END