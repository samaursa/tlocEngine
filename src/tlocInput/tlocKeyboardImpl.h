#ifndef TLOC_KEYBOARD_IMPL_H
#define TLOC_KEYBOARD_IMPL_H

#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocNonCopyable.h"
#include "tlocCore/tlocPlatform.h"

namespace tloc { namespace input {

  ///-------------------------------------------------------------------------
  /// A keyboard event that is sent as the argument when a keyboard event
  /// is fired.
  ///-------------------------------------------------------------------------
  struct KeyboardEvent
  {
    enum KeyCode
    {
      NONE = 0,
      A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
      N1, N2, N3, N4, N5, N6, N7, N8, N9, N0, // top-row numbers
      Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, // Num-pad
      Esc,
      LControl, RControl,
      LShift, RShift,
      LAlt, RAlt,
      LSystem, RSystem,               // Platform specific keys
      Tilde, Dash, Equal,
      Backspace,
      LBracket, RBracket, BackSlash,  // [ ] and backslash
      SemiColon, Quote,               // ; '
      Comma, Period, Slash,
      Tab, Enter, Space,
      Insert, Delete, Home, End, PageUp, PageDown,
      NumDivide, NumMultiply, NumMinus, NumPlus, NumEnter, NumDecimal,
      NumHome, NumEnd, NumPageUp, NumPageDown,
      NumUp, NumDown, NumLeft, NumRight,
      NumInsert, NumDelete,
      Up, Down, Left, Right,
      F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
      PrintScreen,
      NumLock, CapsLock, ScrollLock,

      Count,
    };  typedef u32 key_code_type;

    KeyCode m_keyCode;
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
  class KeyboardImplBase : public core::NonCopyable
  {
  public:
    typedef T_ParentKeyboard                              parent_keyboard_type;
    typedef T_ParamList                                   param_list_type;
    typedef typename parent_keyboard_type::platform_type  platform_type;
    typedef typename parent_keyboard_type::keycode_type   keycode_type;
    typedef u32                                           index_type;

    KeyboardImplBase(parent_keyboard_type* a_parent, param_list_type a_params)
      : m_parent(a_parent), m_params(a_params)
    {
      TLOC_ASSERT_NOT_NULL(m_parent);
    }

    const param_list_type& GetParams() const;

  protected:
    enum {pressed_alt = 0, pressed_shift, pressed_ctrl, pressed_system,
          pressed_count};

    u32                   m_buffer[KeyboardEvent::Count];
    param_list_type       m_params;
    parent_keyboard_type* m_parent;
    bool                  m_altPressed,
                          m_shiftPressed,
                          m_ctrlPressed,
                          m_systemPressed;
  };

};};};

#endif