#ifndef TLOC_KEYBOARD_IMPL_H
#define TLOC_KEYBOARD_IMPL_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input { namespace hid {

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
      left_sys, right_sys, power_sys, sleep_sys, wake_sys,

      Count,
    };  typedef s32 key_code_type;

    enum Modifier
    {
      NoModifier  = 0,
      Shift = 1 << 0,
      Ctrl  = 1 << 1,
      Alt   = 1 << 2,
    }; typedef s32 modifier_type;

    KeyboardEvent(KeyCode a_code = none, modifier_type a_mod = NoModifier) 
      : m_modifier(a_mod)
      , m_keyCode(a_code)
    { }

    char8 ToChar() const
    {
        if (m_modifier & Shift)
        {
          switch ( m_keyCode )
          {
          case KeyboardEvent::n1: return '!';
          case KeyboardEvent::n2: return '@';
          case KeyboardEvent::n3: return '#';
          case KeyboardEvent::n4: return '$';
          case KeyboardEvent::n5: return '%';
          case KeyboardEvent::n6: return '^';
          case KeyboardEvent::n7: return '&';
          case KeyboardEvent::n8: return '*';
          case KeyboardEvent::n9: return '(';
          case KeyboardEvent::n0: return ')';

          case KeyboardEvent::minus_main: return '_';
          case KeyboardEvent::equals: return '+';

          case KeyboardEvent::q: return 'Q';
          case KeyboardEvent::w: return 'W';
          case KeyboardEvent::e: return 'E';
          case KeyboardEvent::r: return 'R';
          case KeyboardEvent::t: return 'T';
          case KeyboardEvent::y: return 'Y';
          case KeyboardEvent::u: return 'U';
          case KeyboardEvent::i: return 'I';
          case KeyboardEvent::o: return 'O';
          case KeyboardEvent::p: return 'P';

          case KeyboardEvent::left_bracket: return '{';
          case KeyboardEvent::right_bracket: return '}';

          case KeyboardEvent::a: return 'A';
          case KeyboardEvent::s: return 'S';
          case KeyboardEvent::d: return 'D';
          case KeyboardEvent::f: return 'F';
          case KeyboardEvent::g: return 'G';
          case KeyboardEvent::h: return 'H';
          case KeyboardEvent::j: return 'J';
          case KeyboardEvent::k: return 'K';
          case KeyboardEvent::l: return 'L';

          case KeyboardEvent::semicolon: return ':';
          case KeyboardEvent::apostrophe: return '\"';
          case KeyboardEvent::grave: return '~';
          case KeyboardEvent::backslash: return '|';

          case KeyboardEvent::z: return 'Z';
          case KeyboardEvent::x: return 'X';
          case KeyboardEvent::c: return 'C';
          case KeyboardEvent::v: return 'V';
          case KeyboardEvent::b: return 'B';
          case KeyboardEvent::n: return 'N';
          case KeyboardEvent::m: return 'M';

          case KeyboardEvent::comma: return '<';
          case KeyboardEvent::period_main: return '>';
          case KeyboardEvent::slash: return '?';
          default: return 0;
          }
        }
        else
        {
          switch ( m_keyCode )
          {
          case KeyboardEvent::n1: return '1';
          case KeyboardEvent::n2: return '2';
          case KeyboardEvent::n3: return '3';
          case KeyboardEvent::n4: return '4';
          case KeyboardEvent::n5: return '5';
          case KeyboardEvent::n6: return '6';
          case KeyboardEvent::n7: return '7';
          case KeyboardEvent::n8: return '8';
          case KeyboardEvent::n9: return '9';
          case KeyboardEvent::n0: return '0';

          case KeyboardEvent::minus_main: return '-';
          case KeyboardEvent::equals: return '=';

          case KeyboardEvent::q: return 'q';
          case KeyboardEvent::w: return 'w';
          case KeyboardEvent::e: return 'e';
          case KeyboardEvent::r: return 'r';
          case KeyboardEvent::t: return 't';
          case KeyboardEvent::y: return 'y';
          case KeyboardEvent::u: return 'u';
          case KeyboardEvent::i: return 'i';
          case KeyboardEvent::o: return 'o';
          case KeyboardEvent::p: return 'p';

          case KeyboardEvent::left_bracket: return '[';
          case KeyboardEvent::right_bracket: return ']';

          case KeyboardEvent::a: return 'a';
          case KeyboardEvent::s: return 's';
          case KeyboardEvent::d: return 'd';
          case KeyboardEvent::f: return 'f';
          case KeyboardEvent::g: return 'g';
          case KeyboardEvent::h: return 'h';
          case KeyboardEvent::j: return 'j';
          case KeyboardEvent::k: return 'k';
          case KeyboardEvent::l: return 'l';

          case KeyboardEvent::semicolon: return ';';
          case KeyboardEvent::apostrophe: return '\'';
          case KeyboardEvent::grave: return '`';
          case KeyboardEvent::backslash: return '\\';


          case KeyboardEvent::z: return 'z';
          case KeyboardEvent::x: return 'x';
          case KeyboardEvent::c: return 'c';
          case KeyboardEvent::v: return 'v';
          case KeyboardEvent::b: return 'b';
          case KeyboardEvent::n: return 'n';
          case KeyboardEvent::m: return 'm';

          case KeyboardEvent::comma: return ',';
          case KeyboardEvent::period_main: return '.';
          case KeyboardEvent::slash: return '/';
          default: return 0;
        }
      }
    }

    modifier_type m_modifier;
    KeyCode       m_keyCode;
  };

};};};

namespace tloc { namespace input { namespace hid { namespace priv {

  ///-------------------------------------------------------------------------
  /// Keyboard implementation that must be specialized for each platform
  ///
  /// \tparam T_ParentKeyboard Platform-independant keyboard implementation that
  ///                          will eventually create platform-specific
  ///                          implementations
  ///-------------------------------------------------------------------------
  template <class T_ParentKeyboard> class KeyboardImpl;

  template <class T_ParentKeyboard, class T_ParamList>
  class KeyboardImplBase
    : public core_bclass::ImplBase<T_ParentKeyboard>
  {
  public:
    typedef core::base_classes::ImplBase<T_ParentKeyboard>  base_type;
    typedef typename base_type::parent_type                 parent_type;

    typedef T_ParamList                                   param_list_type;
    typedef typename parent_type::platform_type           platform_type;
    typedef typename parent_type::keycode_type            keycode_type;
    typedef typename parent_type::size_type               size_type;
    typedef typename parent_type::modifier_type           modifier_type;
    typedef u32                                           index_type;

  public:
    KeyboardImplBase(parent_type& a_parent, param_list_type a_params)
      : base_type(a_parent), m_params(a_params)
      , m_modifier(KeyboardEvent::NoModifier)
    { }

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
    modifier_type         m_modifier;
  };

};};};};

#endif