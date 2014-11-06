#include "tlocInputImplWin.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/types/tlocAny.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/string/tlocString.inl.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocInput/hid/tlocKeyboardImplWin.h>
#include <tlocInput/hid/tlocMouseImplWin.h>
#include <tlocInput/hid/tlocJoystickImplWin.h>
#include <tlocInput/hid/tlocTouchSurfaceImplWin.h>

namespace tloc { namespace input { namespace priv {

  //------------------------------------------------------------------------

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

  //------------------------------------------------------------------------
  // Free functions and definitions

  namespace {

    template <typename T_InputObject, tl_int T_Index>
    struct DoCreateHID
    {
      T_InputObject* 
        Create(param_options::value_type a_params, 
               IDirectInput8* a_directInput, InputDeviceInfo a_info, 
               input_param_type a_inputManagerParams)
      {
        TLOC_LOG_INPUT_ERR() << "Unsupported input type selected";
        TLOC_UNUSED_3(a_params, a_directInput, a_inputManagerParams);
        TLOC_STATIC_ASSERT_FALSE(T_InputObject, Unsupported_input_type_selected);
        return nullptr;
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Keyboard::m_index>
    {
      T_InputObject* 
        Create(param_options::value_type a_params, 
               IDirectInput8* a_directInput, InputDeviceInfo a_info, 
               input_param_type a_inputManagerParams)
      {
        TLOC_UNUSED(a_params);
        windows_keyboard_param_type params;
        params.m_param1 = a_inputManagerParams.m_param1.Cast<HWND>();
        params.m_param2 = a_directInput;
        params.m_param3 = a_info;
        params.m_param4 = a_params;

        T_InputObject* newInput = new T_InputObject(params);

        return newInput;
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Mouse::m_index>
    {
      T_InputObject* 
        Create(param_options::value_type a_params, 
               IDirectInput8* a_directInput, InputDeviceInfo a_info, 
               input_param_type a_inputManagerParams)
      {
        TLOC_UNUSED(a_params);
        windows_mouse_param_type params;
        params.m_param1 = a_inputManagerParams.m_param1.Cast<HWND>();
        params.m_param2 = a_directInput;
        params.m_param3 = a_info;
        params.m_param4 = a_params;

        T_InputObject* newInput = new T_InputObject(params);

        return newInput;
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Joystick::m_index>
    {
      T_InputObject* 
        Create(param_options::value_type a_params, 
               IDirectInput8* a_directInput, InputDeviceInfo a_info, 
               input_param_type a_inputManagerParams)
      {
        TLOC_UNUSED(a_params);
        windows_joystick_param_type params;
        params.m_param1 = a_inputManagerParams.m_param1.Cast<HWND>();
        params.m_param2 = a_directInput;
        params.m_param3 = a_info;
        params.m_param4 = a_params;

        T_InputObject* newInput = new T_InputObject(params);

        return newInput;
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::TouchSurface::m_index>
    {
      T_InputObject* 
        Create(param_options::value_type a_params, 
               IDirectInput8* a_directInput, InputDeviceInfo a_info, 
               input_param_type a_inputManagerParams)
      {
        TLOC_UNUSED_3(a_params, a_directInput, a_inputManagerParams);
        win_touch_surface_param_type params;
        return new T_InputObject(params);
      }
    };

  };

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < p_hid::Count::m_index,\
  "Unsupported input type passed!")

#define STATIC_ASSERT_INPUT_TYPE(x) TLOC_STATIC_ASSERT((x) < p_hid::Count::m_index,\
  Unsupported_input_type_passed)

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type& a_parent,
                     param_type a_params)
                     : InputManagerImplBase(a_parent, a_params)
                     , m_directInput(TLOC_NULL)
  {
    m_winHIDs.resize(p_hid::Count::m_index);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    if (m_directInput)
    {
      m_directInput->Release();
      m_directInput = TLOC_NULL;
    }

    for (size_type hidIndex = 0; hidIndex < p_hid::Count::m_index; ++hidIndex)
    {
      for (size_type hidNum = 0; hidNum < m_winHIDs[hidIndex].size(); ++hidNum)
      {
        switch(hidIndex)
        {
          case p_hid::Keyboard::m_index:
            {
              core_t::Any anyHid = m_winHIDs[hidIndex][hidNum].m_devicePtr;

              if (anyHid.IsEmpty()) { break; }

              core_sptr::VirtualPtr<hid::Keyboard<policy_type> > 
                ptr = anyHid.Cast
                <core_sptr::VirtualPtr<hid::Keyboard<policy_type> > >();

              core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);

              break;
            }
          case p_hid::Mouse::m_index:
            {
              core_t::Any anyHid = m_winHIDs[hidIndex][hidNum].m_devicePtr;

              if (anyHid.IsEmpty()) { break; }

              core_sptr::VirtualPtr<hid::Mouse<policy_type> > 
                ptr = anyHid.Cast
                <core_sptr::VirtualPtr<hid::Mouse<policy_type> > >();

              core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);

              break;
            }
          case p_hid::Joystick::m_index:
            {
              core_t::Any anyHid = m_winHIDs[hidIndex][hidNum].m_devicePtr;

              if (anyHid.IsEmpty()) { break; }

              core_sptr::VirtualPtr<hid::Joystick_T<policy_type> > 
                ptr = anyHid.Cast
                <core_sptr::VirtualPtr<hid::Joystick_T<policy_type> > >();

              core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);

              break;
            }
          case p_hid::TouchSurface::m_index:
            {
              core_t::Any anyHid = m_winHIDs[hidIndex][hidNum].m_devicePtr;

              if (anyHid.IsEmpty()) { break; }

              core_sptr::VirtualPtr<hid::TouchSurface<policy_type> > 
                ptr = anyHid.Cast
                <core_sptr::VirtualPtr<hid::TouchSurface<policy_type> > >();

              core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);

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
    HINSTANCE hInst = TLOC_NULL;
    HRESULT hr;

    if (IsWindow(m_params.m_param1.Cast<HWND>()) == 0)
    {
      TLOC_LOG_INPUT_ERR() << "The passed window handle is not valid";
      return 1;
    }

    hInst = GetModuleHandle(TLOC_NULL);

    // Create the input device
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
                            (VOID**)&m_directInput, TLOC_NULL);
    if (FAILED(hr))
    {
      TLOC_LOG_INPUT_ERR() << "Unable to initialize direct input";
      return 1;
    }

    DoEnumerateDevices();
    return 0;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  core_sptr::VirtualPtr<T_InputObject>  
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(param_options::value_type a_params)
  {
    STATIC_ASSERT_INPUT_TYPE(T_InputObject::m_index);

    core_sptr::VirtualPtr<T_InputObject> newInput;

    for (size_type i = 0; i < m_winHIDs[T_InputObject::m_index].size(); ++i)
    {
      auto& deviceInfo = m_winHIDs[T_InputObject::m_index][i];

      if (deviceInfo.m_inUse == false)
      {
        newInput.reset
          (DoCreateHID<T_InputObject, T_InputObject::m_index>()
          .Create(a_params, m_directInput, deviceInfo, m_params));

        deviceInfo.m_inUse = true;
        deviceInfo.m_devicePtr = newInput;

        break;
      }
    }

    TLOC_LOG_INPUT_WARN_IF(newInput == nullptr) 
      << "Could not create the requested input device";

    return newInput;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    typedef p_hid::Keyboard       keyboard_type;
    typedef p_hid::Mouse          mouse_type;
    typedef p_hid::Joystick       joystick_type;
    typedef p_hid::TouchSurface   touch_surface_type;

    switch(a_inputType)
    {
    case keyboard_type::m_index:
      {
        typedef hid::Keyboard<policy_type>            keyboard_type;
        typedef core_sptr::VirtualPtr<keyboard_type>  keyboard_ptr;

        for (size_type i = 0; i < m_winHIDs[keyboard_type::m_index].size(); ++i)
        {
          if (m_winHIDs[keyboard_type::m_index][i].m_inUse)
          {
            keyboard_ptr kb = m_winHIDs[keyboard_type::m_index][i].m_devicePtr
              .Cast<keyboard_ptr>();
            kb->Update();
          }
        }
        break;
      }
    case mouse_type::m_index:
      {
        typedef hid::Mouse<policy_type>               mouse_type;
        typedef core_sptr::VirtualPtr<mouse_type>     mouse_ptr;

        for (size_type i = 0; i < m_winHIDs[mouse_type::m_index].size(); ++i)
        {
          if (m_winHIDs[mouse_type::m_index][i].m_inUse)
          {
            mouse_ptr mse = m_winHIDs[mouse_type::m_index][i].m_devicePtr
              .Cast<mouse_ptr>();
            mse->Update();
          }
        }
        break;
      }
    case joystick_type::m_index:
      {
        typedef hid::Joystick_T<policy_type>            joystick_type;
        typedef core_sptr::VirtualPtr<joystick_type>    joystick_ptr;

        for (size_type i = 0; i < m_winHIDs[joystick_type::m_index].size(); ++i)
        {
          if (m_winHIDs[joystick_type::m_index][i].m_inUse)
          {
            joystick_ptr js = m_winHIDs[joystick_type::m_index][i].m_devicePtr
              .Cast<joystick_ptr>();
            js->Update();
          }
        }

        break;
      }
    case touch_surface_type::m_index:
      {
        break;
      }
    default:
      {
      }
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Reset(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    typedef p_hid::Keyboard       keyboard_type;
    typedef p_hid::Mouse          mouse_type;
    typedef p_hid::Joystick       joystick_type;
    typedef p_hid::TouchSurface   touch_surface_type;

    switch(a_inputType)
    {
    case keyboard_type::m_index:
      {
        typedef hid::Keyboard<policy_type>            keyboard_type;
        typedef core_sptr::VirtualPtr<keyboard_type>  keyboard_ptr;

        for (size_type i = 0; i < m_winHIDs[keyboard_type::m_index].size(); ++i)
        {
          if (m_winHIDs[keyboard_type::m_index][i].m_inUse)
          {
            keyboard_ptr kb = m_winHIDs[keyboard_type::m_index][i].m_devicePtr
              .Cast<keyboard_ptr>();
            kb->Reset();
          }
        }
        break;
      }
    case mouse_type::m_index:
      {
        typedef hid::Mouse<policy_type>               mouse_type;
        typedef core_sptr::VirtualPtr<mouse_type>     mouse_ptr;

        for (size_type i = 0; i < m_winHIDs[mouse_type::m_index].size(); ++i)
        {
          if (m_winHIDs[mouse_type::m_index][i].m_inUse)
          {
            mouse_ptr mse = m_winHIDs[mouse_type::m_index][i].m_devicePtr
              .Cast<mouse_ptr>();
            mse->Reset();
          }
        }
        break;
      }
    case joystick_type::m_index:
      {
        typedef hid::Joystick_T<policy_type>            joystick_type;
        typedef core_sptr::VirtualPtr<joystick_type>    joystick_ptr;

        for (size_type i = 0; i < m_winHIDs[joystick_type::m_index].size(); ++i)
        {
          if (m_winHIDs[joystick_type::m_index][i].m_inUse)
          {
            joystick_ptr js = m_winHIDs[joystick_type::m_index][i].m_devicePtr
              .Cast<joystick_ptr>();
            js->Reset();
          }
        }

        break;
      }
    case touch_surface_type::m_index:
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
  core_sptr::VirtualPtr<T_InputObject>
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetHID(size_type a_index)
  {
    STATIC_ASSERT_INPUT_TYPE(T_InputObject::m_index);
    TLOC_ASSERT(a_index < m_winHIDs[T_InputObject::m_index].size(),
                "Index out of range!");

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<T_InputObject::policy_type, policy_type>::value),
         Requested_return_type_has_incorrect_policy_type );

    return m_winHIDs[T_InputObject::m_index][a_index].m_devicePtr
      .Cast<core_sptr::VirtualPtr<T_InputObject> >();
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
    case p_hid::TouchSurface::m_index:
      {
        return m_winHIDs[p_hid::TouchSurface::m_index].size();
        break;
      }
    default:
      {
        TLOC_LOG_INPUT_ERR() << "Unsupported HID request";
        return 0;
      }
    }
  }

  //------------------------------------------------------------------------
  // Platform specific methods

  template <INPUT_MANAGER_IMPL_TEMP>
  HWND InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::GetWindowHandle()
  {
    return m_params.m_param1.Cast<HWND>();
  }

  //------------------------------------------------------------------------
  // Private methods

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::DoEnumerateDevices()
  {
    m_directInput->EnumDevices(TLOC_NULL, &this_type::DoEnumerateCallback, this,
                               DIEDFL_ATTACHEDONLY);

    // Now add other devices that are dummies such as touch
    InputDeviceInfo dummyInfo;
    dummyInfo.m_productGuid = GUID();
    dummyInfo.m_deviceGuid  = GUID();
    dummyInfo.m_deviceName  = "DummyDevice";
    dummyInfo.m_inUse       = false;
    dummyInfo.m_devicePtr.Reset();

    m_winHIDs[p_hid::TouchSurface::m_index].push_back(dummyInfo);
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
    info.m_inUse       = false;
    info.m_devicePtr.Reset();

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
  template core_sptr::VirtualPtr<_HID_<i_buff> >\
    InputManagerImpl<i_mgr_buff>::CreateHID<_HID_<i_buff> >\
    (param_options::value_type);\
  \
  template core_sptr::VirtualPtr<_HID_<i_imm> >\
    InputManagerImpl<i_mgr_imm >::CreateHID<_HID_<i_imm> >\
    (param_options::value_type);\
  \
  template core_sptr::VirtualPtr<_HID_<i_buff> >  \
    InputManagerImpl<i_mgr_buff>::GetHID<_HID_<i_buff> >(tl_size);\
  template core_sptr::VirtualPtr<_HID_<i_imm> > \
    InputManagerImpl<i_mgr_imm >::GetHID<_HID_<i_imm> >(tl_size)

  INSTANTIATE_HID(hid::Keyboard);
  INSTANTIATE_HID(hid::Mouse);
  INSTANTIATE_HID(hid::TouchSurface);
  INSTANTIATE_HID(hid::Joystick_T);

};};};