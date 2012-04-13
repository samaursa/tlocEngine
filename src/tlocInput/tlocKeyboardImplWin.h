#ifndef TLOC_KEYBOARD_IMPL_WIN_H
#define TLOC_KEYBOARD_IMPL_WIN_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"

#include "tlocInputTypes.h"
#include "tlocKeyboard.h"
#include "tlocKeyboardImpl.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <dinput.h>

namespace tloc { namespace input {

  typedef KeyboardParamList<HWND, IDirectInput8*, parameter_options::Type>
    windows_keyboard_param_type;

};};

namespace tloc { namespace input { namespace priv {

  template <typename T_ParentKeyboard>
  class KeyboardImpl
    : public KeyboardImplBase<T_ParentKeyboard, windows_keyboard_param_type>
  {
  public:
    typedef windows_keyboard_param_type            keyboard_param_type;
    typedef T_ParentKeyboard                       parent_type;
    typedef KeyboardImpl<parent_type>              this_type;
    typedef KeyboardImplBase
      <parent_type, keyboard_param_type>           base_type;

    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename base_type::keycode_type          keycode_type;

    KeyboardImpl(parent_type* a_parent,
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

  private:

    void        DoInitialize();
    // Buffered input requires extra initialization
    bool        DoInitializeExtra(InputPolicy::Buffered);
    // Immediate mode does not require anything special
    bool        DoInitializeExtra(InputPolicy::Immediate) { return true; }

    void        DoUpdate(InputPolicy::Buffered);
    void        DoUpdate(InputPolicy::Immediate);

  private:

    IDirectInput8*        m_directInput;
    IDirectInputDevice8*  m_keyboard;
    HWND                  m_windowPtr;

    bool                   m_buffer[KeyboardEvent::Count];

    static const size_type s_bufferSize = 256;
    uchar8                  m_rawBuffer[s_bufferSize];
  };

};};};

#endif