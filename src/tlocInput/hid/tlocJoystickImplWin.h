#ifndef _TLOC_INTPUT_HID_JOYSTICK_IMPL_H_
#define _TLOC_INTPUT_HID_JOYSTICK_IMPL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocJoystick.h>
#include <tlocInput/hid/tlocJoystickImpl.h>

#include <tlocCore/platform/tlocPlatformSpecificIncludes.h>
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <WinSDK/dinput.h>

// ///////////////////////////////////////////////////////////////////////
// ParamList

namespace tloc { namespace input {

  typedef ParamList<HWND, IDirectInput8*, param_options::value_type>
    windows_joystick_param_type;

};};

namespace tloc { namespace input { namespace hid { namespace priv {


  // ///////////////////////////////////////////////////////////////////////
  // Joystick Info (from OIS)

  struct JoystickInfo
  {
    tl_int            m_deviceId;
    GUID              m_deviceGuid;
    GUID              m_productGuid;
    core_str::String  m_vendor;
    bool              m_xInput;
    tl_int            m_xInputDev;
  };

  // ///////////////////////////////////////////////////////////////////////
  // JoystickImpl_T

  // Reference: http://www.csh.rit.edu/~oguns/src/DirectInput.cpp

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

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (joystick_event_type, GetCurrState, m_currentState);

    void  Update();
    void  Reset();

  private:
    void  DoInitialize();
    // Buffered input requires extra initialization
    bool  DoInitializeExtra(InputPolicy::Buffered);
    // Immediate mode does not require anything special
    bool  DoInitializeExtra(InputPolicy::Immediate) { return true; }

    void  DoEnumerate();

    DWORD DoUpdate();

    void  DoUpdate(InputPolicy::Buffered);
    void  DoUpdate(InputPolicy::Immediate);

    void  DoReset(InputPolicy::Buffered) { }
    void  DoReset(InputPolicy::Immediate) { }

    bool  DoButtonEvent(tl_int a_button, DIDEVICEOBJECTDATA& a_di, InputPolicy::Buffered);
    bool  DoButtonEvent(tl_int a_button, DIDEVICEOBJECTDATA& a_di, InputPolicy::Immediate);
    bool  DoChangePOV(tl_int a_pov, DIDEVICEOBJECTDATA& a_di, InputPolicy::Buffered);
    bool  DoChangePOV(tl_int a_pov, DIDEVICEOBJECTDATA& a_di, InputPolicy::Immediate);

    //! Enumerate axis callback
    static BOOL CALLBACK DIEnumDeviceObjectsCallback
      (LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

  private:
    using base_type::m_currentState;
    using base_type::m_parent;

    IDirectInput8*        m_directInput;
    IDirectInputDevice8*  m_joystick;
    DIDEVCAPS             m_diJoyCaps;
    HWND                  m_windowPtr;

    // we have to store the slider count here because the callback DIEnumDevice...
    // may be called several times which will allow us to use this count to set
    // the size of the slider array
    tl_int                      m_sliderCount;
    tl_int                      m_povCount;
    tl_int                      m_axisCount;

    core_conts::Array<bool>     m_axisMoved;
    core_conts::Array<bool>     m_sliderMoved;

    JoystickInfo          m_joyInfo;
  };

};};};};

#endif