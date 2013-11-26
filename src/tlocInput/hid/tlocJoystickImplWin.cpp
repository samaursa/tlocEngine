#include "tlocJoystickImplWin.h"
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

namespace tloc { namespace input { namespace hid { namespace priv {

  // ///////////////////////////////////////////////////////////////////////
  // TranslateKeyCode function

  namespace {

    JoystickEvent::state_code_type
      TranslateStateCode(DWORD dwOfs)
    {
      switch(dwOfs)
      {
      case DIJOFS_X:           return JoystickEvent::k_xPos;
      case DIJOFS_Y:           return JoystickEvent::k_yPos;
      case DIJOFS_Z:           return JoystickEvent::k_zPos;
      case DIJOFS_RX:          return JoystickEvent::k_xRot;
      case DIJOFS_RY:          return JoystickEvent::k_yRot;
      case DIJOFS_RZ:          return JoystickEvent::k_zRot;
      case DIJOFS_SLIDER(0):   return JoystickEvent::k_slider0;
      case DIJOFS_SLIDER(1):   return JoystickEvent::k_slider1;
      case DIJOFS_POV(0):      return JoystickEvent::k_pov0;
      case DIJOFS_POV(1):      return JoystickEvent::k_pov1;
      case DIJOFS_POV(2):      return JoystickEvent::k_pov2;
      case DIJOFS_POV(3):      return JoystickEvent::k_pov3;
      case DIJOFS_BUTTON0:     return JoystickEvent::k_button0;
      case DIJOFS_BUTTON1:     return JoystickEvent::k_button1;
      case DIJOFS_BUTTON2:     return JoystickEvent::k_button2;
      case DIJOFS_BUTTON3:     return JoystickEvent::k_button3;
      case DIJOFS_BUTTON4:     return JoystickEvent::k_button4;
      case DIJOFS_BUTTON5:     return JoystickEvent::k_button5;
      case DIJOFS_BUTTON6:     return JoystickEvent::k_button6;
      case DIJOFS_BUTTON7:     return JoystickEvent::k_button7;
      case DIJOFS_BUTTON8:     return JoystickEvent::k_button8;
      case DIJOFS_BUTTON9:     return JoystickEvent::k_button9;
      case DIJOFS_BUTTON10:     return JoystickEvent::k_button10;
      case DIJOFS_BUTTON11:     return JoystickEvent::k_button11;
      case DIJOFS_BUTTON12:     return JoystickEvent::k_button12;
      case DIJOFS_BUTTON13:     return JoystickEvent::k_button13;
      case DIJOFS_BUTTON14:     return JoystickEvent::k_button14;
      case DIJOFS_BUTTON15:     return JoystickEvent::k_button15;
      case DIJOFS_BUTTON16:     return JoystickEvent::k_button16;
      case DIJOFS_BUTTON17:     return JoystickEvent::k_button17;
      case DIJOFS_BUTTON18:     return JoystickEvent::k_button18;
      case DIJOFS_BUTTON19:     return JoystickEvent::k_button19;
      case DIJOFS_BUTTON20:     return JoystickEvent::k_button20;
      case DIJOFS_BUTTON21:     return JoystickEvent::k_button21;
      case DIJOFS_BUTTON22:     return JoystickEvent::k_button22;
      case DIJOFS_BUTTON23:     return JoystickEvent::k_button23;
      case DIJOFS_BUTTON24:     return JoystickEvent::k_button24;
      case DIJOFS_BUTTON25:     return JoystickEvent::k_button25;
      case DIJOFS_BUTTON26:     return JoystickEvent::k_button26;
      case DIJOFS_BUTTON27:     return JoystickEvent::k_button27;
      case DIJOFS_BUTTON28:     return JoystickEvent::k_button28;
      case DIJOFS_BUTTON29:     return JoystickEvent::k_button29;
      case DIJOFS_BUTTON30:     return JoystickEvent::k_button30;
      case DIJOFS_BUTTON31:     return JoystickEvent::k_button31;
      default:                  return JoystickEvent::k_none;
      }
    }

  };

