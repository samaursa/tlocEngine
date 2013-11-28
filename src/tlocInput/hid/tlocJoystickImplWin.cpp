#include "tlocJoystickImplWin.h"
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

// Copied directly from OIS:
// DX Only defines macros for the JOYSTICK not JOYSTICK2, so fix it
#undef DIJOFS_BUTTON
#undef DIJOFS_POV

#define DIJOFS_BUTTON(n)  (FIELD_OFFSET(DIJOYSTATE2, rgbButtons) + (n))
#define DIJOFS_POV(n)     (FIELD_OFFSET(DIJOYSTATE2, rgdwPOV)+(n)*sizeof(DWORD))
#define DIJOFS_SLIDER0(n) (FIELD_OFFSET(DIJOYSTATE2, rglSlider)+(n) * sizeof(LONG))
#define DIJOFS_SLIDER1(n) (FIELD_OFFSET(DIJOYSTATE2, rglVSlider)+(n) * sizeof(LONG))
#define DIJOFS_SLIDER2(n) (FIELD_OFFSET(DIJOYSTATE2, rglASlider)+(n) * sizeof(LONG))
#define DIJOFS_SLIDER3(n) (FIELD_OFFSET(DIJOYSTATE2, rglFSlider)+(n) * sizeof(LONG))

namespace {

  const tloc::tl_int g_numAxis = 24;
  const tloc::tl_int g_numSliders = 4;

};

namespace tloc { namespace input { namespace hid { namespace priv {

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

