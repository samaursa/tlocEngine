#pragma once
#ifndef _TLOC_INPUT_HID_JOYSTICK_H_
#define _TLOC_INPUT_HID_JOYSTICK_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/dispatch/tlocTemplateDispatchDefaults.h>
#include <tlocCore/dispatch/tlocEvent.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocInput/hid/tlocJoystickImpl.h>

namespace tloc { namespace input { namespace hid {

  template <typename T_Policy, typename T_Platform>   class Joystick_T;

  namespace priv {

    struct JoystickCallbacks
    {
    public:
      typedef core_dispatch::Event                    event_type;

    public:
      virtual event_type 
        OnButtonPress(const tl_size a_caller, 
                      const JoystickEvent& a_event, 
                      tl_int a_buttonIndex) const = 0; 

      virtual event_type 
        OnButtonRelease(const tl_size a_caller, 
                        const JoystickEvent& a_event, 
                        tl_int a_buttonIndex) const = 0; 
      
      virtual event_type 
        OnAxisChange(const tl_size a_caller, 
                     const JoystickEvent& a_event, 
                     tl_int a_axisIndex, 
                     JoystickEvent::axis_type a_axis) const = 0;

      virtual event_type 
        OnSliderChange(const tl_size a_caller, 
                       const JoystickEvent& a_event, 
                       tl_int a_sliderIndex, 
                       JoystickEvent::slider_type a_slider) const = 0;

      virtual event_type
        OnPOVChange(const tl_size a_caller, 
                    const JoystickEvent& a_event, 
                    tl_int a_povIndex, 
                    JoystickEvent::pov_type a_pov) const = 0;
    };

    template <typename T>
    class JoystickCallbackGroup_T
      : public core_dispatch::CallbackGroupTArray<T, JoystickCallbacks>::type
    {
    public:
      typedef typename core_dispatch::
        CallbackGroupTArray<T, JoystickCallbacks>::type         base_type;

      typedef typename base_type::event_type                    event_type;

      using base_type::m_observers;

    public:
      virtual event_type
        OnButtonPress(const tl_size a_caller, 
                      const JoystickEvent& a_event, 
                      tl_int a_buttonIndex) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnButtonPress
                (a_caller, a_event, a_buttonIndex).IsVeto())
          { 
            return core_dispatch::f_event::Veto();
          }
        }

        return core_dispatch::f_event::Continue();
      }

      virtual event_type
        OnButtonRelease(const tl_size a_caller, 
                        const JoystickEvent& a_event, 
                        tl_int a_buttonIndex) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnButtonRelease
                (a_caller, a_event, a_buttonIndex).IsVeto())
          { 
            return core_dispatch::f_event::Veto();
          }
        }

        return core_dispatch::f_event::Continue();
      }

      virtual event_type 
        OnAxisChange(const tl_size a_caller, 
                     const JoystickEvent& a_event, 
                     tl_int a_axisIndex, 
                     JoystickEvent::axis_type a_axis) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnAxisChange
                (a_caller, a_event, a_axisIndex, a_axis).IsVeto())
          {
            return core_dispatch::f_event::Veto();
          }
        }

        return core_dispatch::f_event::Continue();
      }

      virtual event_type
        OnSliderChange(const tl_size a_caller, 
                       const JoystickEvent& a_event, 
                       tl_int a_sliderIndex, 
                       JoystickEvent::slider_type a_slider) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnSliderChange
                (a_caller, a_event, a_sliderIndex, a_slider).IsVeto())
          {
            return core_dispatch::f_event::Veto();
          }
        }

        return core_dispatch::f_event::Continue();
      }

      virtual event_type 
        OnPOVChange(const tl_size a_caller, 
                    const JoystickEvent& a_event, 
                    tl_int a_povIndex, 
                    JoystickEvent::pov_type a_pov) const
      {
        for (u32 i = 0; i < m_observers.size(); ++i)
        {
          if (m_observers[i]->OnPOVChange
                (a_caller, a_event, a_povIndex, a_pov).IsVeto())
          {
            return core_dispatch::f_event::Veto();
          }
        }

        return core_dispatch::f_event::Continue();
      }
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Joystick_T<>

  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core_plat::PlatformInfo::platform_type>
  class Joystick_T
    : public core_dispatch::DispatcherBaseArray
        <priv::JoystickCallbacks, priv::JoystickCallbackGroup_T>::type
    , public core_bclass::NonCopyable_I
    , public p_hid::Joystick
  {
  public:
    typedef T_Platform                              platform_type;
    typedef T_Policy                                policy_type;
    typedef JoystickEvent                           joystick_event_type;
    typedef joystick_event_type::state_code_type    button_code_type;

    typedef core_dispatch::Event                    event_type;

    typedef Joystick_T<policy_type, platform_type>    this_type;

  public:
    template <typename T_ParamList>
    Joystick_T(const T_ParamList& a_paramList);
    ~Joystick_T();

    const joystick_event_type& GetCurrState() const;

    event_type 
      SendButtonPress(const joystick_event_type& a_event, 
                      tl_int a_buttonIndex) const;
    event_type 
      SendButtonRelease(const joystick_event_type& a_event, 
                        tl_int a_buttonIndex) const;
    event_type 
      SendAxisChange(const joystick_event_type& a_event, 
                     tl_int a_axisIndex, 
                     joystick_event_type::axis_type a_axis) const;
    event_type 
      SendSliderChange(const joystick_event_type& a_event, 
                       tl_int a_sliderIndex, 
                       joystick_event_type::slider_type a_slider) const;
    event_type 
      SendPOVChange(const joystick_event_type& a_event, 
                    tl_int a_povIndex, 
                    joystick_event_type::pov_type a_pov) const;

    void Update();
    void Reset();
    
  private:

    typedef priv::JoystickImpl_T<this_type>           impl_type;
    typedef core_sptr::UniquePtr<impl_type>           impl_ptr_type;

    impl_ptr_type   m_impl;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Joystick_T<InputPolicy::Buffered>           JoystickB;
  typedef Joystick_T<InputPolicy::Immediate>          JoystickI;

  TLOC_TYPEDEF_ALL_SMART_PTRS(JoystickB, joystick_b);
  TLOC_TYPEDEF_ALL_SMART_PTRS(JoystickI, joystick_i);

};};};

#endif