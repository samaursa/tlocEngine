#ifndef _TLOC_INTPUT_HID_JOYSTICK_IMPL_H_
#define _TLOC_INTPUT_HID_JOYSTICK_IMPL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocJoystick.h>
#include <tlocInput/hid/tlocJoystickImpl.h>

#ifndef NOMINMAX
  #define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <WinSDK/dinput.h>

// ///////////////////////////////////////////////////////////////////////
// ParamList

namespace tloc { namespace input {

  typedef ParamList<HWND, IDirectInput8*, param_options::value_type>
    windows_joystick_param_type;

};};

// ///////////////////////////////////////////////////////////////////////
// JoystickImpl_T

// Reference: http://www.csh.rit.edu/~oguns/src/DirectInput.cpp

namespace tloc { namespace input { namespace hid { namespace priv {

  template <typename T_ParentJoystick>
  class JoystickImpl_T
    : public JoystickImplBase<T_ParentJoystick, windows_joystick_param_type>
  {
  public:
    typedef windows_joystick_param_type                 joystick_params_type;
    typedef T_ParentJoystick                            parent_type;
    typedef JoystickImpl_T<parent_type>                 this_type;
    typedef JoystickImplBase
      <parent_type, joystick_params_type>               base_type;

    typedef typename parent_type::platform_type         platform_type;
    typedef typename parent_type::policy_type           policy_type;
    typedef typename base_type::button_code_type        button_code_type;

  public:
    JoystickImpl_T(parent_type* a_parent,
                   const joystick_params_type& a_params);
    ~JoystickImpl_T();

    bool  IsButtonDown(button_code_type a_key) const;

    void  Update();
    void  Reset();

  private:
    void  DoInitialize();
    // Buffered input requires extra initialization
    bool  DoInitializeExtra(InputPolicy::Buffered);
    // Immediate mode does not require anything special
    bool  DoInitializeExtra(InputPolicy::Immediate) { return true; }

    void  DoUpdate(InputPolicy::Buffered);
    void  DoUpdate(InputPolicy::Immediate);

    void  DoReset(InputPolicy::Buffered);
    void  DoReset(InputPolicy::Immediate);

  private:
    IDirectInput8*        m_directInput;
    IDirectInputDevice8*  m_joystick;
    HWND                  m_windowPtr;

    bool                  m_buffer[JoystickEvent::k_count];

    JoystickEvent           m_currentState;
    static const size_type  s_bufferSize = sizeof(DIJOYSTATE);
  };

};};};};

#endif