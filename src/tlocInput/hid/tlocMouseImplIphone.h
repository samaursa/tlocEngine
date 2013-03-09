#pragma once
#ifndef _TLOC_INPUT_HID_PRIV_MOUSE_IMPL_IPHONE_H_
#define _TLOC_INPUT_HID_PRIV_MOUSE_IMPL_IPHONE_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/hid/tlocMouseImpl.h>

namespace tloc { namespace input {

  typedef ParamList<> iphone_mouse_param_type;

};};

namespace tloc { namespace input { namespace hid { namespace priv {

  template <typename T_ParentMouse>
  class MouseImpl
    : public MouseImplBase<T_ParentMouse, iphone_mouse_param_type>
  {
  public:
    typedef iphone_mouse_param_type     mouse_param_type;
    typedef T_ParentMouse               parent_type;
    typedef MouseImpl<parent_type>      this_type;
    typedef MouseImplBase
      <parent_type, mouse_param_type>   base_type;

    typedef typename parent_type::platform_type   platform_type;
    typedef typename parent_type::policy_type     policy_type;
    typedef typename base_type::button_code_type  button_code_type;

  public:
    MouseImpl(parent_type* a_parent, const mouse_param_type& a_params)
      : base_type(a_parent, a_params) {}

    ~MouseImpl() {}

    bool IsButtonDown(button_code_type) const { return false; }
    MouseEvent GetState() const { return m_currentState; }

    void Update() {}
    void Reset() {}

  private:
    MouseEvent  m_currentState;
  };

};};};};

#endif
