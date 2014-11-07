#ifndef TLOC_MOUSE_H
#define TLOC_MOUSE_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/dispatch/tlocTemplateDispatchDefaults.h>
#include <tlocCore/dispatch/tlocEvent.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/tlocRange.h>

#include <tlocInput/tlocInputTypes.h>
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
  public:
    typedef core_dispatch::Event                            event_type;

  public:
    virtual event_type
      OnMouseButtonPress(const tl_size a_caller,
                         const MouseEvent& a_event,
                         const MouseEvent::button_code_type a_buttonCode) const = 0;
    virtual event_type
      OnMouseButtonRelease(const tl_size a_caller,
                           const MouseEvent& a_event,
                           const MouseEvent::button_code_type a_buttonCode) const = 0;
    virtual event_type
      OnMouseMove(const tl_size a_caller, const MouseEvent& a_event) const = 0;
  };

  ///-------------------------------------------------------------------------
  /// This class is for internal use only
  ///
  /// @sa core::CallbackGroupTArray<T, KeyboardCallbacks>::type
  ///-------------------------------------------------------------------------
  template <typename T>
  struct MouseCallbackGroupT:
    public core::dispatch::CallbackGroupTArray<T, MouseCallbacks>::type
  {
  public:
    typedef typename core::dispatch::
      CallbackGroupTArray<T, MouseCallbacks>::type      base_type;

    typedef typename base_type::event_type              event_type;

    using base_type::m_observers;

  public:
    virtual event_type
      OnMouseButtonPress(const tl_size a_caller,
                         const MouseEvent& a_event,
                         const MouseEvent::button_code_type a_buttonCode) const
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->
            OnMouseButtonPress(a_caller, a_event, a_buttonCode).IsVeto())
        {
          return core_dispatch::f_event::Veto();
        }
      }

      return core_dispatch::f_event::Continue();
    }

    virtual event_type
      OnMouseButtonRelease(const tl_size a_caller,
                           const MouseEvent& a_event,
                           const MouseEvent::button_code_type a_buttonCode) const
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->
            OnMouseButtonRelease(a_caller, a_event, a_buttonCode).IsVeto())
        {
          return core_dispatch::f_event::Veto();
        }
      }

      return core_dispatch::f_event::Continue();
    }

    virtual event_type
      OnMouseMove(const tl_size a_caller, const MouseEvent& a_event) const
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnMouseMove(a_caller, a_event).IsVeto())
        {
          return core_dispatch::f_event::Veto();
        }
      }

      return core_dispatch::f_event::Continue();
    }
  };

  ///-------------------------------------------------------------------------
  /// Cross-platform class to handle keyboard input.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core_plat::PlatformInfo::platform_type>
  class Mouse
    : public core::dispatch::DispatcherBaseArray
             <MouseCallbacks, MouseCallbackGroupT>::type
    , public core_bclass::NonCopyable_I
    , public p_hid::Mouse
  {
  public:
    typedef T_Platform                                  platform_type;
    typedef T_Policy                                    policy_type;
    typedef MouseEvent                                  event_type;
    typedef event_type::axis_type::abs_type::value_type abs_value_type;
    typedef math::Range_T<abs_value_type>               abs_range_type;
    typedef event_type::axis_type::rel_type             rel_value_type;
    typedef event_type::button_code_type                button_code_type;

    typedef Mouse<policy_type, platform_type>           this_type;

  public:
    template <typename T_ParamList>
    Mouse(const T_ParamList& a_paramList);
    ~Mouse();

    bool        IsButtonDown(button_code_type a_button) const;
    event_type  GetState() const;

    void SendOnMouseButtonPress(const MouseEvent& a_event,
                                button_code_type a_buttonCode) const;
    void SendOnMouseButtonRelease(const MouseEvent& a_event,
                                  button_code_type a_buttonCode) const;
    void SendOnMouseMove(const MouseEvent& a_event) const;

    void Clamp(event_type& a_event) const;

    ///-------------------------------------------------------------------------
    /// Buffer any keys that were pressed between this and the last update
    ///-------------------------------------------------------------------------
    void Update();
    void Reset();

    TLOC_DECL_AND_DEF_GETTER(bool, IsClamped, m_clamped);
    TLOC_DECL_AND_DEF_SETTER(bool, SetClamped, m_clamped);

    TLOC_DECL_AND_DEF_GETTER(abs_range_type, GetClampX, m_clampX);
    TLOC_DECL_AND_DEF_GETTER(abs_range_type, GetClampY, m_clampY);

    TLOC_DECL_SETTER(abs_range_type, SetClampX);
    TLOC_DECL_SETTER(abs_range_type, SetClampY);

  private:
    typedef priv::MouseImpl<this_type>               impl_type;
    typedef core::smart_ptr::UniquePtr<impl_type>    impl_ptr_type;

  private:

    impl_ptr_type  m_impl;
    abs_range_type m_clampX;
    abs_range_type m_clampY;
    bool           m_clamped;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Mouse<InputPolicy::Buffered>   MouseB;
  typedef Mouse<InputPolicy::Immediate>  MouseI;

  TLOC_TYPEDEF_ALL_SMART_PTRS(MouseB, mouse_b);
  TLOC_TYPEDEF_ALL_SMART_PTRS(MouseI, mouse_i);

};};};

#endif