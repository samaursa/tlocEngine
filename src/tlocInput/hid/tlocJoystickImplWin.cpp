#include "tlocJoystickImplWin.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/logging/tlocLogger.h>

// In dinput.h we have macros for offsets for the DIJOYSTATE struct but no
// macros for DIJOYSTATE2 struct, we will define our own here (by copying
// the existing macros in DIJOYSTATE and replacing DIJOYSTATE with DIJOYSTATE2)

#define TLOC_DIJOFS_X            FIELD_OFFSET(DIJOYSTATE2, lX)
#define TLOC_DIJOFS_Y            FIELD_OFFSET(DIJOYSTATE2, lY)
#define TLOC_DIJOFS_Z            FIELD_OFFSET(DIJOYSTATE2, lZ)
#define TLOC_DIJOFS_RX           FIELD_OFFSET(DIJOYSTATE2, lRx)
#define TLOC_DIJOFS_RY           FIELD_OFFSET(DIJOYSTATE2, lRy)
#define TLOC_DIJOFS_RZ           FIELD_OFFSET(DIJOYSTATE2, lRz)

#define TLOC_DIJOFS_VX            FIELD_OFFSET(DIJOYSTATE2, lVX)
#define TLOC_DIJOFS_VY            FIELD_OFFSET(DIJOYSTATE2, lVY)
#define TLOC_DIJOFS_VZ            FIELD_OFFSET(DIJOYSTATE2, lVZ)
#define TLOC_DIJOFS_VRX           FIELD_OFFSET(DIJOYSTATE2, lVRx)
#define TLOC_DIJOFS_VRY           FIELD_OFFSET(DIJOYSTATE2, lVRy)
#define TLOC_DIJOFS_VRZ           FIELD_OFFSET(DIJOYSTATE2, lVRz)

#define TLOC_DIJOFS_AX            FIELD_OFFSET(DIJOYSTATE2, lAX)
#define TLOC_DIJOFS_AY            FIELD_OFFSET(DIJOYSTATE2, lAY)
#define TLOC_DIJOFS_AZ            FIELD_OFFSET(DIJOYSTATE2, lAZ)
#define TLOC_DIJOFS_ARX           FIELD_OFFSET(DIJOYSTATE2, lARx)
#define TLOC_DIJOFS_ARY           FIELD_OFFSET(DIJOYSTATE2, lARy)
#define TLOC_DIJOFS_ARZ           FIELD_OFFSET(DIJOYSTATE2, lARz)

#define TLOC_DIJOFS_FX            FIELD_OFFSET(DIJOYSTATE2, lFX)
#define TLOC_DIJOFS_FY            FIELD_OFFSET(DIJOYSTATE2, lFY)
#define TLOC_DIJOFS_FZ            FIELD_OFFSET(DIJOYSTATE2, lFZ)
#define TLOC_DIJOFS_FRX           FIELD_OFFSET(DIJOYSTATE2, lFRx)
#define TLOC_DIJOFS_FRY           FIELD_OFFSET(DIJOYSTATE2, lFRy)
#define TLOC_DIJOFS_FRZ           FIELD_OFFSET(DIJOYSTATE2, lFRz)

#define TLOC_DIJOFS_SLIDER0(n)   (FIELD_OFFSET(DIJOYSTATE2, rglSlider) + \
                                                        (n) * sizeof(LONG))
#define TLOC_DIJOFS_SLIDER1(n)   (FIELD_OFFSET(DIJOYSTATE2, rglVSlider) + \
                                                        (n) * sizeof(LONG))
#define TLOC_DIJOFS_SLIDER2(n)   (FIELD_OFFSET(DIJOYSTATE2, rglASlider) + \
                                                        (n) * sizeof(LONG))
#define TLOC_DIJOFS_SLIDER3(n)   (FIELD_OFFSET(DIJOYSTATE2, rglFSlider) + \
                                                        (n) * sizeof(LONG))
#define TLOC_DIJOFS_POV(n)      (FIELD_OFFSET(DIJOYSTATE2, rgdwPOV) + \
                                                        (n) * sizeof(DWORD))
