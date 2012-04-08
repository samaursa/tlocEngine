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

namespace tloc { namespace input { namespace priv {

  template <typename T_ParamList>
  class KeyboardImpl<Keyboard<T_ParamList>, T_ParamList>
    : public KeyboardImplBase<Keyboard<T_ParamList>, T_ParamList>
  {
  public:
    typedef Keyboard<T_ParamList>                           keyboard_type;
    typedef typename keyboard_type::platform_type           platform_type;
    typedef T_ParamList                                     param_list_type;
    typedef KeyboardImplBase<keyboard_type, param_list_type> base_type;
    typedef KeyboardImpl<keyboard_type, keyboard_type>      this_type;
    typedef typename base_type::parent_keyboard_type        parent_keybody_type;
    typedef typename base_type::keycode_type                keycode_type;

    KeyboardImpl(parent_keyboard_type* a_parent,
                 const param_list_type& a_paramList);

    ///-------------------------------------------------------------------------
    /// Query if 'a_key' is key down.
    ///
    /// @param  a_key The key.
    ///
    /// @return true if key is down, false if not.
    ///-------------------------------------------------------------------------
    bool IsKeyDown(keycode_type a_key) const { return false; }

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update() { }

  private:
    HWND          m_windowHandle;
  };

};};};

#endif