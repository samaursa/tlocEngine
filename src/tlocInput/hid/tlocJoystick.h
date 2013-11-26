#ifndef _TLOC_INPUT_HID_KEYBOARD_H_
#define _TLOC_INPUT_HID_KEYBOARD_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include <tlocInput/tlocInputManager.h>
#include <tlocInput/hid/tlocJoystickImpl.h>

namespace tloc { namespace input { namespace hid {

  template <typename T_Policy, typename T_Platform>   class Keyboard;

  namespace priv {

    struct JoystickCallbacks
    {
      virtual bool OnButtonPress(const tl_size a_caller,
                                 const JoystickEvent& a_event) const = 0;
      virtual bool OnButtonRelease(const tl_size a_caller,
                                   const JoystickEvent& a_event) const = 0;
      virtual bool OnPosAxisChange(const tl_size a_caller,
                                   const JoystickEvent& a_event) const = 0;
      virtual bool OnRotAxisChange(const tl_size a_caller,
                                   const JoystickEvent& a_event) const = 0;
      virtual bool OnPOVChange(const tl_size a_caller,
                               const JoystickEvent& a_event) const = 0;
    };

    template <typename T>
    class JoystickCallbackGroup_T
      : public core_bclass::CallbackGroupTArray<T, JoystickCallbacks>::type
    {
    public:
      typedef typename core_bclass::
        CallbackGroupTArray<T, JoystickCallbacks>::type         base_type;

      using base_type::m_observers;

    public:
      virtual bool OnButtonPress(const tl_size a_caller,
                                 const JoystickEvent& a_event) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnButtonPress(a_caller, a_event) == true)
          { return true; }
        }
        return false;
      }

      virtual bool OnButtonRelease(const tl_size a_caller,
                                   const JoystickEvent& a_event) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnButtonRelease(a_caller, a_event) == true)
          { return true; }
        }
        return false;
      }

      virtual bool OnPosAxisChange(const tl_size a_caller,
                                   const JoystickEvent& a_event) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnPosAxisChange(a_caller, a_event) == true)
          { return true; }
        }
        return false;
      }

      virtual bool OnRotAxisChange(const tl_size a_caller,
                                   const JoystickEvent& a_event) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnRotAxisChange(a_caller, a_event) == true)
          { return true; }
        }
        return false;
      }

      virtual bool OnPOVChange(const tl_size a_caller,
                               const JoystickEvent& a_event) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnPOVChange(a_caller, a_event) == true)
          { return true; }
        }
        return false;
      }
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Joystick_T<>

  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core_plat::PlatformInfo::platform_type>
  class Joystick_T
    : public core_bclass::DispatcherBaseArray
        <priv::JoystickCallbacks, priv::JoystickCallbackGroup_T>::type
    , public core_bclass::NonCopyable_I
    , public p_hid::Keyboard
  {
  public:
    typedef T_Platform                              platform_type;
    typedef T_Policy                                policy_type;
    typedef JoystickEvent                           joystick_event_type;
    typedef joystick_event_type::state_code_type   button_code_type;
    typedef joystick_event_type::pos2_type          pos2_type;
    typedef joystick_event_type::pos3_type          pos3_type;
    typedef joystick_event_type::rot3_type          rot3_type;

    typedef Joystick_T<policy_type, platform_type>    this_type;

  public:
    template <typename T_ParamList>
    Joystick_T(const T_ParamList& a_paramList);
    ~Joystick_T();

    bool IsButtonDown(button_code_type a_key) const;

    void SendButtonPress(const joystick_event_type& a_event) const;
    void SendButtonRelease(const joystick_event_type& a_event) const;
    void SendPosAxisChange(const joystick_event_type& a_event) const;
    void SendRotAxisChange(const joystick_event_type& a_event) const;
    void SendPOVChange(const joystick_event_type& a_event) const;

    void Update();
    void Reset();

  private:

    typedef priv::JoystickImpl_T<this_type>           impl_type;
    typedef core_sptr::UniquePtr<impl_type>           impl_ptr_type;

    impl_ptr_type   m_impl;
  };

  typedef Joystick_T<InputPolicy::Buffered>           JoystickB;
  typedef Joystick_T<InputPolicy::Immediate>          JoystickI;

};};};

#endif