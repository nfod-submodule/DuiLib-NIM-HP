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

bool WindowExMgr::RegisterWindow(const std::wstring wnd_class_name, const std::wstring wnd_id, WindowEx *wnd)
{
	if (IsStopRegister())
	{
		assert(!stop_register_);
		return false;
	}
	WindowsMap::iterator it = windows_map_.find(wnd_class_name);
	if (it != windows_map_.end())
	{
		std::map<std::wstring, WindowEx*>::iterator it2 = it->second.find(wnd_id);
		it->second[wnd_id] = wnd;
	}
	else
	{
		std::map<std::wstring, WindowEx*> id_win;
		id_win[wnd_id] = wnd;
		windows_map_[wnd_class_name] = id_win;
	}
	return true;
}

void WindowExMgr::UnRegisterWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id, WindowEx *wnd)
{
	WindowsMap::iterator it = windows_map_.find(wnd_class_name);
	if (it != windows_map_.end())
	{
		std::map<std::wstring, WindowEx*>::iterator it2 = it->second.find(wnd_id);
		if (it2 != it->second.end())
		{
			it->second.erase(it2);
		}
	}
}

WindowList WindowExMgr::GetAllWindows()
{
	WindowList list;
	WindowsMap::iterator it = windows_map_.begin();
	for (; it != windows_map_.end(); ++it)
	{
		std::map<std::wstring, WindowEx*>::iterator it2 = it->second.begin();
		for (; it2 != it->second.end(); ++it2)
		{
			WindowEx *wnd = (WindowEx *)(it2->second);
			if (wnd && ::IsWindow(wnd->GetHWND()))
			{
				list.push_back(wnd);
			}
		}
	}
	return list;
}

WindowEx* WindowExMgr::GetWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id)
{
	WindowsMap::iterator it = windows_map_.find(wnd_class_name);
	if (it != windows_map_.end())
	{
		std::map<std::wstring, WindowEx*>::iterator it2 = it->second.find(wnd_id);
		if (it2 != it->second.end())
		{
			WindowEx* wnd = (WindowEx*)(it2->second);
			if (wnd && ::IsWindow(wnd->GetHWND()))
			{
				return wnd;
			}
		}
	}
	return NULL;
}

WindowList WindowExMgr::GetWindowsByClassName(LPCTSTR classname)
{
	WindowList wnd_list;
	WindowsMap::iterator it = windows_map_.find(classname);
	if (it != windows_map_.end())
	{
		std::map<std::wstring, WindowEx*>::iterator it2 = it->second.begin();
		for (; it2 != it->second.end(); it2++)
		{
			WindowEx* wnd = (WindowEx*)(it2->second);
			if (wnd && ::IsWindow(wnd->GetHWND()))
			{
				wnd_list.push_back(wnd);
			}
		}
	}
	return wnd_list;
}

void WindowExMgr::DestroyAllWindows()
{
	SetStopRegister();

	WindowList lst_wnd = GetAllWindows();
	WindowList::iterator it = lst_wnd.begin();
	for (; it != lst_wnd.end(); ++it)
	{
		WindowEx *wnd = (WindowEx *)*it;
		if (wnd && ::IsWindow(wnd->GetHWND()))
		{
			::DestroyWindow(wnd->GetHWND());
		}
	}
}

NS_UI_COMP_END