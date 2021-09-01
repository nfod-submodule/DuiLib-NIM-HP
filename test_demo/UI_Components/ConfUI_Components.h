#pragma once

// namespace ui_comp
#ifdef __cplusplus
#   define NS_UI_COMP_BEGIN  namespace ui_comp {
#   define NS_UI_COMP_END    }
#   define USING_NS_UI_COMP  using namespace ui_comp
#   define NS_UI_COMP        ::ui_comp
#else
#   define NS_HELPER_BEGIN
#   define NS_HELPER_END
#   define USING_NS_HELPER
#   define NS_HELPER
#endif

//-- ≈‰÷√
namespace ConfUI_Components
{
	static const wchar_t* MsgBox_SkinFolder		= L"ui_comp_msgbox";
	static const wchar_t* MsgBox_SkinFile		= L"msgbox.xml";
	static const wchar_t* MsgBox_ClassName		= L"MsgBox";
	
	static const wchar_t* MenuWnd_SkinFolder	= L"ui_comp_menuwnd";
	static const wchar_t* MenuWnd_ClassName		= L"MenuWnd";
	
	static const wchar_t* Toast_SkinFolder		= L"ui_comp_toast";
	static const wchar_t* Toast_SkinFile		= L"toast.xml";
	static const wchar_t* Toast_ClassName		= L"Toast";
}
