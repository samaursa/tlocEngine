#include "tlocMouseImplWin.h"

namespace tloc { namespace input { namespace hid { namespace priv {

#define MOUSE_IMPL_TEMP    typename T_ParentMouse
#define MOUSE_IMPL_PARAMS  T_ParentMouse
#define MOUSE_IMPL_TYPE    typename MouseImpl<MOUSE_IMPL_PARAMS>

  //------------------------------------------------------------------------
  // Free functions

  MouseEvent::ButtonCode TranslateKeyCode(DWORD dwOfs)
  {
    switch(dwOfs)
    {
    case DIMOFS_BUTTON0:      return MouseEvent::left;
    case DIMOFS_BUTTON1:      return MouseEvent::right;
    case DIMOFS_BUTTON2:      return MouseEvent::middle;
    case DIMOFS_BUTTON3:      return MouseEvent::button4;
    case DIMOFS_BUTTON4:      return MouseEvent::button5;
    case DIMOFS_BUTTON5:      return MouseEvent::button6;
    case DIMOFS_BUTTON6:      return MouseEvent::button7;
    case DIMOFS_BUTTON7:      return MouseEvent::button8;
    default:                  return MouseEvent::none;
    }
  }

  //------------------------------------------------------------------------
  // MouseImpl

  template MouseImpl< hid::Mouse<InputPolicy::Buffered> >;
  template MouseImpl< hid::Mouse<InputPolicy::Immediate> >;

  template <MOUSE_IMPL_TEMP>
  MouseImpl<MOUSE_IMPL_PARAMS>::
    MouseImpl(parent_type* a_parent,
    const mouse_param_type& a_params)
    : MouseImplBase(a_parent, a_params)
    , m_directInput(a_params.m_param2)
    , m_mouse(NULL)
    , m_windowPtr(a_params.m_param1)
    , m_currentState(MouseEvent::none)
  {
    DoInitialize();
  }

  template <MOUSE_IMPL_TEMP>
  MouseImpl<MOUSE_IMPL_PARAMS>::~MouseImpl()
  {
    if (m_mouse)
    {
      m_mouse->Unacquire();
      m_mouse->Release();
      m_mouse = NULL;
    }
  }

  template <MOUSE_IMPL_TEMP>
  bool MouseImpl<MOUSE_IMPL_PARAMS>::IsButtonDown(button_code_type a_mouse) const
  {
    return (m_currentState.m_buttonCode & a_mouse) == 1;
  }

  template <MOUSE_IMPL_TEMP>
  void MouseImpl<MOUSE_IMPL_PARAMS>::Update()
  {
    DoUpdate(policy_type());
  }

  template <MOUSE_IMPL_TEMP>
  void MouseImpl<MOUSE_IMPL_PARAMS>::DoInitialize()
  {
    if (FAILED(m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL)))
    {
      // LOG: Mouse failed to initialize
      return;
    }

    if ( FAILED(m_mouse->SetDataFormat(&c_dfDIMouse2)) )
    {
      // LOG: Mouse format error
      return;
    }

    DWORD coop = 0;
    // Default parameters or...?
    if (m_params.m_param3 == parameter_options::TL_DEFAULT)
    {
      coop = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
    }
    else
    {
      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_BACKGROUND)
      { coop = DISCL_BACKGROUND; }
      else { coop = DISCL_FOREGROUND; } // default

      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_NONEXCLUSIVE)
      { coop |= DISCL_NONEXCLUSIVE; }
      else { coop = DISCL_EXCLUSIVE; } // default

      if (m_params.m_param3 & parameter_options::TL_WIN_DISCL_NOWINKEY)
      { coop |= DISCL_NOWINKEY; }
    }

    if (!DoInitializeExtra(policy_type()))
    {
      // LOG: Unable to acquire a buffered mouse
      return;
    }

    if (FAILED(m_mouse->SetCooperativeLevel(m_windowPtr, coop)))
    {
      // LOG: Mouse cooperative level settings error
      return;
    }

    HRESULT hr = m_mouse->Acquire();
    if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
    {
      // LOG: Unable to acquire Win32 mouse
      return;
    }
  }

  template <MOUSE_IMPL_TEMP>
  bool MouseImpl<MOUSE_IMPL_PARAMS>::DoInitializeExtra(InputPolicy::Buffered)
  {
    TLOC_ASSERT_NOT_NULL(m_mouse);

    DIPROPDWORD dipw;
    dipw.diph.dwSize        = sizeof(DIPROPDWORD);
    dipw.diph.dwHeaderSize  = sizeof(DIPROPHEADER);
    dipw.diph.dwObj         = 0;
    dipw.diph.dwHow         = DIPH_DEVICE;
    dipw.dwData             = buffer_size::mouse_buffer_size;

    if (FAILED(m_mouse->SetProperty(DIPROP_BUFFERSIZE, &dipw.diph)))
    {
      return false;
    }

    return true;
  }

