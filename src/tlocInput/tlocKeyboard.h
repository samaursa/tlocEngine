#ifndef TLOC_KEYBOARD_H
#define TLOC_KEYBOARD_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocPlatform.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTemplateDispatchDefaults.h"
#include "tlocCore/tlocTemplateUtils.h"

#include "tlocInput.h"
#include "tlocKeyboardImpl.h"

namespace tloc { namespace input {


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

  ///-------------------------------------------------------------------------
  /// Platform independent list of parameters. Passing incorrect parameters
  /// will result in compile errors.
  ///-------------------------------------------------------------------------
  template <class T1,
            class T2 = TLOC_DUMMY_PARAM(),
            class T3 = TLOC_DUMMY_PARAM(),
            class T4 = TLOC_DUMMY_PARAM()>
  struct KeyboardParamList
  {
    T1 m_param1;
    T2 m_param2;
    T3 m_param3;
    T4 m_param4;
  };

  ///-------------------------------------------------------------------------
  /// Cross-platform class to handle keyboard input.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Keyboard :
    public core::DispatcherBaseArray <KeyboardCallbacks, KeyboardCallbackGroupT>::type,
    public core::NonCopyable
  {
  public:
    typedef T_Platform                      platform_type;
    typedef Keyboard<T_Policy, T_Platform>  this_type;
    typedef KeyboardEvent::key_code_type    keycode_type;

    template <typename T_ParamList>
    Keyboard(T_ParamList a_paramList);
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

    typedef priv::KeyboardImpl<this_type> impl_type;
    impl_type*  m_impl;
  };

};};

#endif