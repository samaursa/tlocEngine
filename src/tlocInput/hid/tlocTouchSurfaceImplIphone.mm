#include "tlocTouchSurfaceImplIphone.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tloccore/tlocAlgorithms.inl.h>

#import <tlocGraphics/window/tlocOpenGLViewIphone.h>

namespace tloc { namespace input { namespace hid { namespace priv {
  
#define TOUCH_SURFACE_IMPL_TEMP     typename T_ParentTouchSurface
#define TOUCH_SURFACE_IMPL_PARAMS   T_ParentTouchSurface
#define TOUCH_SURFACE_IMPL_TYPE     typename TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Free functions and definitions

  namespace {
    typedef OpenGLView*  view_internal_type;

    view_internal_type DoExtractView(const core_t::Any& a_any)
    {
      return a_any.Cast<view_internal_type>();
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // TouchSurfaceImpl
  
  template <TOUCH_SURFACE_IMPL_TEMP>
  TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    TouchSurfaceImpl(parent_type* a_parent,
    const touch_surface_param_type& a_params)
    : base_type(*a_parent, a_params)
  {
    view_handle_type view = DoGetViewHandle();
    TLOC_ASSERT_NOT_NULL(DoExtractView(view));

    DoInitialize(view, policy_type());
  }
  
  template <TOUCH_SURFACE_IMPL_TEMP>
  TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::~TouchSurfaceImpl()
  {
    view_handle_type view = DoGetViewHandle();
    TLOC_ASSERT_NOT_NULL(DoExtractView(view));

    DoDestroy(view, policy_type());
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  const TOUCH_SURFACE_IMPL_TYPE::touch_type*
    TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    GetTouch(touch_handle_type a_touch) const
  {
    return m_touchDevice.GetTouch(a_touch);
  }
  
  template <TOUCH_SURFACE_IMPL_TEMP>
  bool TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    IsTouchDown(touch_handle_type a_touch) const
  {
    return (m_touchDevice.GetTouch(a_touch) != NULL);
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::Update()
  {
    if (m_currentTouches.size() != m_touchDevice.GetCurrentTouches().size())
    {
      m_currentTouches.resize(m_touchDevice.GetCurrentTouches().size());
    }

    DoUpdate(policy_type());
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::Reset()
  {
    base_type::Reset();
    m_touchDevice.Reset();
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoInitialize(view_handle_type a_view, InputPolicy::Buffered)
  {
    [DoExtractView(a_view) RegisterTouchSurfaceDeviceBuffered:&m_touchDevice];
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoInitialize(view_handle_type a_view, InputPolicy::Immediate)
  {
    [DoExtractView(a_view) RegisterTouchSurfaceDeviceImmediate:&m_touchDevice];
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoDestroy(view_handle_type a_view, InputPolicy::Buffered)
  {
    [DoExtractView(a_view) UnRegisterTouchSurfaceDeviceBuffered:&m_touchDevice];
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoDestroy(view_handle_type a_view, InputPolicy::Immediate)
  {
    [DoExtractView(a_view) UnRegisterTouchSurfaceDeviceImmediate:&m_touchDevice];
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  typename TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::view_handle_type
    TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::DoGetViewHandle()
  {
    return m_params.m_param1;
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoUpdate(InputPolicy::Buffered)
  {
    core::copy(m_touchDevice.GetCurrentTouches().begin(),
               m_touchDevice.GetCurrentTouches().end(),
               m_currentTouches.begin());

    typename touch_device_type::buffer_container_type::const_iterator itr =
      m_touchDevice.GetBufferedTouches().begin();
    const typename touch_device_type::buffer_container_type::const_iterator itrEnd =
      m_touchDevice.GetBufferedTouches().end();

    while (itr != itrEnd)
    {
      switch ((*itr).m_currentState)
      {
        case TouchSurfaceBufferedElement::begin:
        {
          m_parent.SendOnTouchPress((*itr).m_event);
          break;
        }
        case TouchSurfaceBufferedElement::end:
        {
          m_parent.SendOnTouchRelease((*itr).m_event);
          break;
        }
        case TouchSurfaceBufferedElement::move:
        {
          m_parent.SendOnTouchMove((*itr).m_event);
          break;
        }

        default: break;
      }
      ++itr;
    }

    // We need to reset the touch device's buffer to prevent touches from
    // accumulating
    m_touchDevice.Reset();
  }

  template <TOUCH_SURFACE_IMPL_TEMP>
  void TouchSurfaceImpl<TOUCH_SURFACE_IMPL_PARAMS>::
    DoUpdate(InputPolicy::Immediate)
  {
    core::copy(m_touchDevice.GetCurrentTouches().begin(),
               m_touchDevice.GetCurrentTouches().end(),
               m_currentTouches.begin());
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit Instantiations
  template class TouchSurfaceImpl< TouchSurface<InputPolicy::Buffered> >;
  template class TouchSurfaceImpl< TouchSurface<InputPolicy::Immediate> >;
  
};};};};
