#include "tlocKeyboard.h"

#include "tlocCore/tlocTypes.inl"

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include "tlocKeyboardImplWin.h"
#else
# error "WIP"
#endif

namespace tloc { namespace input {

#define KEYBOARD_TEMP   typename T_ParamList, typename T_Policy, typename T_Platform
#define KEYBOARD_PARAMS T_ParamList, T_Policy, T_Platform
#define KEYBOARD_TYPE   typename Keyboard<KEYBOARD_PARAMS>

  template <KEYBOARD_TEMP>
  Keyboard<KEYBOARD_PARAMS>::Keyboard(const param_list_type& a_paramList)
  {
    m_impl = new impl_type(this, a_paramList);
  }

  template <KEYBOARD_TEMP>
  bool Keyboard<KEYBOARD_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    m_impl
  }

};};