  template <MOUSE_IMPL_TEMP>
  void MouseImpl<MOUSE_IMPL_PARAMS>::DoUpdate(InputPolicy::Buffered)
  {
    m_currentState.m_X.m_rel() = 0;
    m_currentState.m_Y.m_rel() = 0;
    m_currentState.m_Z.m_rel() = 0;
    m_currentState.m_buttonCode = MouseEvent::none;

    DIDEVICEOBJECTDATA diBuff[buffer_size::mouse_buffer_size];
    DWORD entries = buffer_size::mouse_buffer_size;
    HRESULT hRes;

    hRes = m_mouse->
      GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, NULL);
    if (hRes != DI_OK)
    {
      // Try one more time
      hRes = m_mouse->Acquire();
      if (hRes != DI_OK)
      {
        return;
      }
      else
      {
        hRes = m_mouse->
          GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, NULL);
        if (hRes != DI_OK)
        {
          // we don't have the mouse, return
          return;
        }
      }
    }

    if (FAILED(hRes))
    {
      // LOG: Could not get device data
      TLOC_ASSERT(false, "Could not get device data!");
    }

    bool axesUpdated = false;
    for (tl_size i = 0; i < entries; ++i)
    {
      // Grab the key code that was pressed/released
      m_currentState.m_buttonCode |= TranslateKeyCode(diBuff[i].dwOfs);

      if (m_currentState.m_buttonCode != MouseEvent::none)
      {
        if (diBuff[i].dwData & 0x80)
          m_parent->SendOnButtonPress(m_currentState);
        else
          m_parent->SendOnButtonRelease(m_currentState);
      }
      else
      {
        switch(diBuff[i].dwOfs)
        {
        case DIMOFS_X:
          {
            m_currentState.m_X.m_rel() += (tl_int)diBuff[i].dwData;
            axesUpdated = true;
            break;
          }
        case DIMOFS_Y:
          {
            m_currentState.m_Y.m_rel() += (tl_int)diBuff[i].dwData;
            axesUpdated = true;
            break;
          }
        case DIMOFS_Z:
          {
            m_currentState.m_Z.m_rel() += (tl_int)diBuff[i].dwData;
            axesUpdated = true;
            break;
          }
        default: break;
        }
      }
    }

    // If the mouse was moved...
    if (axesUpdated)
    {
      // Going with OIS's suggestion here
      if (m_params.m_param3 == parameter_options::TL_WIN_DISCL_NONEXCLUSIVE)
      {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(m_windowPtr, &point);
        m_currentState.m_X.m_abs() = point.x;
        m_currentState.m_Y.m_abs() = point.y;
      }
      else
      {
        m_currentState.m_X.m_abs() += m_currentState.m_X.m_rel();
        m_currentState.m_Y.m_abs() += m_currentState.m_Y.m_rel();
      }
      m_currentState.m_Z.m_abs() += m_currentState.m_Z.m_rel();

      m_parent->SendOnMouseMove(m_currentState);
    }
  }

  template <MOUSE_IMPL_TEMP>
  void MouseImpl<MOUSE_IMPL_PARAMS>::DoUpdate(InputPolicy::Immediate)
  {
    HRESULT hRes = m_mouse->GetDeviceState(s_bufferSize, &m_mouseBuffer);

    if (hRes == DIERR_INPUTLOST || hRes == DIERR_NOTACQUIRED)
    {
      hRes = m_mouse->Acquire();
      if (hRes != DIERR_OTHERAPPHASPRIO)
      {
        m_mouse->GetDeviceState(s_bufferSize, &m_mouseBuffer);
      }
    }

    m_currentState.m_X.m_rel() = m_mouseBuffer.lX;
    m_currentState.m_Y.m_rel() = m_mouseBuffer.lY;
    m_currentState.m_Z.m_rel() = m_mouseBuffer.lZ;

    // Going with OIS's suggestion here
    if (m_params.m_param3 == parameter_options::TL_WIN_DISCL_NONEXCLUSIVE)
    {
      POINT point;
      GetCursorPos(&point);
      ScreenToClient(m_windowPtr, &point);
      m_currentState.m_X.m_abs() = point.x;
      m_currentState.m_Y.m_abs() = point.y;
    }
    else
    {
      m_currentState.m_X.m_abs() += m_currentState.m_X.m_rel();
      m_currentState.m_Y.m_abs() += m_currentState.m_Y.m_rel();
    }
    m_currentState.m_Z.m_abs() += m_currentState.m_Z.m_rel();

    if(m_mouseBuffer.rgbButtons[0] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::left;
    else if(m_mouseBuffer.rgbButtons[1] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::right;
    else if(m_mouseBuffer.rgbButtons[2] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::middle;
    else if(m_mouseBuffer.rgbButtons[3] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::button4;
    else if(m_mouseBuffer.rgbButtons[4] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::button5;
    else if(m_mouseBuffer.rgbButtons[5] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::button6;
    else if(m_mouseBuffer.rgbButtons[6] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::button7;
    else if(m_mouseBuffer.rgbButtons[7] & 0x80)
      m_currentState.m_buttonCode = MouseEvent::button8;
  }

};};};};