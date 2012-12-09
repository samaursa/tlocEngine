#include "tlocInput.h"
#include "tlocInputTypes.h"

#include <tlocInput/HIDs/tlocKeyboard.h>
#include <tlocInput/HIDs/tlocMouse.h>
#include <tlocInput/HIDs/tlocJoystick.h>
#include <tlocInput/HIDs/tlocTouchSurface.h>

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_OS_WIN)
# include "tlocInputImplWin.h"
//# include "tlocKeyboardImplWin.h"
//# include "tlocMouseImplWin.h"
#elif defined(TLOC_OS_IPHONE)
# include "tlocInputImplIphone.h"
#else
# error "WIP"
#endif

namespace tloc { namespace input {

#define INPUT_MANAGER_TEMP  typename T_Policy, typename T_Platform
#define INPUT_MANAGER_PARAM T_Policy, T_Platform
#define INPUT_MANAGER_TYPE  typename InputManager<INPUT_MANAGER_PARAM>

  //------------------------------------------------------------------------
  // Method Definitions

  template <INPUT_MANAGER_TEMP>
  template <typename T_ParamList>
  InputManager<INPUT_MANAGER_PARAM>::InputManager(T_ParamList a_paramList)
  {
    m_impl = new impl_type(this, a_paramList);
    m_impl->Initialize();
  }

  template <INPUT_MANAGER_TEMP>
  InputManager<INPUT_MANAGER_PARAM>::~InputManager()
  {
    delete m_impl;
  }

  template <INPUT_MANAGER_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManager<INPUT_MANAGER_PARAM>::
    CreateHID(input_type a_inputType, parameter_options::Type a_params)
  {
    return m_impl->template CreateHID<T_InputObject>(a_inputType, a_params);
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::Update(input_type a_inputType)
  {
    m_impl->Update(a_inputType);
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::Update()
  {
    for (u32 i = 0; i < hid::count; ++i)
    {
      Update(i);
    }
  }

  template <INPUT_MANAGER_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManager<INPUT_MANAGER_PARAM>::
    GetHID(input_type a_inputType, size_type a_index)
  {
    return m_impl->template GetHID<T_InputObject>(a_inputType, a_index);
  }

  template <INPUT_MANAGER_TEMP>
  INPUT_MANAGER_TYPE::size_type
    InputManager<INPUT_MANAGER_PARAM>::GetTotalHID(input_type a_inputType)
  {
    return m_impl->GetTotalHID(a_inputType);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template class InputManager<InputPolicy::Buffered>;
  template class InputManager<InputPolicy::Immediate>;

  //------------------------------------------------------------------------
  // Force instantiate the constructor for each platform
#if defined(TLOC_OS_WIN)
  template InputManager<InputPolicy::Buffered>::InputManager(input_param_type);
  template InputManager<InputPolicy::Immediate>::InputManager(input_param_type);
#elif defined(TLOC_OS_IPHONE)
  template InputManager<InputPolicy::Buffered>::InputManager(input_param_type);
  template InputManager<InputPolicy::Immediate>::InputManager(input_param_type);
#else
# error TODO
#endif

  //------------------------------------------------------------------------
  // Force instantiate CreateHID for all supported types

#define INSTANTIATE_FOR_HID(_HID_, _type_)\
  template class _HID_<_type_::policy_type>* _type_::CreateHID\
  <_HID_<_type_::policy_type> >(input_type, parameter_options::Type);\
  template class _HID_<_type_::policy_type>* _type_::GetHID\
  <_HID_<_type_::policy_type> >(input_type, _type_::size_type );\

#if defined(TLOC_OS_WIN)
  INSTANTIATE_FOR_HID(Keyboard, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(Keyboard, InputManager<InputPolicy::Immediate>);

  INSTANTIATE_FOR_HID(Mouse, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(Mouse, InputManager<InputPolicy::Immediate>);
#elif defined(TLOC_OS_IPHONE)
  INSTANTIATE_FOR_HID(Keyboard, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(Keyboard, InputManager<InputPolicy::Immediate>);
  
  INSTANTIATE_FOR_HID(TouchSurface, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(TouchSurface, InputManager<InputPolicy::Immediate>);
#endif

};};