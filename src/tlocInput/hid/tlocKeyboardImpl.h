#ifndef TLOC_KEYBOARD_IMPL_H
#define TLOC_KEYBOARD_IMPL_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input {

  ///-------------------------------------------------------------------------
  /// A keyboard event that is sent as the argument when a keyboard event
  /// is fired.
  ///-------------------------------------------------------------------------
  struct KeyboardEvent
  {
    enum KeyCode
    {
      none = 0, // unsupported key was pressed
      escape,
      n1, n2, n3, n4, n5, n6, n7, n8, n9, n0,
      minus_main, equals, backspace, tab,
      q, w, e, r, t, y, u, i, o, p,
      left_bracket, right_bracket,
      enter_main,
      left_control,
      a, s, d, f, g, h, j, k, l,
      semicolon, apostrophe, grave, left_shift, backslash,
      z, x, c, v, b, n, m,
      comma, period_main, slash, right_shift,
      multiply_keypad, left_alt, space, capital,
      f1, f2, f3, f4, f5, f6, f7, f8, f9, f10,
      numlock, scroll_lock,
      num7, num8, num9, minus_keypad,
      num4, num5, num6, add_keypad,
      num1, num2, num3, num0, period_keypad,
      f11, f12, f13, f14, f15,
      prev_track, next_track,
      enter_keypad,
      right_control, mute, calculator, play_pause, media_stop,
      volume_down, volume_up, web_home,
      divide_keypad, slash_keypad,
      sysrq, right_alt, pause, home,
      up, page_up, left, right, end, down, page_down, insert, delete_main,
      left_sys, right_sys, sys_power, power_sys, sleep_sys, wake_sys,

      Count,
    };  typedef u32 key_code_type;

    enum Modifier
    {
      Shift = 1 << 0,
      Ctrl  = 1 << 1,
      Alt   = 1 << 2,
    };

    KeyboardEvent(KeyCode a_code = none) : m_keyCode(a_code) {}

    KeyCode   m_keyCode;
  };

};};

namespace tloc { namespace input { namespace priv {

  ///-------------------------------------------------------------------------
  /// Keyboard implementation that must be specialized for each platform
  ///
  /// \tparam T_ParentKeyboard Platform-independant keyboard implementation that
  ///                          will eventually create platform-specific
  ///                          implementations
  ///-------------------------------------------------------------------------
  template <class T_ParentKeyboard> class KeyboardImpl;

  template <class T_ParentKeyboard, class T_ParamList>
  class KeyboardImplBase : public core::ImplBase<T_ParentKeyboard>
  {
  public:
    typedef core::ImplBase<T_ParentKeyboard>              base_type;
    typedef typename base_type::parent_type               parent_type;

    typedef T_ParamList                                   param_list_type;
    typedef typename parent_type::platform_type           platform_type;
    typedef typename parent_type::keycode_type            keycode_type;
    typedef typename parent_type::size_type               size_type;
    typedef typename parent_type::modifier_type           modifier_type;
    typedef u32                                           index_type;

    KeyboardImplBase(parent_type* a_parent, param_list_type a_params)
      : base_type(a_parent), m_params(a_params)
    {
    }

    const param_list_type& GetParams() const
    {
      return m_params;
    }

    bool IsModifierDown(modifier_type a_mod) const
    {
      return (m_modifier & a_mod) != 0;
    }

  protected:
    enum {pressed_alt = 0, pressed_shift, pressed_ctrl, pressed_system,
          pressed_count};

    param_list_type       m_params;
    index_type            m_modifier;
  };

};};};

#endif