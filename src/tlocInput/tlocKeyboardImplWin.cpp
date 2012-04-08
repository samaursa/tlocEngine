#include "tlocKeyboardImplWin.h"

namespace tloc { namespace input { namespace priv {

#define KEYBOARD_IMPL_TEMP    typename T_ParamList
#define KEYBOARD_IMPL_PARAMS  Keyboard<T_ParamList>, T_ParamList
#define KEYBOARD_IMPL_TYPE    typename KeyboardImpl<KEYBOARD_IMPL_PARAMS>

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    KeyboardImpl(parent_keyboard_type* a_parent,
                 const param_list_type& a_paramList)
  {
  }

};};};