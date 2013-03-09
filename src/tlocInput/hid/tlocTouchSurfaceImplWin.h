#ifndef _TLOC_INPUT_HID_PRIV_TOUCH_SURFACE_IMPL_WIN_H_
#define _TLOC_INPUT_HID_PRIV_TOUCH_SURFACE_IMPL_WIN_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/hid/tlocTouchSurfaceImpl.h>

namespace tloc { namespace input {

  typedef ParamList<> win_touch_surface_param_type;

};};

namespace tloc { namespace input { namespace hid { namespace priv {

  template <typename T_ParentTouchSurface>
  class TouchSurfaceImpl
    : public TouchSurfaceImplBase<T_ParentTouchSurface, win_touch_surface_param_type>
  {
  public:
    typedef win_touch_surface_param_type              touch_surface_param_type;

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

    TouchSurfaceImpl
      (parent_type* a_parent, const touch_surface_param_type& a_params)
      : base_type(a_parent, a_params) {}
    ~TouchSurfaceImpl() {}

    const touch_type* GetTouch(touch_handle_type a_touch) const
    {
      TLOC_UNUSED(a_touch);
      return NULL;
    }

    bool IsTouchDown(touch_handle_type a_touch) const
    {
      TLOC_UNUSED(a_touch);
      return false;
    }

    void Update() {}
    void Reset() {}


  };

};};};};

#endif