#include "tlocMouse.h"

#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>
#include <tlocCore/utilities/tlocPointerUtils.h>
#include <tlocMath/tlocRange.inl.h>

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include <tlocInput/hid/tlocMouseImplWin.h>
#elif defined (TLOC_OS_IPHONE)
# include <tlocInput/hid/tlocMouseImplIphone.h>
#else
# error "WIP"
#endif

namespace tloc { namespace input { namespace hid {

#define MOUSE_TEMP   typename T_Policy, typename T_Platform
#define MOUSE_PARAMS T_Policy, T_Platform
#define MOUSE_TYPE   typename Mouse<MOUSE_PARAMS>


  //------------------------------------------------------------------------
  // Method definitions

  template <MOUSE_TEMP>
  template <typename T_ParamList>
  Mouse<MOUSE_PARAMS>::Mouse(const T_ParamList& a_paramList)
    : m_clamped(true)
  {
    m_impl.reset(new impl_type(*this, a_paramList));
  }

  template <MOUSE_TEMP>
  Mouse<MOUSE_PARAMS>::~Mouse()
  { }

  template <MOUSE_TEMP>
  bool Mouse<MOUSE_PARAMS>::IsButtonDown(button_code_type a_button) const
  {
    return m_impl->IsButtonDown(a_button);
  }

  template <MOUSE_TEMP>
  MouseEvent Mouse<MOUSE_PARAMS>::GetState() const
  {
    return m_impl->GetState();
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::
    SendOnButtonPress(const MouseEvent& a_event,
                      button_code_type a_buttonCode) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnButtonPress(core_utils::GetMemoryAddress(this),
                                           a_event, a_buttonCode) == true)
      {
        break;
      }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::
    SendOnButtonRelease(const MouseEvent& a_event,
                        button_code_type a_buttonCode) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnButtonRelease(core_utils::GetMemoryAddress(this),
                                             a_event, a_buttonCode) == true)
      {
        break;
      }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::
    SendOnMouseMove(const MouseEvent& a_event) const
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnMouseMove(core_utils::GetMemoryAddress(this),
                                         a_event) == true)
      { break; }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::
    Clamp(event_type& a_event) const
  {
    // TODO: Replace with Clamp<>() method when available
    a_event.m_X.m_abs() =
      core::Clamp(a_event.m_X.m_abs(),
                  GetClampX().front(),
                  GetClampX().back());

    a_event.m_Y.m_abs() =
      core::Clamp(a_event.m_Y.m_abs(),
                  GetClampY().front(),
                  GetClampY().back());
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::Update()
  {
    m_impl->Update();
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::Reset()
  {
    m_impl->Reset();
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::SetClampX(const abs_range_type& a_range)
  {
    m_clampX = a_range;
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::SetClampY(const abs_range_type& a_range)
  {
    m_clampY = a_range;
  }

  //------------------------------------------------------------------------
  // Forward Instantiations

  template class Mouse<InputPolicy::Buffered>;
  template class Mouse<InputPolicy::Immediate>;

  //------------------------------------------------------------------------
  // Force instantiate the constructor for each platform

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
  template Mouse<InputPolicy::Buffered>::Mouse(const windows_mouse_param_type&);
  template Mouse<InputPolicy::Immediate>::Mouse(const windows_mouse_param_type&);
#elif defined (TLOC_OS_IPHONE)
  template Mouse<InputPolicy::Buffered>::Mouse(const iphone_mouse_param_type&);
  template Mouse<InputPolicy::Immediate>::Mouse(const iphone_mouse_param_type&);
#else
# error TODO
#endif

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::input_hid;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MouseB);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MouseI);