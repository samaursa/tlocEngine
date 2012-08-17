#include "tlocInputImplIphone.h"

namespace tloc { namespace input { namespace priv {

#define INPUT_MANAGER_IMPL_TEMP   typename T_ParentInputManager
#define INPUT_MANAGER_IMPL_PARAM  T_ParentInputManager
#define INPUT_MANAGER_IMPL_TYPE   typename InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>

#define ASSERT_INPUT_TYPE(x) TLOC_ASSERT((x) < hid::count,\
  "Unsupported input type passed!")

  template class InputManagerImpl<InputManager<InputPolicy::Buffered> >;
  template class InputManagerImpl<InputManager<InputPolicy::Immediate> >;

#define INSTANTIATE_HID(_HID_) \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::CreateHID<_HID_<InputPolicy::Buffered> >(input_type, parameter_options::Type);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::CreateHID<_HID_<InputPolicy::Immediate> >(input_type, parameter_options::Type);\
  \
  template _HID_<InputPolicy::Buffered>*  InputManagerImpl<InputManager<InputPolicy::Buffered> >  ::GetHID<_HID_<InputPolicy::Buffered> >(input_type, tl_size);\
  template _HID_<InputPolicy::Immediate>* InputManagerImpl<InputManager<InputPolicy::Immediate> > ::GetHID<_HID_<InputPolicy::Immediate> >(input_type, tl_size)


  //------------------------------------------------------------------------
  // InputManagerImpl

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    InputManagerImpl(parent_type* a_parent,
                     param_type a_params)
                     : base_type(a_parent, a_params)
  {
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::~InputManagerImpl()
  {
    
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type
    InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Initialize()
  {
    return 0;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    CreateHID(input_type a_inputType, parameter_options::Type a_params)
  {
    return NULL;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  void InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::Update(input_type a_inputType)
  {
    
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  template <typename T_InputObject>
  T_InputObject* InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>::
    GetHID(input_type a_inputType, size_type a_index)
  {
    return NULL;
  }

  template <INPUT_MANAGER_IMPL_TEMP>
  INPUT_MANAGER_IMPL_TYPE::size_type InputManagerImpl<INPUT_MANAGER_IMPL_PARAM>
    ::GetTotalHID(input_type a_inputType)
  {
    return 0;
  }



};};};