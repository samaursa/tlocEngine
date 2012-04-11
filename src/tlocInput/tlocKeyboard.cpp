#include "tlocKeyboard.h"

#include "tlocCore/tlocTypes.inl"

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include "tlocKeyboardImplWin.h"
#else
# error "WIP"
#endif

namespace tloc { namespace input {

#define KEYBOARD_TEMP   typename T_Policy, typename T_Platform
#define KEYBOARD_PARAMS T_Policy, T_Platform
#define KEYBOARD_TYPE   typename Keyboard<KEYBOARD_PARAMS>

  template Keyboard<InputPolicy::Buffered>;
  template Keyboard<InputPolicy::UnBuffered>;

  // Force instantiate the constructor for each platform
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
  template Keyboard<InputPolicy::Buffered>::Keyboard(windows_keyboard_param_type);
  template Keyboard<InputPolicy::UnBuffered>::Keyboard(windows_keyboard_param_type);
#else
# error TODO
#endif

  //------------------------------------------------------------------------
  // Method definitions

  template <KEYBOARD_TEMP>
  template <typename T_ParamList>
  Keyboard<KEYBOARD_PARAMS>::Keyboard(T_ParamList a_paramList)
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
  void Keyboard<KEYBOARD_PARAMS>::Update()
  {
    m_impl->Update();
  }

};};