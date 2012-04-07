#ifndef TLOC_KEYBOARD_H
#define TLOC_KEYBOARD_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTemplateDispatch.h"

namespace tloc { namespace input {

  struct KeyboardEvent
  {
    enum KeyCode
    {
      NONE,
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
    };

    KeyCode m_keyCode;
  };

  struct KeyboardCallbacks
  {
    virtual void OnKeyPress(const KeyboardEvent& a_event) = 0;
    virtual void OnKeyRelease(const KeyboardEvent& a_event) = 0;
  };

  template <typename T>
  struct KeyboardCallbackGroupT:
    public core::CallbackGroupTArray<T, KeyboardCallbacks>::type
  {
    virtual void OnKeyPress(const KeyboardEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->OnKeyPress(a_event);
      }
    }

    virtual void OnKeyRelease(const KeyboardEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->OnKeyRelease(a_event);
      }
    }
  };

  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Keyboard :
    public core::DispatcherBaseArray <KeyboardCallbacks, KeyboardCallbackGroupT>::type,
    public core::NonCopyable
  {
  public:

  private:
    bool m_altPressed,
         m_shiftPressed,
         m_ctrlPressed,
         m_systemPressed;
  };

};};

#endif