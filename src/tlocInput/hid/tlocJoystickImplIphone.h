#pragma once
#ifndef _TLOC_INPUT_HID_PRIV_JOYSTICK_IMPL_IPHONE_H_
#define _TLOC_INPUT_HID_PRIV_JOYSTICK_IMPL_IPHONE_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/hid/tlocJoystick.h>
#include <tlocInput/hid/tlocJoystickImpl.h>

namespace tloc { namespace input {
  
  typedef ParamList<> iphone_joystick_param_type;
  
};};

namespace tloc { namespace input { namespace hid { namespace priv {
  
  template <typename T_ParentJoystick>
  class JoystickImpl_T
    : public JoystickImplBase<T_ParentJoystick, iphone_joystick_param_type>
  {
  public:
    typedef iphone_joystick_param_type              joystick_params_type;
    typedef T_ParentJoystick                        parent_type;
    typedef JoystickImpl_T<parent_type>             this_type;
    typedef JoystickImplBase
      <parent_type, joystick_params_type>           base_type;
    
    typedef typename parent_type::platform_type     platform_type;
    typedef typename parent_type::policy_type       policy_type;
    typedef typename base_type::button_code_type    button_code_type;
    typedef typename base_type::joystick_event_type joystick_event_type;
    
  public:
    JoystickImpl_T(parent_type* a_parent, const joystick_params_type& a_params)
      : base_type(a_parent, a_params)
    { }
    
    ~JoystickImpl_T() { }
    
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (joystick_event_type, GetCurrState, m_currentState);
    
    void Update() { }
    void Reset() { }
    
  private:
    using base_type::m_currentState;
    
  };
  
};};};};

#endif