  // ///////////////////////////////////////////////////////////////////////
  // JoystickImpl_T<>

#define JOYSTICK_IMPL_TEMP    typename T_ParentJoystick
#define JOYSTICK_IMPL_PARAMS  T_ParentJoystick
#define JOYSTICK_IMPL_TYPE    typename JoystickImpl_T<JOYSTICK_IMPL_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    JoystickImpl_T(parent_type* a_parent,
                   const joystick_params_type& a_params)
                   : JoystickImplBase(a_parent, a_params)
                   , m_directInput(a_params.m_param2)
                   , m_joystick(TLOC_NULL)
                   , m_windowPtr(a_params.m_param1)
  {
    DoInitialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    ~JoystickImpl_T()
  {
    if (m_joystick)
    {
      m_joystick->Unacquire();
      m_joystick->Release();
      m_joystick = TLOC_NULL;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    Update()
  {
    DoUpdate(policy_type());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    Reset()
  {
    DoReset(policy_type());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoInitialize()
  {
    if (FAILED(m_directInput->
      CreateDevice(GUID_Joystick, &m_joystick, TLOC_NULL)) )
    {
      // LOG: Joystick failed to initialize
      TLOC_ASSERT(false, "Joystick failed to initialize");
      return;
    }

    if (FAILED(m_joystick->SetDataFormat(&c_dfDIJoystick)) )
    {
      // Log: Joystick format error
      TLOC_ASSERT(false, "Could not set joystick device format");
    }

    DWORD coop = 0;

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_BACKGROUND)
    { coop |= DISCL_BACKGROUND; }
    else { coop |= DISCL_FOREGROUND; } // default

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_NONEXCLUSIVE)
    { coop |= DISCL_NONEXCLUSIVE; }
    else { coop |= DISCL_EXCLUSIVE; } // default

    if (m_params.m_param3 & param_options::TL_WIN_DISCL_NOWINKEY)
    { coop |= DISCL_NOWINKEY; }

    if (!DoInitializeExtra(policy_type()))
    {
      // LOG: Unable to acquire a buffered joystick
      return;
    }

    if (FAILED(m_joystick->SetCooperativeLevel(m_windowPtr, coop)))
    {
      // LOG: Joystick cooperative level settings error
      return;
    }

    HRESULT hr = m_joystick->Acquire();
    if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
    {
      // LOG: Unable to acquire Win32 joystick
      return;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoInitializeExtra(InputPolicy::Buffered)
  {
    TLOC_ASSERT_NOT_NULL(m_joystick);

    DIPROPDWORD dipw;
    dipw.diph.dwSize            = sizeof(DIPROPDWORD);
    dipw.diph.dwHeaderSize      = sizeof(DIPROPHEADER);
    dipw.diph.dwObj             = 0;
    dipw.diph.dwHow             = DIPH_DEVICE;
    dipw.dwData                 = buffer_size::joystick_buffer_Size;

    if (FAILED(m_joystick->SetProperty(DIPROP_BUFFERSIZE, &dipw.diph)))
    {
      return false;
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoUpdate(InputPolicy::Buffered)
  {
    m_currentState = JoystickEvent();

    DIDEVICEOBJECTDATA diBuff[buffer_size::joystick_buffer_Size];
    DWORD entries = buffer_size::joystick_buffer_Size;
    HRESULT hRes;

    hRes = m_joystick->
      GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, TLOC_NULL);
    if (hRes != DI_OK)
    {
      // try one more time
      hRes = m_joystick->Acquire();
      if (hRes != DI_OK)
      { return; }
      else
      {
        hRes = m_joystick->
          GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, TLOC_NULL);

        // didn't acquire the joystick, return
        if (hRes != DI_OK)
        { return; }
      }
    }

    if (FAILED(hRes))
    {
      // LOG: Could not get device data
      TLOC_ASSERT(false, "Could not get joystick data");
    }

    bool axesUpdated = false;
    for (tl_size i = 0; i < entries; ++i)
    {
      JoystickEvent::state_code_type stateCode = TranslateStateCode(diBuff[i].dwOfs);

      m_currentState.SetState(m_currentState.GetState() | stateCode);

      if (stateCode != JoystickEvent::k_none)
      {
        if (diBuff[i].dwData & 0x80)
        {
        }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoUpdate(InputPolicy::Immediate)
  {
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template JoystickImpl_T<Joystick_T<InputPolicy::Buffered> >;
  template JoystickImpl_T<Joystick_T<InputPolicy::Immediate> >;

};};};};