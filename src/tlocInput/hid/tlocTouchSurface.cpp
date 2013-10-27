#include "tlocTouchSurface.h"

#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_OS_WIN)
# include <tlocInput/hid/tlocTouchSurfaceImplWin.h>
#elif defined(TLOC_OS_IPHONE)
# include <tlocInput/hid/tlocTouchSurfaceImplIphone.h>
#else
# error "WIP"
#endif

namespace tloc { namespace input { namespace hid {

#define TOUCH_SURFACE_TEMP    typename T_Policy, typename T_Platform
#define TOUCH_SURFACE_PARAMS  T_Policy, T_Platform
#define TOUCH_SURFACE_TYPE    typename TouchSurface<TOUCH_SURFACE_PARAMS>

  //------------------------------------------------------------------------
  // Method definitions

  template <TOUCH_SURFACE_TEMP>
  template <typename T_ParamList>
  TouchSurface<TOUCH_SURFACE_PARAMS>::TouchSurface(const T_ParamList& a_paramList)
  {
    m_impl.reset( new impl_type(this, a_paramList) );
  }

  template <TOUCH_SURFACE_TEMP>
  TouchSurface<TOUCH_SURFACE_PARAMS>::~TouchSurface()
  { }

  template <TOUCH_SURFACE_TEMP>
  const TOUCH_SURFACE_TYPE::touch_container_type&
  TouchSurface<TOUCH_SURFACE_PARAMS>::GetCurrentTouches() const
  {
    return m_impl->GetCurrentTouches();
  }

  template <TOUCH_SURFACE_TEMP>
  const TOUCH_SURFACE_TYPE::touch_type*
    TouchSurface<TOUCH_SURFACE_PARAMS>::GetTouch(touch_handle_type a_touch) const
  {
    return m_impl->GetTouch(a_touch);
  }

  template <TOUCH_SURFACE_TEMP>
  bool TouchSurface<TOUCH_SURFACE_PARAMS>::
    IsTouchDown(touch_handle_type a_touch) const
  {
    return m_impl->IsTouchDown(a_touch);
  }

  template <TOUCH_SURFACE_TEMP>
  void TouchSurface<TOUCH_SURFACE_PARAMS>::
    SendOnTouchPress(const touch_type &a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnTouchPress( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <TOUCH_SURFACE_TEMP>
  void TouchSurface<TOUCH_SURFACE_PARAMS>::
    SendOnTouchRelease(const touch_type &a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnTouchRelease( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <TOUCH_SURFACE_TEMP>
  void TouchSurface<TOUCH_SURFACE_PARAMS>::
    SendOnTouchMove(const touch_type &a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnTouchMove( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <TOUCH_SURFACE_TEMP>
  void TouchSurface<TOUCH_SURFACE_PARAMS>::Update()
  {
    m_impl->Update();
  }

  template <TOUCH_SURFACE_TEMP>
  void TouchSurface<TOUCH_SURFACE_PARAMS>::Reset()
  {
    m_impl->Reset();
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template class TouchSurface<InputPolicy::Buffered>;
  template class TouchSurface<InputPolicy::Immediate>;

  //------------------------------------------------------------------------
  // Force instantiation for constructors

#if defined(TLOC_OS_WIN)
  template TouchSurface<InputPolicy::Buffered>
    ::TouchSurface(const win_touch_surface_param_type&);
  template TouchSurface<InputPolicy::Immediate>
    ::TouchSurface(const win_touch_surface_param_type&);
#elif defined(TLOC_OS_IPHONE)
  template TouchSurface<InputPolicy::Buffered>
    ::TouchSurface(const iphone_touch_surface_param_type&);
  template TouchSurface<InputPolicy::Immediate>
    ::TouchSurface(const iphone_touch_surface_param_type&);
#else
# error TODO
#endif

};};};