#define TLOC_DIJOFS_BUTTON(n)   (FIELD_OFFSET(DIJOYSTATE2, rgbButtons) + (n))
#define TLOC_DIJOFS_BUTTON0      TLOC_DIJOFS_BUTTON(0)
#define TLOC_DIJOFS_BUTTON1      TLOC_DIJOFS_BUTTON(1)
#define TLOC_DIJOFS_BUTTON2      TLOC_DIJOFS_BUTTON(2)
#define TLOC_DIJOFS_BUTTON3      TLOC_DIJOFS_BUTTON(3)
#define TLOC_DIJOFS_BUTTON4      TLOC_DIJOFS_BUTTON(4)
#define TLOC_DIJOFS_BUTTON5      TLOC_DIJOFS_BUTTON(5)
#define TLOC_DIJOFS_BUTTON6      TLOC_DIJOFS_BUTTON(6)
#define TLOC_DIJOFS_BUTTON7      TLOC_DIJOFS_BUTTON(7)
#define TLOC_DIJOFS_BUTTON8      TLOC_DIJOFS_BUTTON(8)
#define TLOC_DIJOFS_BUTTON9      TLOC_DIJOFS_BUTTON(9)
#define TLOC_DIJOFS_BUTTON10     TLOC_DIJOFS_BUTTON(10)
#define TLOC_DIJOFS_BUTTON11     TLOC_DIJOFS_BUTTON(11)
#define TLOC_DIJOFS_BUTTON12     TLOC_DIJOFS_BUTTON(12)
#define TLOC_DIJOFS_BUTTON13     TLOC_DIJOFS_BUTTON(13)
#define TLOC_DIJOFS_BUTTON14     TLOC_DIJOFS_BUTTON(14)
#define TLOC_DIJOFS_BUTTON15     TLOC_DIJOFS_BUTTON(15)
#define TLOC_DIJOFS_BUTTON16     TLOC_DIJOFS_BUTTON(16)
#define TLOC_DIJOFS_BUTTON17     TLOC_DIJOFS_BUTTON(17)
#define TLOC_DIJOFS_BUTTON18     TLOC_DIJOFS_BUTTON(18)
#define TLOC_DIJOFS_BUTTON19     TLOC_DIJOFS_BUTTON(19)
#define TLOC_DIJOFS_BUTTON20     TLOC_DIJOFS_BUTTON(20)
#define TLOC_DIJOFS_BUTTON21     TLOC_DIJOFS_BUTTON(21)
#define TLOC_DIJOFS_BUTTON22     TLOC_DIJOFS_BUTTON(22)
#define TLOC_DIJOFS_BUTTON23     TLOC_DIJOFS_BUTTON(23)
#define TLOC_DIJOFS_BUTTON24     TLOC_DIJOFS_BUTTON(24)
#define TLOC_DIJOFS_BUTTON25     TLOC_DIJOFS_BUTTON(25)
#define TLOC_DIJOFS_BUTTON26     TLOC_DIJOFS_BUTTON(26)
#define TLOC_DIJOFS_BUTTON27     TLOC_DIJOFS_BUTTON(27)
#define TLOC_DIJOFS_BUTTON28     TLOC_DIJOFS_BUTTON(28)
#define TLOC_DIJOFS_BUTTON29     TLOC_DIJOFS_BUTTON(29)
#define TLOC_DIJOFS_BUTTON30     TLOC_DIJOFS_BUTTON(30)
#define TLOC_DIJOFS_BUTTON31     TLOC_DIJOFS_BUTTON(31)

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
                   , m_sliderCount(0)
                   , m_povCount(0)
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
      TLOC_LOG_INPUT_ERR() << "Joystick failed to initialize";
      return;
    }

    if (FAILED(m_joystick->SetDataFormat(&c_dfDIJoystick2)) )
    {
      TLOC_LOG_INPUT_ERR() << "Could not set joystick device format";
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
      TLOC_LOG_INPUT_ERR() << "Unable to acquire a buffered joystick";
      return;
    }

    if (FAILED(m_joystick->SetCooperativeLevel(m_windowPtr, coop)))
    {
      TLOC_LOG_INPUT_ERR() << "Joystick cooperative level settings error";
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
    { TLOC_LOG_INPUT_ERR() << "Failed to get joystick capabilities"; }

    m_axisCount = m_diJoyCaps.dwAxes;
    m_povCount = m_diJoyCaps.dwPOVs;

    m_currentState.m_buttons.resize(m_diJoyCaps.dwButtons);
    m_currentState.m_axes.resize(m_diJoyCaps.dwAxes);
    m_currentState.m_pov.resize(m_diJoyCaps.dwPOVs);

    m_axisMoved.resize(m_diJoyCaps.dwAxes);

    m_joystick->EnumObjects(DIEnumDeviceObjectsCallback, this, DIDFT_AXIS);
    m_currentState.m_sliders.resize(m_sliderCount);

    m_currentState.Clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  DWORD
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoUpdate()
  {
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
      TLOC_LOG_INPUT_ERR() << "Could not get joystick (device) data";
    }

    core::fill_all(m_axisMoved, false);
    core::fill_all(m_sliderMoved, false);

    for (tl_size i = 0; i < entries; ++i)
    {
      const s32 data = diBuff[i].dwData;
      const s32 offset = diBuff[i].dwOfs;

      switch(offset)
      {
        // -----------------------------------------------------------------------
        // Since there are only 4 POVs in the DIJOYSTATE struct
      case TLOC_DIJOFS_SLIDER0(0):
        m_sliderMoved[0] = true;
        m_currentState.m_sliders[0][0] = data;
        break;
      case TLOC_DIJOFS_SLIDER0(1):
        m_sliderMoved[0] = true;
        m_currentState.m_sliders[0][1] = data;
        break;
      case TLOC_DIJOFS_SLIDER1(0):
        m_sliderMoved[1] = true;
        m_currentState.m_sliders[1][0] = data;
        break;
      case TLOC_DIJOFS_SLIDER1(1):
        m_sliderMoved[1] = true;
        m_currentState.m_sliders[1][1] = data;
        break;
      case TLOC_DIJOFS_SLIDER2(0):
        m_sliderMoved[2] = true;
        m_currentState.m_sliders[2][0] = data;
        break;
      case TLOC_DIJOFS_SLIDER2(1):
        m_sliderMoved[2] = true;
        m_currentState.m_sliders[2][1] = data;
        break;
      case TLOC_DIJOFS_SLIDER3(0):
        m_sliderMoved[3] = true;
        m_currentState.m_sliders[3][0] = data;
        break;
      case TLOC_DIJOFS_SLIDER3(1):
        m_sliderMoved[3] = true;
        m_currentState.m_sliders[3][1] = data;
        break;
        // -----------------------------------------------------------------------
        // Since there are only 4 POVs in the DIJOYSTATE struct
      case TLOC_DIJOFS_POV(0):
        if(DoChangePOV(0,diBuff[i], policy_type()) == false)
        break;
      case TLOC_DIJOFS_POV(1):
        if(DoChangePOV(1,diBuff[i], policy_type()) == false)
        break;
      case TLOC_DIJOFS_POV(2):
        if(DoChangePOV(2,diBuff[i], policy_type()) == false)
        break;
      case TLOC_DIJOFS_POV(3):
        if(DoChangePOV(3,diBuff[i], policy_type()) == false)
        break;
      default:
        if( offset >= TLOC_DIJOFS_BUTTON(0) &&
            offset < TLOC_DIJOFS_BUTTON(joystick_event_type::k_count) )
        {
          if(DoButtonEvent( (offset - TLOC_DIJOFS_BUTTON(0)), diBuff[i],
                            policy_type()) == false)
          { continue; }
        }
        else if (diBuff[i].uAppData == 0x1313)
        {
          switch(offset)
          {
            // -----------------------------------------------------------------------
            // axis #1
          case TLOC_DIJOFS_X:
            m_currentState.m_axes[0][0] = data;
            m_axisMoved[0] = true;
            break;
          case TLOC_DIJOFS_Y:
            m_currentState.m_axes[0][1] = data;
            m_axisMoved[0] = true;
            break;
          case TLOC_DIJOFS_Z:
            m_currentState.m_axes[0][2] = data;
            m_axisMoved[0] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #2
          case TLOC_DIJOFS_RX:
            m_currentState.m_axes[1][0] = data;
            m_axisMoved[1] = true;
            break;
          case TLOC_DIJOFS_RY:
            m_currentState.m_axes[1][1] = data;
            m_axisMoved[1] = true;
            break;
          case TLOC_DIJOFS_RZ:
            m_currentState.m_axes[1][2] = data;
            m_axisMoved[1] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #3
          case TLOC_DIJOFS_VX:
            m_currentState.m_axes[2][0] = data;
            m_axisMoved[2] = true;
            break;
          case TLOC_DIJOFS_VY:
            m_currentState.m_axes[2][1] = data;
            m_axisMoved[2] = true;
            break;
          case TLOC_DIJOFS_VZ:
            m_currentState.m_axes[2][2] = data;
            m_axisMoved[2] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #4
          case TLOC_DIJOFS_VRX:
            m_currentState.m_axes[3][0] = data;
            m_axisMoved[3] = true;
            break;
          case TLOC_DIJOFS_VRY:
            m_currentState.m_axes[3][1] = data;
            m_axisMoved[3] = true;
            break;
          case TLOC_DIJOFS_VRZ:
            m_currentState.m_axes[3][2] = data;
            m_axisMoved[3] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #5
          case TLOC_DIJOFS_AX:
            m_currentState.m_axes[4][0] = data;
            m_axisMoved[4] = true;
            break;
          case TLOC_DIJOFS_AY:
            m_currentState.m_axes[4][1] = data;
            m_axisMoved[4] = true;
            break;
          case TLOC_DIJOFS_AZ:
            m_currentState.m_axes[4][2] = data;
            m_axisMoved[4] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #6
          case TLOC_DIJOFS_ARX:
            m_currentState.m_axes[5][0] = data;
            m_axisMoved[5] = true;
            break;
          case TLOC_DIJOFS_ARY:
            m_currentState.m_axes[5][1] = data;
            m_axisMoved[5] = true;
            break;
          case TLOC_DIJOFS_ARZ:
            m_currentState.m_axes[5][2] = data;
            m_axisMoved[5] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #7
          case TLOC_DIJOFS_FX:
            m_currentState.m_axes[6][0] = data;
            m_axisMoved[6] = true;
            break;
          case TLOC_DIJOFS_FY:
            m_currentState.m_axes[6][1] = data;
            m_axisMoved[6] = true;
            break;
          case TLOC_DIJOFS_FZ:
            m_currentState.m_axes[6][2] = data;
            m_axisMoved[6] = true;
            break;

            // -----------------------------------------------------------------------
            // axis #8
          case TLOC_DIJOFS_FRX:
            m_currentState.m_axes[7][0] = data;
            m_axisMoved[7] = true;
            break;
          case TLOC_DIJOFS_FRY:
            m_currentState.m_axes[7][1] = data;
            m_axisMoved[7] = true;
            break;
          case TLOC_DIJOFS_FRZ:
            m_currentState.m_axes[7][2] = data;
            m_axisMoved[7] = true;
            break;
          }
        }
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
      for (tl_int i = 0; i < m_axisCount; ++i)
      {
        if (m_axisMoved[i])
        {
          if (m_parent->SendAxisChange(m_currentState, i,
                                       m_currentState.m_axes[i]) == false)
            return;
        }
      }

      for (tl_int i = 0; i < m_sliderCount; ++i)
      {
        if (m_sliderMoved[i])
        {
          if (m_parent->SendSliderChange(m_currentState, i,
                                         m_currentState.m_sliders[i]) == false)
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
      return m_parent->SendButtonPress( JoystickEvent(m_currentState), a_button);
    }
    else
    {
      return m_parent->SendButtonRelease( JoystickEvent(m_currentState), a_button);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoChangePOV(tl_int a_povIndex, DIDEVICEOBJECTDATA& a_di, InputPolicy::Buffered)
  {
    DoChangePOV(a_povIndex, a_di, InputPolicy::Immediate());
    return m_parent->SendPOVChange(JoystickEvent(m_currentState), a_povIndex,
                                   m_currentState.m_pov[a_povIndex]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <JOYSTICK_IMPL_TEMP>
  bool
    JoystickImpl_T<JOYSTICK_IMPL_PARAMS>::
    DoChangePOV(tl_int a_povIndex, DIDEVICEOBJECTDATA& a_di, InputPolicy::Immediate)
  {
    using namespace Component;

    if (LOWORD(a_di.dwData) == 0xFFFF)
    {
      m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_centered);
    }
    else
    {
      switch(a_di.dwData)
      {
      case 0: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_north); break;
      case 4500: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_north_east); break;
      case 9000: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_east); break;
      case 13500: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_south_east); break;
      case 18000: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_south); break;
      case 22500: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_south_west); break;
      case 27000: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_west); break;
      case 31500: m_currentState.m_pov[a_povIndex].SetDirection(Pov::k_north_west); break;
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
    diptr.uData               = 0x1313;

    // If the axis is a slider, then remove it from regular axis
    if (GUID_Slider == lpddoi->guidType)
    {
      t->m_sliderCount++;
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
    { TLOC_LOG_INPUT_WARN() << "Failed to set min/max for the axis"; }

    return DIENUM_CONTINUE;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template JoystickImpl_T<Joystick_T<InputPolicy::Buffered> >;
  template JoystickImpl_T<Joystick_T<InputPolicy::Immediate> >;

};};};};

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(bool);