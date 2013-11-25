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
    m_impl.reset(new impl_type(this, a_paramList));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  Joystick_T<JOYSTICK_PARAMS>::~Joystick_T()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  bool
    Joystick_T<JOYSTICK_PARAMS>::
    IsButtonDown(button_code_type a_key) const
  {
    return m_impl->IsButtonDown(a_key);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    SendButtonPress(const joystick_event_type& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnButtonPress( core_utils::GetMemoryAddress(this), a_event) == true)
      { return; }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    SendButtonRelease(const joystick_event_type& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnButtonRelease( core_utils::GetMemoryAddress(this), a_event) == true)
      { return; }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    SendPosAxisChange(const joystick_event_type& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnPosAxisChange( core_utils::GetMemoryAddress(this), a_event) == true)
      { return; }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    SendRotAxisChange(const joystick_event_type& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnRotAxisChange( core_utils::GetMemoryAddress(this), a_event) == true)
      { return; }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_TEMP>
  void
    Joystick_T<JOYSTICK_PARAMS>::
    SendPOVChange(const joystick_event_type& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->
          OnPOVChange( core_utils::GetMemoryAddress(this), a_event) == true)
      { return; }
    }
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

};};};