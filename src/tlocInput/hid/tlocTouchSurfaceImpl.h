//
//  tlocTouchImplSurface.h
//  tlocInput
//
//  Created by Skopworks Inc on 12-08-25.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TLOC_TOUCH_SURFACE_IMPL_H
#define TLOC_TOUCH_SURFACE_IMPL_H

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>

#include <tlocInput/tlocInputTypes.h>

namespace tloc { namespace input {

  struct TouchSurfaceEvent
  {
    typedef tl_uintptr              touch_handle_type;
    typedef Component::AxisAbsf     axis_type;
    typedef axis_type::value_type   axis_value_type;

    TouchSurfaceEvent(touch_handle_type a_touchHandle = 0)
      : m_touchHandle(a_touchHandle) {}

    TouchSurfaceEvent(touch_handle_type a_touchHandle,
                      axis_type::value_type a_x,
                      axis_type::value_type a_y)
    : m_touchHandle(a_touchHandle), m_X(a_x), m_Y(a_y) {}

    touch_handle_type m_touchHandle;

    axis_type m_X, m_Y;
  };

};};

namespace tloc { namespace input { namespace priv {

  template <class T_ParentTouchSurface> class TouchSurfaceImpl;

  template <class T_ParentTouchSurface, class T_ParamList>
  class TouchSurfaceImplBase
    : public core::base_classes::ImplBase<T_ParentTouchSurface>
  {
  public:
    typedef core::base_classes::ImplBase<T_ParentTouchSurface>  base_type;
    typedef typename base_type::parent_type                     parent_type;

    typedef T_ParamList                                 param_list_type;
    typedef typename parent_type::platform_type         platform_type;
    typedef typename parent_type::touch_type            touch_type;
    typedef typename parent_type::touch_handle_type     touch_handle_type;
    typedef typename parent_type::touch_container_type  touch_container_type;
    typedef typename parent_type::size_type             size_type;

    TouchSurfaceImplBase(parent_type* a_parent, param_list_type a_params)
      : base_type(a_parent), m_params(a_params)
    {
    }

    const param_list_type& GetParams() const
    {
      return m_params;
    }

    const touch_container_type& GetCurrentTouches() const
    {
      return m_currentTouches;
    }

    void Reset()
    {
      m_currentTouches.clear();
    }

  protected:

    param_list_type       m_params;
    touch_container_type  m_currentTouches;
  };

};};};

#endif
