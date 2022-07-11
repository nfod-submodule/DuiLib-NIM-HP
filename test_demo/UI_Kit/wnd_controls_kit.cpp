#include "stdafx.h"
#include "wnd_controls_kit.h"
#include "wnd_controls.h"

//****************************/
//-- class wnd_controls_kit
//****************************/
//////////////////////////////////////////////////////////////////////////

wnd_controls_kit::wnd_controls_kit()
{
	UnRegisterCallback();
}

void wnd_controls_kit::RegisterCallback(
	const Callback_Error& cb_Error)
{
	m_cb_Error = cb_Error;
}

void wnd_controls_kit::UnRegisterCallback()
{
	m_cb_Error = nullptr;
}

void wnd_controls_kit::Invoke_Error(const std::wstring& error)
{
	try {
		if (m_cb_Error) {
			m_cb_Error(error);
		}
	}
	catch (const std::exception&) {}
}
