#include "tlocKeyboard.h"

#include <tlocCore/types/tlocTypes.inl>

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_OS_WIN)
# include <tlocInput/hid/tlocKeyboardImplWin.h>
#elif defined (TLOC_OS_IPHONE)
# include <tlocInput/hid/tlocKeyboardImplIphone.h>
#else
# error "WIP"
#endif

namespace tloc { namespace input {

#define KEYBOARD_TEMP   typename T_Policy, typename T_Platform
#define KEYBOARD_PARAMS T_Policy, T_Platform
#define KEYBOARD_TYPE   typename Keyboard<KEYBOARD_PARAMS>

  //------------------------------------------------------------------------
  // Method definitions

  template <KEYBOARD_TEMP>
  template <typename T_ParamList>
  Keyboard<KEYBOARD_PARAMS>::Keyboard(const T_ParamList& a_paramList)
  {
    m_impl = new impl_type(this, a_paramList);
  }

  template <KEYBOARD_TEMP>
  Keyboard<KEYBOARD_PARAMS>::~Keyboard()
  {
    delete m_impl;
  }

  template <KEYBOARD_TEMP>
  bool Keyboard<KEYBOARD_PARAMS>::IsKeyDown(keycode_type a_key) const
  {
    return m_impl->IsKeyDown(a_key);
  }

  template <KEYBOARD_TEMP>
  bool Keyboard<KEYBOARD_PARAMS>::IsModifierDown(modifier_type a_mod) const
  {
    return m_impl->IsModifierDown(a_mod);
  }

  template <KEYBOARD_TEMP>
  void Keyboard<KEYBOARD_PARAMS>::SendOnKeyPress(const KeyboardEvent& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnKeyPress( (tl_size)this, a_event) == true)
      {
        return;
      }
    }
  }

  template <KEYBOARD_TEMP>
  void Keyboard<KEYBOARD_PARAMS>::SendOnKeyRelease(const KeyboardEvent& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnKeyRelease( (tl_size)this, a_event) == true)
      {
        return;
      }
    }
  }

  template <KEYBOARD_TEMP>
  void Keyboard<KEYBOARD_PARAMS>::Update()
  {
    m_impl->Update();
  }

  //------------------------------------------------------------------------
  // Forward Instantiations

  template class Keyboard<InputPolicy::Buffered>;
  template class Keyboard<InputPolicy::Immediate>;

  //------------------------------------------------------------------------
  // Force instantiate the constructor for each platform
#if defined(TLOC_OS_WIN)
  template Keyboard<InputPolicy::Buffered>::Keyboard(const windows_keyboard_param_type&);
  template Keyboard<InputPolicy::Immediate>::Keyboard(const windows_keyboard_param_type&);
#elif defined (TLOC_OS_IPHONE)
  template Keyboard<InputPolicy::Buffered>::Keyboard(const iphone_keyboard_param_type&);
  template Keyboard<InputPolicy::Immediate>::Keyboard(const iphone_keyboard_param_type&);
#else
# error TODO
#endif

};};