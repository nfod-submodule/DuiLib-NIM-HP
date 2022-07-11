#ifndef _PUBLIC_DEFINE_H_
#define _PUBLIC_DEFINE_H_

// c++ header
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <mutex>
#include <atomic>

// namespace ui_comp
#ifdef __cplusplus
#   define NS_UI_COMP_BEGIN  namespace ui_comp {
#   define NS_UI_COMP_END    }
#   define USING_NS_UI_COMP  using namespace ui_comp
#   define NS_UI_COMP        ::ui_comp
#else
#   define NS_UI_COMP_BEGIN
#   define NS_UI_COMP_END
#   define USING_NS_UI_COMP
#   define NS_UI_COMP
#endif

NS_UI_COMP_BEGIN

enum ThreadId
{
	kThreadUI
};

//-- ����
// SkinFolder	��Դ·��
// SkinFile		�����ļ�
// ClassName	��������
// WindowId		����id
namespace ConfUI_Components
{
	// msgbox - ��Ϣ��
	static const wchar_t* MsgBox_SkinFolder	= L"ui_comp_msgbox";
	static const wchar_t* MsgBox_SkinFile	= L"msgbox.xml";
	static const wchar_t* MsgBox_ClassName	= L"msgbox";
	static const wchar_t* MsgBox_WindowId	= L"msgbox";

	// shadow - ��Ӱ����
	static const wchar_t* Shadow_SkinFolder	= L"ui_comp_shadow";
	static const wchar_t* Shadow_SkinFile	= L"shadow.xml";
	static const wchar_t* Shadow_ClassName	= L"shadow";
	static const wchar_t* Shadow_WindowId	= L"shadow";

	// toast - ��ʾ��
	static const wchar_t* Toast_SkinFolder	= L"ui_comp_toast";
	static const wchar_t* Toast_SkinFile	= L"toast.xml";
	static const wchar_t* Toast_ClassName	= L"toast";
	static const wchar_t* Toast_WindowId	= L"toast";
}

NS_UI_COMP_END

#endif // _PUBLIC_DEFINE_H_