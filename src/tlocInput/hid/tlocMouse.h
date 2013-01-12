#ifndef TLOC_MOUSE_H
#define TLOC_MOUSE_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocMouse.h>
#include <tlocInput/hid/tlocMouseImpl.h>

namespace tloc { namespace input { namespace hid {

  template <typename T_Policy, typename T_Platform> class Mouse;

  ///-------------------------------------------------------------------------
  /// This class itself is for internal use only.
  ///
  /// If a class is registered with Keyboard to receive callbacks, this class
  /// defines the function signature of the callbacks (Note that the callbacks
  /// in your class need not be virtual)
  ///-------------------------------------------------------------------------
  struct MouseCallbacks
  {
    virtual bool OnButtonPress(const tl_size a_caller,
                               const MouseEvent& a_event) = 0;
    virtual bool OnButtonRelease(const tl_size a_caller,
                                 const MouseEvent& a_event) = 0;
    virtual bool OnMouseMove(const tl_size a_caller,
                             const MouseEvent& a_event) = 0;
  };

  ///-------------------------------------------------------------------------
  /// This class is for internal use only
  ///
  /// @sa core::CallbackGroupTArray<T, KeyboardCallbacks>::type
  ///-------------------------------------------------------------------------
  template <typename T>
  struct MouseCallbackGroupT:
    public core::CallbackGroupTArray<T, MouseCallbacks>::type
  {
    typedef typename core::CallbackGroupTArray<T, MouseCallbacks>::type
      base_type;
    using base_type::m_observers;

    virtual bool OnButtonPress(const tl_size a_caller,
                               const MouseEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnButtonPress(a_caller, a_event) == true)
        {
          return true; // Veto the rest of the events
        }
      }
      return false;
    }

    virtual bool OnButtonRelease(const tl_size a_caller,
                                 const MouseEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnButtonRelease(a_caller, a_event) == false)
        {
          return true; // Veto the rest of the events
        }
      }
      return false;
    }

    virtual bool OnMouseMove(const tl_size a_caller,
                             const MouseEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnMouseMove(a_caller, a_event) == false)
        {
          return true; // Veto the rest of the events
        }
      }
      return false;
    }
  };

  ///-------------------------------------------------------------------------
  /// Platform independent list of parameters. Passing incorrect parameters
  /// will result in compile errors.
  ///-------------------------------------------------------------------------
  template <class T1,
            class T2 = TLOC_DUMMY_PARAM(),
            class T3 = TLOC_DUMMY_PARAM(),
            class T4 = TLOC_DUMMY_PARAM()>
  struct MouseParamList
  {
    T1 m_param1;
    T2 m_param2;
    T3 m_param3;
    T4 m_param4;
  };

  ///-------------------------------------------------------------------------
  /// Cross-platform class to handle keyboard input.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Mouse:
    public core::DispatcherBaseArray <MouseCallbacks, MouseCallbackGroupT>::type,
    public core::NonCopyable,
    public p_hid::Mouse
  {
  public:
    typedef T_Platform                      platform_type;
    typedef T_Policy                        policy_type;
    typedef MouseEvent::button_code_type    button_code_type;

    typedef Mouse<policy_type, platform_type>  this_type;

    template <typename T_ParamList>
    Mouse(const T_ParamList& a_paramList);
    ~Mouse();

    bool IsButtonDown(button_code_type a_button);

    void SendOnButtonPress(const MouseEvent& a_event);
    void SendOnButtonRelease(const MouseEvent& a_event);
    void SendOnMouseMove(const MouseEvent& a_event);

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();

  private:

    typedef priv::MouseImpl<this_type>               impl_type;
    typedef core::smart_ptr::UniquePtr<impl_type>    impl_ptr_type;

    impl_ptr_type  m_impl;
  };

  typedef Mouse<InputPolicy::Buffered>   MouseB;
  typedef Mouse<InputPolicy::Immediate>  MouseI;

};};};

#endif