    DoEnumerate();
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
    DoEnumerate()
  {
    m_diJoyCaps.dwSize = sizeof(DIDEVCAPS);
    if (FAILED(m_joystick->GetCapabilities(&m_diJoyCaps)) )
    {
      // LOG: Failed to get joystick capabilities
      TLOC_ASSERT(false, "Failed to get joystick capabilities");
    }

    m_currentState.m_buttons.resize(m_diJoyCaps.dwButtons);
    m_currentState.m_axes.resize(m_diJoyCaps.dwAxes);

    m_axisNumber = 0;

    m_joystick->EnumObjects(DIEnumDeviceObjectsCallback, this, DIDFT_AXIS);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  DWORD
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoUpdate()
  {
    m_currentState.Clear();

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
      { return 0; }
      else
      {
        hRes = m_joystick->
          GetDeviceData(sizeof(DIDEVICEOBJECTDATA), diBuff, &entries, TLOC_NULL);

        // didn't acquire the joystick, return
        if (hRes != DI_OK)
        { return 0; }
      }
    }

    if (FAILED(hRes))
    {
      // LOG: Could not get device data
      TLOC_ASSERT(false, "Could not get joystick data");
    }

    m_axisMoved.clear();
    m_sliderMoved.clear();

    m_axisMoved.resize(g_numAxis, false);
    m_sliderMoved.resize(g_numSliders, false);

    for (tl_size i = 0; i < entries; ++i)
    {
      //This may seem out of order, but is in order of the way these variables
      //are declared in the JoyStick State 2 structure.
      switch(diBuff[i].dwOfs)
      {
        //------ slider -//
      case DIJOFS_SLIDER0(0):
        m_sliderMoved[0] = true;
        m_currentState.m_sliders[0].m_x = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER0(1):
        m_sliderMoved[0] = true;
        m_currentState.m_sliders[0].m_y = diBuff[i].dwData;
        break;
        //----- Max 4 POVs Next ---------------//
      case DIJOFS_POV(0):
        if(DoChangePOV(0,diBuff[i], policy_type()) == false)
          return entries;
        break;
      case DIJOFS_POV(1):
        if(DoChangePOV(1,diBuff[i], policy_type()) == false)
          return entries;
        break;
      case DIJOFS_POV(2):
        if(DoChangePOV(2,diBuff[i], policy_type()) == false)
          return entries;
        break;
      case DIJOFS_POV(3):
        if(DoChangePOV(3,diBuff[i], policy_type()) == false)
          return entries;
        break;
      case DIJOFS_SLIDER1(0):
        m_sliderMoved[1] = true;
        m_currentState.m_sliders[1].m_x = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER1(1):
        m_sliderMoved[1] = true;
        m_currentState.m_sliders[1].m_y = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER2(0):
        m_sliderMoved[2] = true;
        m_currentState.m_sliders[2].m_x = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER2(1):
        m_sliderMoved[2] = true;
        m_currentState.m_sliders[2].m_y = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER3(0):
        m_sliderMoved[3] = true;
        m_currentState.m_sliders[3].m_x = diBuff[i].dwData;
        break;
      case DIJOFS_SLIDER3(1):
        m_sliderMoved[3] = true;
        m_currentState.m_sliders[3].m_y = diBuff[i].dwData;
        break;
        //-----------------------------------------//
      default:
        //Handle Button Events Easily using the DX Offset Macros
        if( diBuff[i].dwOfs >= DIJOFS_BUTTON(0) && diBuff[i].dwOfs < DIJOFS_BUTTON(128) )
        {
          if(DoButtonEvent( (diBuff[i].dwOfs - DIJOFS_BUTTON(0)), diBuff[i],
                            policy_type()) == false)
          { return entries; }
        }
        else if((short)(diBuff[i].uAppData >> 16) == 0x1313)
        {	//If it was nothing else, might be axis enumerated earlier (determined by magic number)
          int axis = (int)(0x0000FFFF & diBuff[i].uAppData); //Mask out the high bit
          TLOC_ASSERT(axis >= 0 && axis < (int)m_currentState.m_axes.size(),
            "Axis out of range");

          if(axis >= 0 && axis < (int)m_currentState.m_axes.size())
          {
            m_currentState.m_axes[axis] = diBuff[i].dwData;
            m_axisMoved[axis] = true;
          }
        }

        break;
      } //end case
    }

    return entries;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  void
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoUpdate(InputPolicy::Buffered)
  {
    DWORD entries = DoUpdate();

    if (entries > 0)
    {
      for (tl_int i = 0; i < g_numAxis; ++i)
      {
        if (m_axisMoved[i])
        {
          if (m_parent->SendAxisChange(m_currentState) == false)
            return;
        }
      }

      for (tl_int i = 0; i < g_numSliders; ++i)
      {
        if (m_sliderMoved[i])
        {
          if (m_parent->SendSliderChange(m_currentState) == false)
            return;
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
    DoUpdate();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoButtonEvent(tl_int a_button, DIDEVICEOBJECTDATA& a_di, InputPolicy::Immediate)
  {
    if( a_di.dwData & 0x80 )
    {
      m_currentState.m_buttons[a_button] = true;
    }
    else
    {
      m_currentState.m_buttons[a_button] = true;
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoButtonEvent(tl_int a_button, DIDEVICEOBJECTDATA& a_di, InputPolicy::Buffered)
  {
    // Update the current state
    DoButtonEvent(a_button, a_di, InputPolicy::Immediate());

    if( a_di.dwData & 0x80 )
    {
      return m_parent->SendButtonPress( JoystickEvent(m_currentState) );
    }
    else
    {
      return m_parent->SendButtonRelease( JoystickEvent(m_currentState) );
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoChangePOV(tl_int a_pov, DIDEVICEOBJECTDATA& a_di, InputPolicy::Buffered)
  {
    DoChangePOV(a_pov, a_di, InputPolicy::Immediate());
    return m_parent->SendPOVChange(JoystickEvent(m_currentState));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoChangePOV(tl_int a_pov, DIDEVICEOBJECTDATA& a_di, InputPolicy::Immediate)
  {
    using namespace Component;

    if (LOWORD(a_di.dwData) == 0xFFFF)
    {
      m_currentState.m_pov[a_pov].SetDirection(Pov::k_centered);
    }
    else
    {
      switch(a_di.dwData)
      {
      case 0: m_currentState.m_pov[a_pov].SetDirection(Pov::k_north); break;
      case 4500: m_currentState.m_pov[a_pov].SetDirection(Pov::k_north_east); break;
      case 9000: m_currentState.m_pov[a_pov].SetDirection(Pov::k_east); break;
      case 13500: m_currentState.m_pov[a_pov].SetDirection(Pov::k_south_east); break;
      case 18000: m_currentState.m_pov[a_pov].SetDirection(Pov::k_south); break;
      case 22500: m_currentState.m_pov[a_pov].SetDirection(Pov::k_south_west); break;
      case 27000: m_currentState.m_pov[a_pov].SetDirection(Pov::k_west); break;
      case 31500: m_currentState.m_pov[a_pov].SetDirection(Pov::k_north_west); break;
      }
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  BOOL
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
  {
    this_type* t = (this_type*)pvRef;

    // Setup mappings
    DIPROPPOINTER diptr;
    diptr.diph.dwSize         = sizeof(DIPROPPOINTER);
    diptr.diph.dwHeaderSize   = sizeof(DIPROPHEADER);
    diptr.diph.dwHow          = DIPH_BYID;
    diptr.diph.dwObj          = lpddoi->dwType;
    //Add a magic number to recognise we set seomthing
    diptr.uData               = 0x13130000 | t->m_axisNumber;

    // If the axis is a slider, then remove it from regular axis
    tl_int sliderCount = 0;
    if (GUID_Slider == lpddoi->guidType)
    {
      ++sliderCount;
      t->m_currentState.m_axes.pop_back();
    }
    else if (FAILED(t->m_joystick->SetProperty(DIPROP_APPDATA, &diptr.diph)) )
    {
      return DIENUM_CONTINUE;
    }

    // set the range of the axis
    DIPROPRANGE diprg;
    diprg.diph.dwSize       = sizeof(DIPROPRANGE);
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diprg.diph.dwHow        = DIPH_BYID;
    diprg.diph.dwObj        = lpddoi->dwType;
    diprg.lMin              = base_type::MIN_AXIS;
    diprg.lMax              = base_type::MAX_AXIS;

    if (FAILED(t->m_joystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
    {
      // LOG: Failed to set min/max range for the axis
      TLOC_ASSERT(false, "Failed to set min/max for the axis");
    }

    return DIENUM_CONTINUE;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template JoystickImpl_T<Joystick_T<InputPolicy::Buffered> >;
  template JoystickImpl_T<Joystick_T<InputPolicy::Immediate> >;

};};};};