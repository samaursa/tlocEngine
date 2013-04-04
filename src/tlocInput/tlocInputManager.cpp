#include "tlocInputManager.h"
#include "tlocInputTypes.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl>

#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocMouse.h>
#include <tlocInput/hid/tlocJoystick.h>
#include <tlocInput/hid/tlocTouchSurface.h>

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_OS_WIN)
# include "tlocInputImplWin.h"
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
    m_impl.reset(new impl_type(this, a_paramList));
    m_impl->Initialize();
  }

  template <INPUT_MANAGER_TEMP>
  InputManager<INPUT_MANAGER_PARAM>::~InputManager()
  { }

  template <INPUT_MANAGER_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManager<INPUT_MANAGER_PARAM>::
    DoCreateHID(parameter_options::Type a_params)
  {
    return m_impl->template CreateHID<T_InputObject>(a_params);
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::DoUpdate(input_type a_inputType)
  {
    m_impl->Update(a_inputType);
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::Update()
  {
    for (u32 i = 0; i < p_hid::Count::m_index; ++i)
    {
      DoUpdate(i);
    }
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::DoReset(input_type a_inputType)
  {
    m_impl->Reset(a_inputType);
  }

  template <INPUT_MANAGER_TEMP>
  void InputManager<INPUT_MANAGER_PARAM>::Reset()
  {
    for (input_type i = 0; i < p_hid::Count::m_index; ++i)
    {
      DoReset(i);
    }
  }

  template <INPUT_MANAGER_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManager<INPUT_MANAGER_PARAM>::
    DoGetHID(size_type a_index)
  {
    return m_impl->template GetHID<T_InputObject>(a_index);
  }

  template <INPUT_MANAGER_TEMP>
  INPUT_MANAGER_TYPE::size_type
    InputManager<INPUT_MANAGER_PARAM>::DoGetTotalHID(input_type a_inputType)
  {
    return m_impl->GetTotalHID(a_inputType);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template class InputManager<InputPolicy::Buffered>;
  template class InputManager<InputPolicy::Immediate>;

  template class core::smart_ptr::SharedPtr<InputManagerB>;
  template class core::smart_ptr::SharedPtr<InputManagerI>;

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
  // Force instantiate of template methods

#define INSTANTIATE_FOR_HID(_HID_, _type_)\
  template _HID_<_type_::policy_type>* _type_::DoCreateHID\
  <_HID_<_type_::policy_type> >(parameter_options::Type);\
  template _HID_<_type_::policy_type>* _type_::DoGetHID\
  <_HID_<_type_::policy_type> >(_type_::size_type);\

  INSTANTIATE_FOR_HID(hid::Keyboard, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(hid::Keyboard, InputManager<InputPolicy::Immediate>);

  INSTANTIATE_FOR_HID(hid::Mouse, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(hid::Mouse, InputManager<InputPolicy::Immediate>);

  INSTANTIATE_FOR_HID(hid::TouchSurface, InputManager<InputPolicy::Buffered>);
  INSTANTIATE_FOR_HID(hid::TouchSurface, InputManager<InputPolicy::Immediate>);

};};