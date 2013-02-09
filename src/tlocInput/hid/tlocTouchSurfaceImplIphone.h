//
//  tlocTouchSurfaceImplIphone.h
//  tlocInput
//
//  Created by Skopworks Inc on 12-08-31.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TLOC_TOUCH_SURFACE_IMPL_IPHONE_H
#define TLOC_TOUCH_SURFACE_IMPL_IPHONE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTemplateParams.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocTouchSurface.h>
#include <tlocInput/hid/tlocTouchSurfaceImpl.h>

#import "tlocGraphics/window/tlocOpenGLViewIphone.h"

namespace tloc { namespace input {
  
  typedef ParamList<OpenGLView*> iphone_touch_surface_param_type;
  
};};

namespace tloc { namespace input { namespace hid { namespace priv {
  
  template <typename T_ParentTouchSurface>
  class TouchSurfaceImpl 
    : public TouchSurfaceImplBase<T_ParentTouchSurface, iphone_touch_surface_param_type>
  {
  public:
    typedef iphone_touch_surface_param_type           touch_surface_param_type;
    typedef touch_surface_param_type::param_type_1    view_handle_type;
    
    typedef T_ParentTouchSurface                      parent_type;
    typedef TouchSurfaceImpl<parent_type>             this_type;
    typedef TouchSurfaceImplBase
      <parent_type, touch_surface_param_type>         base_type;
    
    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename base_type::touch_type            touch_type;
    typedef typename base_type::touch_handle_type     touch_handle_type;
    typedef typename base_type::touch_container_type  touch_container_type;
    typedef typename base_type::size_type             size_type;

    // TODO: Make the device take in policy types to avoid this
    typedef typename Loki::Int2Type
      <Loki::IsSameType<policy_type,
      InputPolicy::Buffered>::value>                  policy_result_type;

    typedef typename Loki::Select
      <policy_result_type::value,
      TouchSurfaceDeviceBuffered,
      TouchSurfaceDeviceImmediate>::Result            touch_device_type;

    using base_type::m_parent;
    using base_type::m_params;
    using base_type::m_currentTouches;

    TouchSurfaceImpl(parent_type* a_parent, 
                     const touch_surface_param_type& a_params);
    ~TouchSurfaceImpl();

    const touch_type* GetTouch(touch_handle_type a_touch) const;
    bool IsTouchDown(touch_handle_type a_touch) const;
    
    void Update();

    void Reset();
    
  private:

    void DoInitialize(view_handle_type a_view, InputPolicy::Buffered);
    void DoInitialize(view_handle_type a_view, InputPolicy::Immediate);

    void DoDestroy(view_handle_type a_view, InputPolicy::Buffered);
    void DoDestroy(view_handle_type a_view, InputPolicy::Immediate);

    void DoUpdate(InputPolicy::Buffered);
    void DoUpdate(InputPolicy::Immediate);

    view_handle_type DoGetViewHandle();
    
    static const size_type s_maxTouches = 11;

    touch_device_type m_touchDevice;
  };
  
};};};};

#endif