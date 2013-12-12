#include "tlocKeyboardImplWin.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace input { namespace hid { namespace priv {

  //------------------------------------------------------------------------

#define KEYBOARD_IMPL_TEMP    typename T_ParentKeyboard
#define KEYBOARD_IMPL_PARAMS  T_ParentKeyboard
#define KEYBOARD_IMPL_TYPE    typename KeyboardImpl<KEYBOARD_IMPL_PARAMS>

  //------------------------------------------------------------------------
  // Free functions

  namespace {

    KeyboardEvent::KeyCode TranslateKeyCode(DWORD dwOfs)
    {
      switch(dwOfs)
      {
      case DIK_ESCAPE:      return KeyboardEvent::escape;
      case DIK_1:           return KeyboardEvent::n1;
      case DIK_2:           return KeyboardEvent::n2;
      case DIK_3:           return KeyboardEvent::n3;
      case DIK_4:           return KeyboardEvent::n4;
      case DIK_5:           return KeyboardEvent::n5;
      case DIK_6:           return KeyboardEvent::n6;
      case DIK_7:           return KeyboardEvent::n7;
      case DIK_8:           return KeyboardEvent::n8;
      case DIK_9:           return KeyboardEvent::n9;
      case DIK_0:           return KeyboardEvent::n0;
      case DIK_MINUS:       return KeyboardEvent::minus_main;
      case DIK_EQUALS:      return KeyboardEvent::equals;
      case DIK_BACK:        return KeyboardEvent::backspace;
      case DIK_TAB:         return KeyboardEvent::tab;
      case DIK_Q:           return KeyboardEvent::q;
      case DIK_W:           return KeyboardEvent::w;
      case DIK_E:           return KeyboardEvent::e;
      case DIK_R:           return KeyboardEvent::r;
      case DIK_T:           return KeyboardEvent::t;
      case DIK_Y:           return KeyboardEvent::y;
      case DIK_U:           return KeyboardEvent::u;
      case DIK_I:           return KeyboardEvent::i;
      case DIK_O:           return KeyboardEvent::o;
      case DIK_P:           return KeyboardEvent::p;
      case DIK_LBRACKET:    return KeyboardEvent::left_bracket;
      case DIK_RBRACKET:    return KeyboardEvent::right_bracket;
      case DIK_RETURN:      return KeyboardEvent::enter_main;
      case DIK_LCONTROL:    return KeyboardEvent::left_control;
      case DIK_A:           return KeyboardEvent::a;
      case DIK_S:           return KeyboardEvent::s;
      case DIK_D:           return KeyboardEvent::d;
      case DIK_F:           return KeyboardEvent::f;
      case DIK_G:           return KeyboardEvent::g;
      case DIK_H:           return KeyboardEvent::h;
      case DIK_J:           return KeyboardEvent::j;
      case DIK_K:           return KeyboardEvent::k;
      case DIK_L:           return KeyboardEvent::l;
      case DIK_SEMICOLON:   return KeyboardEvent::semicolon;
      case DIK_APOSTROPHE:  return KeyboardEvent::apostrophe;
      case DIK_GRAVE:       return KeyboardEvent::grave;
      case DIK_LSHIFT:      return KeyboardEvent::left_shift;
      case DIK_BACKSLASH:   return KeyboardEvent::backslash;
      case DIK_Z:           return KeyboardEvent::z;
      case DIK_X:           return KeyboardEvent::x;
      case DIK_C:           return KeyboardEvent::c;
      case DIK_V:           return KeyboardEvent::v;
      case DIK_B:           return KeyboardEvent::b;
      case DIK_N:           return KeyboardEvent::n;
      case DIK_M:           return KeyboardEvent::m;
      case DIK_COMMA:       return KeyboardEvent::comma;
      case DIK_PERIOD:      return KeyboardEvent::period_main;
      case DIK_SLASH:       return KeyboardEvent::slash;
      case DIK_RSHIFT:      return KeyboardEvent::right_shift;
      case DIK_MULTIPLY:    return KeyboardEvent::multiply_keypad;
      case DIK_LMENU:       return KeyboardEvent::left_alt;
      case DIK_SPACE:       return KeyboardEvent::space;
      case DIK_CAPITAL:     return KeyboardEvent::capital;
      case DIK_F1:          return KeyboardEvent::f1;
      case DIK_F2:          return KeyboardEvent::f2;
      case DIK_F3:          return KeyboardEvent::f3;
      case DIK_F4:          return KeyboardEvent::f4;
      case DIK_F5:          return KeyboardEvent::f5;
      case DIK_F6:          return KeyboardEvent::f6;
      case DIK_F7:          return KeyboardEvent::f7;
      case DIK_F8:          return KeyboardEvent::f8;
      case DIK_F9:          return KeyboardEvent::f9;
      case DIK_F10:         return KeyboardEvent::f10;
      case DIK_NUMLOCK:     return KeyboardEvent::numlock;
      case DIK_SCROLL:      return KeyboardEvent::scroll_lock;
      case DIK_NUMPAD7:     return KeyboardEvent::num7;
      case DIK_NUMPAD8:     return KeyboardEvent::num8;
      case DIK_NUMPAD9:     return KeyboardEvent::num9;
      case DIK_SUBTRACT:    return KeyboardEvent::minus_keypad;
      case DIK_NUMPAD4:     return KeyboardEvent::num4;
      case DIK_NUMPAD5:     return KeyboardEvent::num5;
      case DIK_NUMPAD6:     return KeyboardEvent::num6;
      case DIK_ADD:         return KeyboardEvent::add_keypad;
      case DIK_NUMPAD1:     return KeyboardEvent::num1;
      case DIK_NUMPAD2:     return KeyboardEvent::num2;
      case DIK_NUMPAD3:     return KeyboardEvent::num3;
      case DIK_NUMPAD0:     return KeyboardEvent::num0;
      case DIK_DECIMAL:     return KeyboardEvent::period_keypad;
      case DIK_F11:         return KeyboardEvent::f11;
      case DIK_F12:         return KeyboardEvent::f12;
      case DIK_F13:         return KeyboardEvent::f13;
      case DIK_F14:         return KeyboardEvent::f14;
      case DIK_F15:         return KeyboardEvent::f15;
      case DIK_PREVTRACK:   return KeyboardEvent::prev_track;
      case DIK_NEXTTRACK:   return KeyboardEvent::next_track;
      case DIK_NUMPADENTER: return KeyboardEvent::enter_keypad;
      case DIK_RCONTROL:    return KeyboardEvent::right_control;
      case DIK_MUTE:        return KeyboardEvent::mute;
      case DIK_CALCULATOR:  return KeyboardEvent::calculator;
      case DIK_PLAYPAUSE:   return KeyboardEvent::play_pause;
      case DIK_MEDIASTOP:   return KeyboardEvent::media_stop;
      case DIK_VOLUMEDOWN:  return KeyboardEvent::volume_down;
      case DIK_VOLUMEUP:    return KeyboardEvent::volume_up;
      case DIK_WEBHOME:     return KeyboardEvent::web_home;
      case DIK_DIVIDE:      return KeyboardEvent::divide_keypad;
      case DIK_SYSRQ:       return KeyboardEvent::sysrq;
      case DIK_RMENU:       return KeyboardEvent::right_alt;
      case DIK_PAUSE:       return KeyboardEvent::pause;
      case DIK_HOME:        return KeyboardEvent::home;
      case DIK_UP:          return KeyboardEvent::up;
      case DIK_PRIOR:       return KeyboardEvent::page_up;
      case DIK_LEFT:        return KeyboardEvent::left;
      case DIK_RIGHT:       return KeyboardEvent::right;
      case DIK_END:         return KeyboardEvent::end;
      case DIK_DOWN:        return KeyboardEvent::down;
      case DIK_NEXT:        return KeyboardEvent::page_down;
      case DIK_INSERT:      return KeyboardEvent::insert;
      case DIK_DELETE:      return KeyboardEvent::delete_main;
      case DIK_LWIN:        return KeyboardEvent::left_sys;
      case DIK_RWIN:        return KeyboardEvent::right_sys;
      case DIK_POWER:       return KeyboardEvent::power_sys;
      case DIK_SLEEP:       return KeyboardEvent::sleep_sys;
      case DIK_WAKE:        return KeyboardEvent::wake_sys;
      default:              return KeyboardEvent::none;
      }
    }
  }

  //------------------------------------------------------------------------
  // KeyboardImpl

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    KeyboardImpl(parent_type* a_parent,
                 const keyboard_param_type& a_params)
    : KeyboardImplBase(a_parent, a_params)
    , m_directInput(a_params.m_param2)
    , m_keyboard(TLOC_NULL)
    , m_windowPtr(a_params.m_param1)
  {
    core::fill(m_buffer, m_buffer + core_utils::ArraySize(m_buffer), false);
    DoInitialize();
  }

  template <KEYBOARD_IMPL_TEMP>
  KeyboardImpl<KEYBOARD_IMPL_PARAMS>::~KeyboardImpl()
  {
    if (m_keyboard)
    {
      m_keyboard->Unacquire();
      m_keyboard->Release();
      m_keyboard = TLOC_NULL;
    }
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    return m_buffer[a_key];
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    IsModifierDown(modifier_type a_modifier) const
  {
    return (m_modifier & a_modifier) == a_modifier;
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Update()
  {
    DoUpdate(policy_type());
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::Reset()
  {
    DoReset(policy_type());
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoInitialize()
  {
    if (FAILED(m_directInput->
      CreateDevice(GUID_SysKeyboard, &m_keyboard, TLOC_NULL)))
    {
      // LOG: Keyboard failed to initialize
      TLOC_LOG_INPUT_ERR() << "Keyboard failed to initialize";
      return;
    }

    if ( FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard)) )
    {
      TLOC_LOG_INPUT_ERR() << "Could not set keyboard device format";
      return;
    }

    DWORD coop = 0;

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_BACKGROUND)
    { coop |= DISCL_BACKGROUND; }
    else { coop |= DISCL_FOREGROUND; } // default

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_NONEXCLUSIVE)
    { coop |= DISCL_NONEXCLUSIVE; }
    else { coop |= DISCL_EXCLUSIVE; } // default

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_NOWINKEY)
    { coop |= DISCL_NOWINKEY; }

    if (!DoInitializeExtra(policy_type()))
    {
      TLOC_LOG_INPUT_ERR() << "Unable to acquire a buffered keyboard";
      return;
    }

    if (FAILED(m_keyboard->SetCooperativeLevel(m_windowPtr, coop)))
    {
      TLOC_LOG_INPUT_ERR() << "Keyboard cooperative level settings error";
      return;
    }

    HRESULT hr = m_keyboard->Acquire();
    if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
    {
      TLOC_LOG_INPUT_ERR() << "Unable to acquire a Win32 keyboard";
      return;
    }
  }

  template <KEYBOARD_IMPL_TEMP>
  bool KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoInitializeExtra(InputPolicy::Buffered)
  {
    DIPROPDWORD dipw;
    dipw.diph.dwSize        = sizeof(DIPROPDWORD);
    dipw.diph.dwHeaderSize  = sizeof(DIPROPHEADER);
    dipw.diph.dwObj         = 0;
    dipw.diph.dwHow         = DIPH_DEVICE;
    dipw.dwData             = buffer_size::keyboard_buffer_size;

    if (FAILED(m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipw.diph)))
    {
      return false;
    }

    return true;
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoUpdate(InputPolicy::Buffered)
  {
    DIDEVICEOBJECTDATA diBuff[buffer_size::keyboard_buffer_size];
    DWORD entries = buffer_size::keyboard_buffer_size;
    HRESULT hRes;

    hRes = m_keyboard->
      GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, TLOC_NULL);
    if (hRes != DI_OK)
    {
      // Try one more time
      hRes = m_keyboard->Acquire();
      if (hRes != DI_OK)
      {
        return;
      }
      else
      {
        hRes = m_keyboard->
          GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, TLOC_NULL);
        if (hRes != DI_OK)
        {
          // we don't have the keyboard, return
          return;
        }
      }
    }

    if (FAILED(hRes))
    { TLOC_LOG_INPUT_WARN() << "Could not get device data"; }

    for (tl_size i = 0; i < entries; ++i)
    {
      // Grab the key code that was pressed/released
      KeyboardEvent::KeyCode kc = TranslateKeyCode(diBuff[i].dwOfs);

      if (diBuff[i].dwData & 0x80)
      {
        if (kc == KeyboardEvent::left_control || kc == KeyboardEvent::right_control)
        {
          m_modifier |= KeyboardEvent::Ctrl;
        }
        else if (kc == KeyboardEvent::left_shift || kc == KeyboardEvent::right_shift)
        {
          m_modifier |= KeyboardEvent::Shift;
        }
        else if (kc == KeyboardEvent::left_alt || kc == KeyboardEvent::right_alt)
        {
          m_modifier |= KeyboardEvent::Alt;
        }

        m_parent->SendOnKeyPress( KeyboardEvent(kc) );
        m_buffer[kc] = true;

      }
      else
      {
        if (kc == KeyboardEvent::left_control || kc == KeyboardEvent::right_control)
        {
          m_modifier &= ~KeyboardEvent::Ctrl;
        }
        else if (kc == KeyboardEvent::left_shift || kc == KeyboardEvent::right_shift)
        {
          m_modifier &= ~KeyboardEvent::Shift;
        }
        else if (kc == KeyboardEvent::left_alt || kc == KeyboardEvent::right_alt)
        {
          m_modifier &= ~KeyboardEvent::Alt;
        }

        m_parent->SendOnKeyRelease( KeyboardEvent(kc) );
        m_buffer[kc] = false;

      }
    }
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::DoUpdate(InputPolicy::Immediate)
  {
    HRESULT hRes = m_keyboard->GetDeviceState(s_bufferSize, &m_rawBuffer);

    if (hRes == DIERR_INPUTLOST || hRes == DIERR_NOTACQUIRED)
    {
      hRes = m_keyboard->Acquire();
      if (hRes != DIERR_OTHERAPPHASPRIO)
      {
        m_keyboard->GetDeviceState(sizeof(s_bufferSize), &m_rawBuffer);
      }
    }

    for (DWORD i = 0; i < s_bufferSize; ++i)
    {
      if ( (m_rawBuffer[i] & 0x80) != 0)
      {
        m_buffer[TranslateKeyCode(i)] = true;
      }
    }
  }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    DoReset(InputPolicy::Buffered)
  { }

  template <KEYBOARD_IMPL_TEMP>
  void KeyboardImpl<KEYBOARD_IMPL_PARAMS>::
    DoReset(InputPolicy::Immediate)
  {
    core::fill_n(m_buffer, KeyboardEvent::Count, false);
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template KeyboardImpl< Keyboard<InputPolicy::Buffered> >;
  template KeyboardImpl< Keyboard<InputPolicy::Immediate> >;

};};};};