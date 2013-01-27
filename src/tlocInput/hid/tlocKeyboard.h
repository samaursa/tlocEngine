#ifndef TLOC_KEYBOARD_H
#define TLOC_KEYBOARD_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include <tlocInput/tlocInputManager.h>
#include <tlocInput/hid/tlocKeyboardImpl.h>

namespace tloc { namespace input { namespace hid {

  template <typename T_Policy, typename T_Platform> class Keyboard;

  ///-------------------------------------------------------------------------
  /// This class itself is for internal use only.
  ///
  /// If a class is registered with Keyboard to receive callbacks, this class
  /// defines the function signature of the callbacks (Note that the callbacks
  /// in your class need not be virtual)
  ///-------------------------------------------------------------------------
  struct KeyboardCallbacks
  {
    virtual bool OnKeyPress(const tl_size a_caller,
                            const KeyboardEvent& a_event) = 0;
    virtual bool OnKeyRelease(const tl_size a_caller,
                              const KeyboardEvent& a_event) = 0;
  };

  ///-------------------------------------------------------------------------
  /// This class is for internal use only
  ///
  /// @sa core::CallbackGroupTArray<T, KeyboardCallbacks>::type
  ///-------------------------------------------------------------------------
  template <typename T>
  struct KeyboardCallbackGroupT:
    public core::base_classes::CallbackGroupTArray<T, KeyboardCallbacks >::type
  {
  public:
    typedef typename core::base_classes::
      CallbackGroupTArray<T, KeyboardCallbacks>::type     base_type;

    using base_type::m_observers;

  public:
    virtual bool OnKeyPress(const tl_size a_caller,
                            const KeyboardEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnKeyPress(a_caller, a_event) == true)
        {
          return true;
        }
      }
      return false;
    }

    virtual bool OnKeyRelease(const tl_size a_caller,
                              const KeyboardEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnKeyRelease(a_caller, a_event) == true)
        {
          return true;
        }
      }
      return false;
    }
  };

  ///-------------------------------------------------------------------------
  /// Cross-platform class to handle keyboard input.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Keyboard
    : public core::base_classes::DispatcherBaseArray
      <KeyboardCallbacks, KeyboardCallbackGroupT>::type
    , public core::NonCopyable
    , public p_hid::Keyboard
  {
  public:
    typedef T_Platform                      platform_type;
    typedef T_Policy                        policy_type;
    typedef KeyboardEvent::key_code_type    keycode_type;
    typedef KeyboardEvent::Modifier         modifier_type;

    typedef Keyboard<policy_type, platform_type>  this_type;

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

    bool IsModifierDown(modifier_type a_mod) const;

    void SendOnKeyPress(const KeyboardEvent& a_event);
    void SendOnKeyRelease(const KeyboardEvent& a_event);

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();

  private:

    typedef priv::KeyboardImpl<this_type>               impl_type;
    typedef core::smart_ptr::UniquePtr<impl_type>       impl_ptr_type;

    impl_ptr_type m_impl;
  };

  typedef Keyboard<InputPolicy::Buffered>   KeyboardB;
  typedef Keyboard<InputPolicy::Immediate>  KeyboardI;

};};};

#endif