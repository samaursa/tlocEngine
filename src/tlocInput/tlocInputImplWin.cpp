#include "tlocInputImplWin.h"

#include "tlocCore/tlocArray.inl"
#include "tlocCore/tlocString.inl"

#include "tlocKeyboardImplWin.h"

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < hid::total_input_types,\
  "Unsupported input type passed!")

  template InputManagerImpl<InputManager<InputPolicy::Buffered> >;
  template InputManagerImpl<InputManager<InputPolicy::Immediate> >;

  template Keyboard<InputPolicy::Buffered>* InputManagerImpl<InputManager<InputPolicy::Buffered> >::CreateHID<Keyboard<InputPolicy::Buffered> >(input_type, parameter_options::Type);
  template Keyboard<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> >::CreateHID<Keyboard<InputPolicy::Immediate> >(input_type, parameter_options::Type);

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : InputManagerImplBase(a_parent, a_params)
                     , m_directInput(NULL)
  {
    m_winHIDs.resize(hid::total_input_types);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    if (m_directInput)
    {
      m_directInput->Release();
      m_directInput = NULL;
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Initialize()
  {
    HINSTANCE hInst = NULL;
    HRESULT hr;

    if (IsWindow(m_params.m_param1) == 0)
    {
      // LOG: The passed window pointer is not valid
      return 1;
    }

    hInst = GetModuleHandle(NULL);

    // Create the input device
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (VOID**)&m_directInput, NULL);
    if (FAILED(hr))
    {
      // LOG: Unable to initialize direct input
      return 1;
    }

    DoEnumerateDevices();
    return 0;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(input_type a_inputType, parameter_options::Type a_params)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch(a_inputType)
    {
    case hid::keyboard:
      {
        windows_keyboard_param_type params;
        params.m_param1 = m_params.m_param1;
        params.m_param2 = m_directInput;
        params.m_param3 = a_params;

        for (size_type i = 0; i < m_winHIDs[hid::keyboard].size(); ++i)
        {
          if (m_winHIDs[hid::keyboard][i].first == false)
          {
            T_InputObject* newInput = new Keyboard<policy_type>(params);
            m_winHIDs[hid::keyboard][i].first = true;
            return newInput;
          }
          else
          {
            // LOG: Could not create a keyboard (either one is already created
            //      or we do not have any keyboards attached)
          }
        }
        break;
      }
    case hid::mouse:
      {
        break;
      }
    case hid::joystick:
      {
        break;
      }
    default:
      {
        return NULL;
      }
    }

    return NULL;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch(a_inputType)
    {
    case hid::keyboard:
      {
        break;
      }
    case hid::mouse:
      {
        break;
      }
    case hid::joystick:
      {
        break;
      }
    default:
      {
      }
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>
    ::GetTotalHID(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch(a_inputType)
    {
    case hid::keyboard:
      {
        return m_winHIDs[hid::keyboard].size();
        break;
      }
    case hid::mouse:
      {
        return m_winHIDs[hid::mouse].size();
        break;
      }
    case hid::joystick:
      {
        return m_winHIDs[hid::joystick].size();
        break;
      }
    default:
      {
        // LOG: Unsupported HID request
        return 0;
      }
    }
  }

  //------------------------------------------------------------------------
  // Platform specific methods

  template <INPUT_MANAGER_IMPL_TEMP>
  HWND InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::GetWindowHandle()
  {
    return m_params.m_param1;
  }

  //------------------------------------------------------------------------
  // Private methods

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::DoEnumerateDevices()
  {
    m_directInput->EnumDevices(NULL, &this_type::DoEnumerateCallback, this,
                               DIEDFL_ATTACHEDONLY);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  BOOL InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    DoEnumerateCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
  {
    this_type* inputMgr = static_cast<this_type*>(pvRef);

    InputDeviceInfo info;
    info.m_productGuid = lpddi->guidProduct;
    info.m_deviceGuid  = lpddi->guidInstance;
    info.m_deviceName  = lpddi->tszInstanceName;

    if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_KEYBOARD)
    {
      inputMgr->m_winHIDs[hid::keyboard].push_back(core::MakePair(false, info));
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_MOUSE)
    {
      inputMgr->m_winHIDs[hid::mouse].push_back(core::MakePair(false, info));
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_JOYSTICK ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_GAMEPAD ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_1STPERSON ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_DRIVING ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_FLIGHT)
    {
      inputMgr->m_winHIDs[hid::joystick].push_back(core::MakePair(false, info));
    }

    return DIENUM_CONTINUE;
  }

};};};