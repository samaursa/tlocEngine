#include "tlocJoystick.h"

#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

// -----------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_OS_WIN)
# include <tlocInput/hid/tlocJoystickImplWin.h>
#elif defined (TLOC_OS_IPHONE)
# include <tlocInput/hid/tlocJoystickImplIphone.h>
#else
# error "WIP"
#endif

namespace tloc { namespace input { namespace hid {

  // ///////////////////////////////////////////////////////////////////////
  // Joystick_T<>

#define JOYSTICK_TEMP   typename T_Policy, typename T_Platform
#define JOYSTICK_PARAMS T_Policy, T_Platform
#define JOYSTICK_TYPE   typename Joystick_T<JOYSTICK_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  template <typename T_ParamList>
  Joystick_T<JOYSTICK_PARAMS>::
    Joystick_T(const T_ParamList& a_paramList)
  {
    m_impl = core_sptr::MakeUnique<impl_type>(*this, a_paramList);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  Joystick_T<JOYSTICK_PARAMS>::~Joystick_T()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  const JOYSTICK_TYPE::joystick_event_type&
    Joystick_T<JOYSTICK_PARAMS>::
    GetCurrState() const
  {
    return m_impl->GetCurrState();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  JOYSTICK_TYPE::event_type
    Joystick_T<JOYSTICK_PARAMS>::
    SendJoystickButtonPress(const joystick_event_type& a_event,
                    tl_int a_buttonIndex) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnJoystickButtonPress(core_utils::GetMemoryAddress(this), a_event,
                                a_buttonIndex).IsVeto())
      { return core_dispatch::f_event::Veto(); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  JOYSTICK_TYPE::event_type
    Joystick_T<JOYSTICK_PARAMS>::
    SendJoystickButtonRelease(const joystick_event_type& a_event,
                              tl_int a_buttonIndex) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnJoystickButtonRelease(core_utils::GetMemoryAddress(this), a_event,
                                  a_buttonIndex).IsVeto())
      { return core_dispatch::f_event::Veto(); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  JOYSTICK_TYPE::event_type
    Joystick_T<JOYSTICK_PARAMS>::
    SendJoystickAxisChange(const joystick_event_type& a_event,
                           tl_int a_axisIndex, 
                           joystick_event_type::axis_type a_axis,
                           joystick_event_type::axis_type_norm a_axisNorm) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnJoystickAxisChange(core_utils::GetMemoryAddress(this), a_event,
                               a_axisIndex, a_axis, a_axisNorm).IsVeto())
      { return core_dispatch::f_event::Veto(); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  JOYSTICK_TYPE::event_type
    Joystick_T<JOYSTICK_PARAMS>::
    SendJoystickSliderChange(const joystick_event_type& a_event,
                             tl_int a_sliderIndex,
                             joystick_event_type::slider_type a_slider) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnJoystickSliderChange(core_utils::GetMemoryAddress(this), a_event,
                                 a_sliderIndex, a_slider).IsVeto())
      { return core_dispatch::f_event::Veto(); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  JOYSTICK_TYPE::event_type
    Joystick_T<JOYSTICK_PARAMS>::
    SendJoystickPOVChange(const joystick_event_type& a_event,
                          tl_int a_povIndex,
                          joystick_event_type::pov_type a_pov) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnJoystickPOVChange(core_utils::GetMemoryAddress(this), a_event,
                              a_povIndex, a_pov).IsVeto())
      { return core_dispatch::f_event::Veto(); }
    }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    Update()
  { m_impl->Update(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    Reset()
  { m_impl->Reset(); }

  // -----------------------------------------------------------------------
  // explicit instantiation for each platform

  template class Joystick_T<InputPolicy::Buffered>;
  template class Joystick_T<InputPolicy::Immediate>;

#if defined (TLOC_OS_WIN)
  template Joystick_T<InputPolicy::Buffered>::Joystick_T(const windows_joystick_param_type&);
  template Joystick_T<InputPolicy::Immediate>::Joystick_T(const windows_joystick_param_type&);
#elif defined (TLOC_OS_IPHONE)
  template Joystick_T<InputPolicy::Buffered>::Joystick_T(const iphone_joystick_param_type&);
  template Joystick_T<InputPolicy::Immediate>::Joystick_T(const iphone_joystick_param_type&);
#else
# error TODO
#endif

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::input_hid;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(JoystickB);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(JoystickI);