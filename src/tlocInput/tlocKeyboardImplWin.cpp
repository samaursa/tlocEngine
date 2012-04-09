#include "tlocKeyboardImplWin.h"

namespace tloc { namespace input { namespace priv {

#define KEYBOARD_IMPL_TEMP
#define KEYBOARD_IMPL_PARAMS  Keyboard<>
#define KEYBOARD_IMPL_TYPE    typename KeyboardImpl<KEYBOARD_IMPL_PARAMS>

  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    KeyboardImpl(parent_keyboard_type* a_parent,
                 const keyboard_param_type& a_params)
    : KeyboardImplBase(a_parent, a_params)
  {
  }

  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    TLOC_UNUSED(a_key);
    return false;
  }

  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Update()
  {
  }

};};};