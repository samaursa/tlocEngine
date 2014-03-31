#include "tlocKeyboardImplIphone.h"

#include <tlocCore/types/tlocAny.inl.h>

#import <tlocGraphics/window/tlocOpenGLViewIphone.h>

namespace tloc { namespace input { namespace hid { namespace priv {

#define KEYBOARD_IMPL_TEMP    typename T_ParentKeyboard
#define KEYBOARD_IMPL_PARAMS  T_ParentKeyboard
#define KEYBOARD_IMPL_TYPE    typename KeyboardImpl<KEYBOARD_IMPL_PARAMS>

  //------------------------------------------------------------------------
  // Free functions

  KeyboardEvent::KeyCode TranslateKeyCode(char dwOfs)
  {
    switch(dwOfs)
    {
    default:              return KeyboardEvent::none;
    }
  }

  //------------------------------------------------------------------------
  // KeyboardImpl

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    KeyboardImpl(parent_type* a_parent,
                 const keyboard_param_type& a_params)
    : base_type(*a_parent, a_params)
  {
    DoInitialize();
  }

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::~KeyboardImpl()
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    return false;
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Update()
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Reset()
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoInitialize()
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoInitializeExtra(InputPolicy::Buffered)
  {
    return false;
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoUpdate(InputPolicy::Buffered)
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoUpdate(InputPolicy::Immediate)
  {
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations
  template class KeyboardImpl< Keyboard<InputPolicy::Buffered> >;
  template class KeyboardImpl< Keyboard<InputPolicy::Immediate> >;

};};};};
