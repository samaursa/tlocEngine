#include "tlocInputImplIphone.h"

#include <tlocInput/HIDs/tlocKeyboardImplIphone.h>
#include <tlocInput/HIDs/tlocTouchSurfaceImplIphone.h>

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < hid::count,\
  "Unsupported input type passed!")

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : base_type(a_parent, a_params)
  {
    for (size_type i = 0; i < hid::count; ++i)
    {
      m_iphoneHIDs[i].m_available = false;
      m_iphoneHIDs[i].m_devicePtr = NULL;
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    for (size_type i = 0; i < hid::count; ++i)
    {
      if (m_iphoneHIDs[i].m_available)
      {
        switch (i)
        {
          case hid::keyboard:
          {
            break;
          }
          case hid::touch_surface:
          {
            delete
              static_cast<TouchSurface<policy_type>*>(m_iphoneHIDs[i].m_devicePtr);
            break;
          }

          default: break;
        }
      }
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Initialize()
  {
    if (GetWindowHandle() == NULL)
    {
      // LOG: the passed window pointer is not valid
      return 1;
    }
    return 0;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(input_type a_inputType, parameter_options::Type a_params)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    T_InputObject* newInput = NULL;

    switch (a_inputType)
    {
      case hid::keyboard:
      {
        break;
      }
      case hid::touch_surface:
      {
        iphone_touch_surface_param_type params;
        params.m_param1 = DoGetOpenGLViewHandle();

        if (m_iphoneHIDs[hid::touch_surface].m_available == false)
        {
          newInput = new T_InputObject(params);
          m_iphoneHIDs[hid::touch_surface].m_available = true;
          m_iphoneHIDs[hid::touch_surface].m_devicePtr = newInput;
        }
        break;
      }
      default:
      {
        return NULL;
        break;
      }
    }

    return newInput;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch (a_inputType)
    {
      case hid::keyboard:
      {
        break;
      }
      case hid::touch_surface:
      {
        typedef TouchSurface<policy_type> touch_surface_type;

        if (m_iphoneHIDs[hid::touch_surface].m_available)
        {
          touch_surface_type* ts =
            static_cast<touch_surface_type*>(m_iphoneHIDs[hid::touch_surface].m_devicePtr);

          ts->Update();
        }
        break;
      }
      default:
      {
        break;
      }
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetHID(input_type a_inputType, size_type a_index)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<typename T_InputObject::policy_type, policy_type>::value),
       Requested_return_type_has_incorrect_policy_type);

    return static_cast<T_InputObject*>(m_iphoneHIDs[a_inputType].m_devicePtr);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetTotalHID(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch (a_inputType) {
      case hid::keyboard:
      {
        return (size_type)m_iphoneHIDs[hid::keyboard].m_available;
        break;
      }
      case hid::touch_surface:
      {
        return (size_type)m_iphoneHIDs[hid::touch_surface].m_available;
        break;
      }

      default:
      {
        // LOG: Unsupported HID request
        return 0;
        break;
      }
    }
  }
  
  //------------------------------------------------------------------------
  // Platform specific methods
  
  template <INPUT_MANAGER_IMPL_TEMP>
  UIWindow* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::GetWindowHandle()
  {
    return m_params.m_param1;
  }
  
  template <INPUT_MANAGER_IMPL_TEMP>
  OpenGLView* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::DoGetOpenGLViewHandle()
  {
    TLOC_ASSERT([[GetWindowHandle() subviews] count] != 0,
                "Window has no views attached");
    return static_cast<OpenGLView*>([[GetWindowHandle() subviews] lastObject]);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations
  
  template class InputManagerImpl<InputManager<InputPolicy::Buffered> >;
  template class InputManagerImpl<InputManager<InputPolicy::Immediate> >;

#define INSTANTIATE_HID(_HID_) \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::CreateHID<_HID_<InputPolicy::Buffered> >(input_type, parameter_options::Type);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::CreateHID<_HID_<InputPolicy::Immediate> >(input_type, parameter_options::Type);\
  \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::GetHID<_HID_<InputPolicy::Buffered> >(input_type, tl_size);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::GetHID<_HID_<InputPolicy::Immediate> >(input_type, tl_size)

  INSTANTIATE_HID(Keyboard);
  INSTANTIATE_HID(TouchSurface);

};};};