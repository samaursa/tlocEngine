#include "tlocMouse.h"

#include <tlocCore/types/tlocTypes.inl>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl>

//------------------------------------------------------------------------
// Platform dependent includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include <tlocInput/hid/tlocMouseImplWin.h>
#else
# error "WIP"
#endif

namespace tloc { namespace input {

#define MOUSE_TEMP   typename T_Policy, typename T_Platform
#define MOUSE_PARAMS T_Policy, T_Platform
#define MOUSE_TYPE   typename Mouse<MOUSE_PARAMS>

  template Mouse<InputPolicy::Buffered>;
  template Mouse<InputPolicy::Immediate>;

  // Force instantiate the constructor for each platform
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
  template Mouse<InputPolicy::Buffered>::Mouse(const windows_mouse_param_type&);
  template Mouse<InputPolicy::Immediate>::Mouse(const windows_mouse_param_type&);
#else
# error TODO
#endif

  //------------------------------------------------------------------------
  // Method definitions

  template <MOUSE_TEMP>
  template <typename T_ParamList>
  Mouse<MOUSE_PARAMS>::Mouse(const T_ParamList& a_paramList)
  {
    m_impl.reset(new impl_type(this, a_paramList));
  }

  template <MOUSE_TEMP>
  Mouse<MOUSE_PARAMS>::~Mouse()
  { }

  template <MOUSE_TEMP>
  bool Mouse<MOUSE_PARAMS>::IsButtonDown(button_code_type a_button)
  {
    return m_impl->IsButtonDown(a_button);
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::SendOnButtonPress(const MouseEvent& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnButtonPress( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::SendOnButtonRelease(const MouseEvent& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnButtonRelease( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::SendOnMouseMove(const MouseEvent& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnMouseMove( (tl_size)this, a_event) == true)
      {
        break;
      }
    }
  }

  template <MOUSE_TEMP>
  void Mouse<MOUSE_PARAMS>::Update()
  {
    m_impl->Update();
  }

};};