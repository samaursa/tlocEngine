#ifndef TLOC_KEYBOARD_H
#define TLOC_KEYBOARD_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocPlatform.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTemplateDispatchDefaults.h"

namespace tloc { namespace input {

  ///-------------------------------------------------------------------------
  /// Keyboard implementation that must be specialized for each platform
  ///-------------------------------------------------------------------------
  template <class T_ParentWindow> class KeyboardImpl;

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

  ///-------------------------------------------------------------------------
  /// This class itself is for internal use only.
  ///
  /// If a class is registered with Keyboard to receive callbacks, this class
  /// defines the function signature of the callbacks (Note that the callbacks
  /// in your class need not be virtual)
  ///-------------------------------------------------------------------------
  struct KeyboardCallbacks
  {
    virtual void OnKeyPress(const KeyboardEvent& a_event) = 0;
    virtual void OnKeyRelease(const KeyboardEvent& a_event) = 0;
  };

  ///-------------------------------------------------------------------------
  /// This class is for internal use only
  ///
  /// @sa core::CallbackGroupTArray<T, KeyboardCallbacks>::type
  ///-------------------------------------------------------------------------
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

  namespace KeyboardPolicy
  {
    struct Buffered{};
    struct UnBuffered{};
  };

  ///-------------------------------------------------------------------------
  /// Platform independent list of parameters. Note that all parameters must
  /// be pointers which will be dereferenced by the platform implementations.
  ///
  /// Incorrect parameter types will result in linking errors.
  ///-------------------------------------------------------------------------
  template <typename T_WindowPtr>
  struct KeyboardParamList
  {
    T_WindowPtr m_windowPtr;
  };

  ///-------------------------------------------------------------------------
  /// Cross-platform class to handle keyboard input.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = KeyboardPolicy::Buffered(),
            typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Keyboard :
    public core::DispatcherBaseArray <KeyboardCallbacks, KeyboardCallbackGroupT>::type,
    public core::NonCopyable
  {
  public:
    typedef KeyboardEvent::key_code_type    keycode_type;
    typedef u32                             index_type;
    typedef T_Platform                      platform_type;
    typedef Keyboard<T_Policy, T_Platform>  this_type;

    template <typename T_ParamList>
    Keyboard(const T_ParamList& a_paramList);
    ~Keyboard();

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
    enum {pressed_alt = 0, pressed_shift, pressed_ctrl, pressed_system,
          pressed_count};

    u32 m_buffer[KeyboardEvent::Count];
    bool m_altPressed,
         m_shiftPressed,
         m_ctrlPressed,
         m_systemPressed;
  };

};};

#endif