#include "tlocInputImplIphone.h"

#include <tlocCore/types/tlocAny.inl>

#include <tlocInput/hid/tlocKeyboardImplIphone.h>
#include <tlocInput/hid/tlocMouseImplIphone.h>
#include <tlocInput/hid/tlocTouchSurfaceImplIphone.h>

#import <UIKit/UIkit.h>
#import <tlocGraphics/window/tlocOpenGLViewIphone.h>

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < p_hid::Count::m_index,\
  "Unsupported input type passed!")

  namespace {

    template <typename T_InputObject, tl_int T_Index>
    struct DoCreateHID
    {
      T_InputObject* Create(parameter_options::Type,
                            input_param_type)
      {
        TLOC_STATIC_ASSERT_FALSE(T_InputObject,
                                 Unsupported_input_type_selected);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Keyboard::m_index>
    {
      T_InputObject* Create(parameter_options::Type,
                            input_param_type)
      {
        iphone_keyboard_param_type params;
        return new T_InputObject(params);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Mouse::m_index>
    {
      T_InputObject* Create(parameter_options::Type,
                            input_param_type)
      {
        iphone_mouse_param_type params;
        return new T_InputObject(params);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Joystick::m_index>
    {
      T_InputObject* Create(parameter_options::Type,
                            input_param_type)
      {
        TLOC_ASSERT_WIP();
        return nullptr;
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::TouchSurface::m_index>
    {
      T_InputObject* Create(parameter_options::Type a_params,
                            input_param_type a_inputManagerParams)
      {
        UIWindow* window = a_inputManagerParams.m_param1.template Cast<UIWindow*>();

        TLOC_ASSERT([[window subviews] count] != 0,
                    "Window has no views attached");

        core_t::Any viewHandle([[window subviews] lastObject]);

        iphone_touch_surface_param_type params;
        params.m_param1 = viewHandle.template Cast<OpenGLView*>();

        T_InputObject* newInput = new T_InputObject(params);
        return newInput;
      }
    };


//    template <typename T_InputManagerImplType>
//    typename T_InputManagerImplType::view_handle_type
//      DoGetOpenGLViewHandle
//      (typename T_InputManagerImplType::window_handle_type* a_windowHandle)
//    {
//
//      
//      UIWindow* window = a_windowHandle.template Cast<UIWindow*>();
//
//      TLOC_ASSERT([[window subviews] count] != 0,
//                  "Window has no views attached");
//
//      return view_handle_type([[window subviews] lastObject]);
//    }  }
  }

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : base_type(a_parent, a_params)
  {
    for (size_type i = 0; i < p_hid::Count::m_index; ++i)
    {
      m_iphoneHIDs[i].m_available = false;
      m_iphoneHIDs[i].m_devicePtr = nullptr;
    }
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    for (size_type i = 0; i < p_hid::Count::m_index; ++i)
    {
      if (m_iphoneHIDs[i].m_available)
      {
        switch (i)
        {
          case p_hid::Keyboard::m_index:
          {
            break;
          }
          case p_hid::TouchSurface::m_index:
          {
            delete
              static_cast<hid::TouchSurface<policy_type>*>(m_iphoneHIDs[i].m_devicePtr);
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
    if (GetWindowHandle().template Cast<UIWindow*>() == nullptr)
    {
      // LOG: the passed window pointer is not valid
      return 1;
    }
    return 0;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(parameter_options::Type a_params)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);

    T_InputObject* newInput = nullptr;

    if(m_iphoneHIDs[T_InputObject::m_index].m_available == false)
    {
      newInput =
        DoCreateHID<T_InputObject, T_InputObject::m_index>().
        Create(a_params, m_params);

      m_iphoneHIDs[T_InputObject::m_index].m_available = true;
      m_iphoneHIDs[T_InputObject::m_index].m_devicePtr = newInput;
    }
    else
    {
      // LOG: Could not create the specified HID because we do not have a
      //      'slot' for the HID on iOS
    }

    return newInput;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch (a_inputType)
    {
      case p_hid::Keyboard::m_index:
      {
        break;
      }
      case p_hid::TouchSurface::m_index:
      {
        typedef hid::TouchSurface<policy_type> touch_surface_type;

        if (m_iphoneHIDs[p_hid::TouchSurface::m_index].m_available)
        {
          touch_surface_type* ts = static_cast<touch_surface_type*>
              (m_iphoneHIDs[p_hid::TouchSurface::m_index].m_devicePtr);

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
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Reset(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch (a_inputType)
    {
      case p_hid::Keyboard::m_index:
      {
        break;
      }
      case p_hid::TouchSurface::m_index:
      {
        typedef hid::TouchSurface<policy_type> touch_surface_type;

        if (m_iphoneHIDs[p_hid::TouchSurface::m_index].m_available)
        {
          touch_surface_type* ts = static_cast<touch_surface_type*>
            (m_iphoneHIDs[p_hid::TouchSurface::m_index].m_devicePtr);

          ts->Reset();
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
    GetHID(size_type a_index)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<typename T_InputObject::policy_type, policy_type>::value),
       Requested_return_type_has_incorrect_policy_type);

    return static_cast<T_InputObject*>
      (m_iphoneHIDs[T_InputObject::m_index].m_devicePtr);
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetTotalHID(input_type a_inputType)
  {
    ASSERT_INPUT_TYPE(a_inputType);

    switch (a_inputType) {
      case p_hid::Keyboard::m_index:
      {
        return (size_type)m_iphoneHIDs[p_hid::Keyboard::m_index].m_available;
        break;
      }
      case p_hid::TouchSurface::m_index:
      {
        return (size_type)m_iphoneHIDs[p_hid::TouchSurface::m_index].m_available;
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
  INPUT_MANAGER_IMPL_TYPE::window_handle_type
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::GetWindowHandle()
  {
    return m_params.m_param1;
  }
  
  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::view_handle_type
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::DoGetOpenGLViewHandle()
  {
    UIWindow* window = GetWindowHandle().template Cast<UIWindow*>();

    TLOC_ASSERT([[window subviews] count] != 0,
                "Window has no views attached");

    return view_handle_type([[window subviews] lastObject]);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  typedef InputPolicy::Buffered   i_buff;
  typedef InputPolicy::Immediate  i_imm;

  typedef InputManager<i_buff>    i_mgr_buff;
  typedef InputManager<i_imm>     i_mgr_imm;
  
  template class InputManagerImpl<InputManager<InputPolicy::Buffered> >;
  template class InputManagerImpl<InputManager<InputPolicy::Immediate> >;

#define INSTANTIATE_HID(_HID_) \
  template _HID_<i_buff>*  \
  InputManagerImpl<i_mgr_buff >::CreateHID<_HID_<i_buff> >\
  (parameter_options::Type);\
  \
  template _HID_<i_imm>*  \
  InputManagerImpl<i_mgr_imm >::CreateHID<_HID_<i_imm> >\
  (parameter_options::Type);\
  \
  template _HID_<i_buff>*  \
  InputManagerImpl<i_mgr_buff >::GetHID<_HID_<i_buff> >(tl_size);\
  template _HID_<i_imm>*  \
  InputManagerImpl<i_mgr_imm >::GetHID<_HID_<i_imm> >(tl_size)

  INSTANTIATE_HID(hid::Keyboard);
  INSTANTIATE_HID(hid::TouchSurface);
  INSTANTIATE_HID(hid::Mouse);
};};};