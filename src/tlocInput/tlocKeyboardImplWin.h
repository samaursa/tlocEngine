#ifndef TLOC_KEYBOARD_IMPL_WIN_H
#define TLOC_KEYBOARD_IMPL_WIN_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"

#include "tlocKeyboard.h"
#include "tlocKeyboardImpl.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <dinput.h>

namespace tloc { namespace input {

  typedef KeyboardParamList<HWND> windows_keyboard_param_type;

};};

namespace tloc { namespace input { namespace priv {

  template <>
  class KeyboardImpl<Keyboard<> >
    : public KeyboardImplBase<Keyboard<>, windows_keyboard_param_type>
  {
  public:
    typedef windows_keyboard_param_type            keyboard_param_type;
    typedef Keyboard<>                             keyboard_type;
    typedef KeyboardImpl<keyboard_type>            this_type;
    typedef KeyboardImplBase
      <keyboard_type, keyboard_param_type>         base_type;

    typedef keyboard_type::platform_type           platform_type;
    typedef base_type::parent_keyboard_type        parent_keybody_type;
    typedef base_type::keycode_type                keycode_type;

    KeyboardImpl(parent_keyboard_type* a_parent,
                 const keyboard_param_type& a_params);

    ///-------------------------------------------------------------------------
    /// Query if 'a_key' is key down.
    ///
    /// @param  a_key The key.
    ///
    /// @return true if key is down, false if not.
    ///-------------------------------------------------------------------------
    bool IsKeyDown(keycode_type a_key) const;

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();
  };

};};};

#endif