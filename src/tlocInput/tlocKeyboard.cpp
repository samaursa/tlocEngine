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

#define KEYBOARD_TEMP   typename T_Policy, typename T_Platform
#define KEYBOARD_PARAMS T_Policy, T_Platform
#define KEYBOARD_TYPE   typename Keyboard<KEYBOARD_PARAMS>

  template <KEYBOARD_TEMP>
  template <typename T_ParamList>
  Keyboard<KEYBOARD_PARAMS>::Keyboard(const T_ParamList& a_paramList)
  {
  }

};};