#include "tlocInputImplWin.h"

#include "tlocCore/tlocArray.inl"
#include "tlocCore/tlocString.inl"
#include "tlocCore/tlocTypeTraits.h"

#include "tlocKeyboardImplWin.h"
#include "tlocMouseImplWin.h"

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < hid::count,\
  "Unsupported input type passed!")

  template InputManagerImpl<InputManager<InputPolicy::Buffered> >;
  template InputManagerImpl<InputManager<InputPolicy::Immediate> >;

#define INSTANTIATE_HID(_HID_) \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::CreateHID<_HID_<InputPolicy::Buffered> >(input_type, parameter_options::Type);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::CreateHID<_HID_<InputPolicy::Immediate> >(input_type, parameter_options::Type);\
  \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::GetHID<_HID_<InputPolicy::Buffered> >(input_type, tl_size);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::GetHID<_HID_<InputPolicy::Immediate> >(input_type, tl_size)

  INSTANTIATE_HID(Keyboard);
  INSTANTIATE_HID(Mouse);

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : InputManagerImplBase(a_parent, a_params)
                     , m_directInput(NULL)
  {
    m_winHIDs.resize(hid::count);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    if (m_directInput)
    {
      m_directInput->Release();
      m_directInput = NULL;
    }

    for (size_type i = 0; i < hid::count; ++i)
    {
      for (size_type hidNum = 0; hidNum < m_winHIDs[i].size(); ++hidNum)
      {
        switch(i)
        {
          case hid::keyboard:
            {
              delete (Keyboard<policy_type>*)m_winHIDs[i][hidNum].m_devicePtr;
            }
          case hid::mouse:
            {
              //delete (Keyboard<policy_type>*)m_winHIDs[i][hidNum];
            }
          case hid::joystick:
            {
              //delete (Keyboard<policy_type>*)m_winHIDs[i][hidNum];
            }
        }
      }
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

    T_InputObject* newInput = NULL;

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
          if (m_winHIDs[hid::keyboard][i].m_available == false)
          {
            newInput = new T_InputObject(params);
            m_winHIDs[hid::keyboard][i].m_available = true;
            m_winHIDs[hid::keyboard][i].m_devicePtr = newInput;
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
        windows_keyboard_param_type params;
        params.m_param1 = m_params.m_param1;
        params.m_param2 = m_directInput;
        params.m_param3 = a_params;

        for (size_type i = 0; i < m_winHIDs[hid::mouse].size(); ++i)
        {
          if (m_winHIDs[hid::mouse][i].m_available == false)
          {
            newInput = new T_InputObject(params);
            m_winHIDs[hid::mouse][i].m_available = true;
            m_winHIDs[hid::mouse][i].m_devicePtr = newInput;
          }
          else
          {
            // LOG: Could not create a keyboard (either one is already created
            //      or we do not have any keyboards attached)
          }
        }
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

    return newInput;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch(a_inputType)
    {
    case hid::keyboard:
      {
        typedef Keyboard<policy_type> keyboard_type;

        for (size_type i = 0; i < m_winHIDs[hid::keyboard].size(); ++i)
        {
          if (m_winHIDs[hid::keyboard][i].m_available)
          {
            keyboard_type* kb = static_cast<keyboard_type*>
                                      (m_winHIDs[hid::keyboard][i].m_devicePtr);
            kb->Update();
          }
        }
        break;
      }
    case hid::mouse:
      {
        typedef Mouse<policy_type> mouse_type;

        for (size_type i = 0; i < m_winHIDs[hid::mouse].size(); ++i)
        {
          if (m_winHIDs[hid::mouse][i].m_available)
          {
            mouse_type* mse = static_cast<mouse_type*>
                                        (m_winHIDs[hid::mouse][i].m_devicePtr);
            mse->Update();
          }
        }
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
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetHID(input_type a_inputType, size_type a_index)
  {
    ASSERT_INPUT_TYPE(a_inputType);
    TLOC_ASSERT(a_index < m_winHIDs[a_inputType].size(), "Index out of range!");

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<T_InputObject::policy_type, policy_type>::value),
         Requested_return_type_has_incorrect_policy_type );

    return static_cast<T_InputObject*>
      (m_winHIDs[a_inputType][a_index].m_devicePtr);
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
    info.m_available   = false;

    if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_KEYBOARD)
    {
      inputMgr->m_winHIDs[hid::keyboard].push_back(info);
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_MOUSE)
    {
      inputMgr->m_winHIDs[hid::mouse].push_back(info);
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_JOYSTICK ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_GAMEPAD ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_1STPERSON ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_DRIVING ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_FLIGHT)
    {
      inputMgr->m_winHIDs[hid::joystick].push_back(info);
    }

    return DIENUM_CONTINUE;
  }

};};};