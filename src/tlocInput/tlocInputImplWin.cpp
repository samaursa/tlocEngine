#include "tlocInputImplWin.h"

#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/string/tlocString.inl>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocInput/hid/tlocKeyboardImplWin.h>
#include <tlocInput/hid/tlocMouseImplWin.h>

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < p_hid::Count::m_index,\
  "Unsupported input type passed!")

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : InputManagerImplBase(a_parent, a_params)
                     , m_directInput(NULL)
  {
    m_winHIDs.resize(p_hid::Count::m_index);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    if (m_directInput)
    {
      m_directInput->Release();
      m_directInput = NULL;
    }

    for (size_type hidIndex = 0; hidIndex < p_hid::Count::m_index; ++hidIndex)
    {
      for (size_type hidNum = 0; hidNum < m_winHIDs[hidIndex].size(); ++hidNum)
      {
        switch(hidIndex)
        {
          case p_hid::Keyboard::m_index:
            {
              delete static_cast<Keyboard<policy_type>* >
                (m_winHIDs[hidIndex][hidNum].m_devicePtr);
              break;
            }
          case p_hid::Mouse::m_index:
            {
              delete static_cast<Mouse<policy_type>* >
                (m_winHIDs[hidIndex][hidNum].m_devicePtr);
              break;
            }
          case p_hid::Joystick::m_index:
            {
              //delete (Keyboard<policy_type>*)m_winHIDs[i][hidNum];
              break;
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
    CreateHID(parameter_options::Type a_params)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);

    T_InputObject* newInput = NULL;

    switch(T_InputObject::m_index)
    {
    case p_hid::Keyboard::m_index:
      {
        windows_keyboard_param_type params;
        params.m_param1 = m_params.m_param1;
        params.m_param2 = m_directInput;
        params.m_param3 = a_params;

        for (size_type i = 0; i < m_winHIDs[p_hid::Keyboard::m_index].size(); ++i)
        {
          if (m_winHIDs[p_hid::Keyboard::m_index][i].m_available == false)
          {
            newInput = new T_InputObject(params);
            m_winHIDs[p_hid::Keyboard::m_index][i].m_available = true;
            m_winHIDs[p_hid::Keyboard::m_index][i].m_devicePtr = newInput;
          }
          else
          {
            // LOG: Could not create a keyboard (either one is already created
            //      or we do not have any keyboards attached)
          }
        }
        break;
      }
    case p_hid::Mouse::m_index:
      {
        windows_keyboard_param_type params;
        params.m_param1 = m_params.m_param1;
        params.m_param2 = m_directInput;
        params.m_param3 = a_params;

        for (size_type i = 0; i < m_winHIDs[p_hid::Mouse::m_index].size(); ++i)
        {
          if (m_winHIDs[p_hid::Mouse::m_index][i].m_available == false)
          {
            newInput = new T_InputObject(params);
            m_winHIDs[p_hid::Mouse::m_index][i].m_available = true;
            m_winHIDs[p_hid::Mouse::m_index][i].m_devicePtr = newInput;
          }
          else
          {
            // LOG: Could not create a keyboard (either one is already created
            //      or we do not have any keyboards attached)
          }
        }
        break;
      }
    case p_hid::Joystick::m_index:
      {
        // LOG: No joystick support yet
        break;
      }
    default:
      {
        // LOG: Unsupported input type selected
        return NULL;
      }
    }

    return newInput;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    typedef p_hid::Keyboard     keyboard_type;
    typedef p_hid::Mouse        mouse_type;
    typedef p_hid::Joystick     joystick_type;

    switch(a_inputType)
    {
    case keyboard_type::m_index:
      {
        typedef Keyboard<policy_type> keyboard_type;

        for (size_type i = 0; i < m_winHIDs[keyboard_type::m_index].size(); ++i)
        {
          if (m_winHIDs[keyboard_type::m_index][i].m_available)
          {
            keyboard_type* kb = static_cast<keyboard_type*>
              (m_winHIDs[keyboard_type::m_index][i].m_devicePtr);
            kb->Update();
          }
        }
        break;
      }
    case mouse_type::m_index:
      {
        typedef Mouse<policy_type> mouse_type;

        for (size_type i = 0; i < m_winHIDs[mouse_type::m_index].size(); ++i)
        {
          if (m_winHIDs[mouse_type::m_index][i].m_available)
          {
            mouse_type* mse = static_cast<mouse_type*>
              (m_winHIDs[mouse_type::m_index][i].m_devicePtr);
            mse->Update();
          }
        }
        break;
      }
    case joystick_type::m_index:
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
    GetHID(size_type a_index)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);
    TLOC_ASSERT(a_index < m_winHIDs[T_InputObject::m_index].size(),
                "Index out of range!");

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<T_InputObject::policy_type, policy_type>::value),
         Requested_return_type_has_incorrect_policy_type );

    return static_cast<T_InputObject*>
      (m_winHIDs[T_InputObject::m_index][a_index].m_devicePtr);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>
    ::GetTotalHID(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch(a_inputType)
    {
    case p_hid::Keyboard::m_index:
      {
        return m_winHIDs[p_hid::Keyboard::m_index].size();
        break;
      }
    case p_hid::Mouse::m_index:
      {
        return m_winHIDs[p_hid::Mouse::m_index].size();
        break;
      }
    case p_hid::Joystick::m_index:
      {
        return m_winHIDs[p_hid::Joystick::m_index].size();
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
    info.m_devicePtr   = nullptr;

    if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_KEYBOARD)
    {
      inputMgr->m_winHIDs[p_hid::Keyboard::m_index].push_back(info);
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_MOUSE)
    {
      inputMgr->m_winHIDs[p_hid::Mouse::m_index].push_back(info);
    }
    else if( GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_JOYSTICK ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_GAMEPAD ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_1STPERSON ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_DRIVING ||
             GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_FLIGHT)
    {
      inputMgr->m_winHIDs[p_hid::Joystick::m_index].push_back(info);
    }

    return DIENUM_CONTINUE;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit Instantiations

  typedef InputPolicy::Buffered     i_buff;
  typedef InputPolicy::Immediate    i_imm;

  typedef InputManager<i_buff>      i_mgr_buff;
  typedef InputManager<i_imm>       i_mgr_imm;

  template class InputManagerImpl<i_mgr_buff>;
  template class InputManagerImpl<i_mgr_imm >;

#define INSTANTIATE_HID(_HID_) \
  template _HID_<i_buff>*  \
  InputManagerImpl<i_mgr_buff>::CreateHID<_HID_<i_buff> >\
  (parameter_options::Type);\
  \
  template _HID_<i_imm>* \
  InputManagerImpl<i_mgr_imm >::CreateHID<_HID_<i_imm> >\
  (parameter_options::Type);\
  \
  template _HID_<i_buff>*  \
  InputManagerImpl<i_mgr_buff>::GetHID<_HID_<i_buff> >(tl_size);\
  template _HID_<i_imm>* \
  InputManagerImpl<i_mgr_imm >::GetHID<_HID_<i_imm> >(tl_size)

  INSTANTIATE_HID(Keyboard);
  INSTANTIATE_HID(Mouse);


};};};