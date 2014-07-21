#include "tlocInputImplIphone.h"

#include <tlocCore/types/tlocAny.inl.h>

#include <tlocInput/hid/tlocKeyboardImplIphone.h>
#include <tlocInput/hid/tlocMouseImplIphone.h>
#include <tlocInput/hid/tlocTouchSurfaceImplIphone.h>
#include <tlocinput/hid/tlocJoystickImplIphone.h>

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
      T_InputObject* Create(param_options::value_type,
                            input_param_type)
      {
        TLOC_STATIC_ASSERT_FALSE(T_InputObject,
                                 Unsupported_input_type_selected);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Keyboard::m_index>
    {
      T_InputObject* Create(param_options::value_type,
                            input_param_type)
      {
        iphone_keyboard_param_type params;
        return new T_InputObject(params);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Mouse::m_index>
    {
      T_InputObject* Create(param_options::value_type,
                            input_param_type)
      {
        iphone_mouse_param_type params;
        return new T_InputObject(params);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::Joystick::m_index>
    {
      T_InputObject* Create(param_options::value_type a_params,
                            input_param_type)
      {
        iphone_joystick_param_type params;
        return new T_InputObject(params);
      }
    };

    template <typename T_InputObject>
    struct DoCreateHID<T_InputObject, p_hid::TouchSurface::m_index>
    {
      T_InputObject* Create(param_options::value_type a_params,
                            input_param_type a_inputManagerParams)
      {
        UIWindow* window = a_inputManagerParams.m_param1.template Cast<UIWindow*>();

        TLOC_ASSERT([[window subviews] count] != 0,
                    "Window has no views attached");

        OpenGLView* viewHandle([[window subviews] lastObject]);

        iphone_touch_surface_param_type params;
        params.m_param1 = viewHandle;

        T_InputObject* newInput = new T_InputObject(params);
        return newInput;
      }
    };
  }

  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type& a_parent,
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
            core_t::Any anyHid = m_iphoneHIDs[i].m_devicePtr;

            if (anyHid.IsEmpty()) { break; }

            core_sptr::VirtualPtr<hid::TouchSurface<policy_type> > 
              ptr = anyHid.Cast
              <core_sptr::VirtualPtr<hid::TouchSurface<policy_type> > >();

            core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);
            break;
          }
          case p_hid::Joystick::m_index:
          {
            core_t::Any anyHid = m_iphoneHIDs[i].m_devicePtr;

            if (anyHid.IsEmpty()) { break; }

            core_sptr::VirtualPtr<hid::Joystick_T<policy_type> >
              ptr = anyHid.Cast
              <core_sptr::VirtualPtr<hid::Joystick_T<policy_type> > >();

            core_sptr::algos::virtual_ptr::DeleteAndReset()(ptr);
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
  core_sptr::VirtualPtr<T_InputObject>
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(param_options::value_type a_params)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);

    core_sptr::VirtualPtr<T_InputObject> newInput;

    if(m_iphoneHIDs[T_InputObject::m_index].m_available == false)
    {
      newInput.reset
        (DoCreateHID<T_InputObject, T_InputObject::m_index>().
         Create(a_params, m_params));

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
        typedef hid::TouchSurface<policy_type>            touch_surface_type;
        typedef core_sptr::VirtualPtr<touch_surface_type> touch_surface_ptr;

        if (m_iphoneHIDs[touch_surface_type::m_index].m_available)
        {
          touch_surface_ptr ts = m_iphoneHIDs[touch_surface_type::m_index]
            .m_devicePtr.template Cast<touch_surface_ptr>();
          ts->Update();
        }
        break;
      }
      case p_hid::Joystick::m_index:
      {
        typedef hid::Joystick_T<policy_type>              joystick_type;
        typedef core_sptr::VirtualPtr<joystick_type>      joystick_ptr;

        if (m_iphoneHIDs[joystick_type::m_index].m_available)
        {
          joystick_ptr js = m_iphoneHIDs[joystick_type::m_index]
            .m_devicePtr.template Cast<joystick_ptr>();
          js->Update();
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
        typedef hid::TouchSurface<policy_type>            touch_surface_type;
        typedef core_sptr::VirtualPtr<touch_surface_type> touch_surface_ptr;

        if (m_iphoneHIDs[p_hid::TouchSurface::m_index].m_available)
        {
          touch_surface_ptr ts = m_iphoneHIDs[p_hid::TouchSurface::m_index]
            .m_devicePtr.template Cast<touch_surface_ptr>();
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
  core_sptr::VirtualPtr<T_InputObject>
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetHID(size_type a_index)
  {
    ASSERT_INPUT_TYPE(T_InputObject::m_index);

    // Make sure the user has the correct policy type, if not, tell them
    TLOC_STATIC_ASSERT
      ( (Loki::IsSameType<typename T_InputObject::policy_type, policy_type>::value),
       Requested_return_type_has_incorrect_policy_type);

    return m_iphoneHIDs[T_InputObject::m_index].m_devicePtr
      .template Cast<core_sptr::VirtualPtr<T_InputObject> >();
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
      case p_hid::Joystick::m_index:
      {
        return (size_type)m_iphoneHIDs[p_hid::Keyboard::m_index].m_available;
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
  template core_sptr::VirtualPtr<_HID_<i_buff> >  \
  InputManagerImpl<i_mgr_buff >::CreateHID<_HID_<i_buff> >\
  (param_options::value_type);\
  \
  template core_sptr::VirtualPtr<_HID_<i_imm> >  \
  InputManagerImpl<i_mgr_imm >::CreateHID<_HID_<i_imm> >\
  (param_options::value_type);\
  \
  template core_sptr::VirtualPtr<_HID_<i_buff> >  \
  InputManagerImpl<i_mgr_buff >::GetHID<_HID_<i_buff> >(tl_size);\
  \
  template core_sptr::VirtualPtr<_HID_<i_imm> >  \
  InputManagerImpl<i_mgr_imm >::GetHID<_HID_<i_imm> >(tl_size)

  INSTANTIATE_HID(hid::Keyboard);
  INSTANTIATE_HID(hid::TouchSurface);
  INSTANTIATE_HID(hid::Mouse);
  INSTANTIATE_HID(hid::Joystick_T);
};};};
