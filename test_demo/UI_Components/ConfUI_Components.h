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
