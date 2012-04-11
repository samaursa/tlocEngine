#include "tlocKeyboardImplWin.h"

namespace tloc { namespace input { namespace priv {

#define KEYBOARD_IMPL_TEMP    typename T_ParentKeyboard
#define KEYBOARD_IMPL_PARAMS  T_ParentKeyboard
#define KEYBOARD_IMPL_TYPE    typename KeyboardImpl<KEYBOARD_IMPL_PARAMS>

  template KeyboardImpl< Keyboard<> >;
  template KeyboardImpl< Keyboard<InputPolicy::UnBuffered> >;

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    KeyboardImpl(parent_type* a_parent,
                 const keyboard_param_type& a_params)
    : KeyboardImplBase(a_parent, a_params)
    , m_directInput(a_params.m_param2)
    , m_keyboard(NULL)
    , m_windowPtr(a_params.m_param1)
  {
    DoInitialize();
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    TLOC_UNUSED(a_key);
    return false;
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Update()
  {
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoInitialize()
  {
    if (FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL)))
    {
      // LOG: Keyboard failed to initialize
      return;
    }

    if ( FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard)) )
    {
      // LOG: Keyboard format error
      return;
    }

    DWORD coop = 0;
    // Default or...?
    if (m_params.m_param3 == 0)
    {
      coop = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
    }
    else
    {
      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_BACKGROUND)
      { coop = DISCL_BACKGROUND; }
      else { coop = DISCL_FOREGROUND; } // default

      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_NONEXCLUSIVE)
      { coop |= DISCL_NONEXCLUSIVE; }
      else { coop = DISCL_EXCLUSIVE; } // default

      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_NOWINKEY)
      { coop |= DISCL_NOWINKEY; }
    }

    if (FAILED(m_keyboard->SetCooperativeLevel(m_windowPtr, coop)))
    {
      // LOG: Keyboard cooperative level settings error
      return;
    }

    HRESULT hr = m_keyboard->Acquire();
    if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
    {
      // LOG: Unable to acquire Win32 keyboard
      return;
    }
  }

};};};