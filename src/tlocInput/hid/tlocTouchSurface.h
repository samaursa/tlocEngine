//
//  tlocTouchSurface.h
//  tlocInput
//
//  Created by Skopworks Inc on 12-08-25.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TLOC_TOUCH_SURFACE_H
#define TLOC_TOUCH_SURFACE_H

#include <tloccore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/types/tlocTypes.h>
#include <tloccore/containers/tlocContainers.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include <tlocInput/tlocInputTypes.h>
#include <tlocInput/hid/tlocTouchSurfaceImpl.h>

namespace tloc { namespace input { namespace hid {

  template <typename T_Policy, typename T_Platform> class TouchSurface;

  struct TouchSurfaceCallbacks
  {
    virtual bool OnTouchPress(const tl_size a_caller,
                              const TouchSurfaceEvent& a_event) = 0;
    virtual bool OnTouchRelease(const tl_size a_caller,
                                const TouchSurfaceEvent& a_event) = 0;
    virtual bool OnTouchMove(const tl_size a_caller,
                             const TouchSurfaceEvent& a_event) = 0;
  };

  template <typename T>
  struct TouchSurfaceCallbackGroupT
    : public core::base_classes::CallbackGroupTArray
             <T, TouchSurfaceCallbacks>::type
  {
  public:
    typedef typename core::base_classes::
      CallbackGroupTArray<T, TouchSurfaceCallbacks>::type     base_type;

    using base_type::m_observers;

  public:
    virtual bool OnTouchPress(const tl_size a_caller,
                              const TouchSurfaceEvent& a_event)
    {
      for (tl_size i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnTouchPress(a_caller, a_event) == true)
        {
          return true; // Veto the rest of the events
        }
      }
      return false;
    }

    virtual bool OnTouchRelease(const tl_size a_caller,
                                const TouchSurfaceEvent& a_event)
    {
      for (tl_size i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnTouchRelease(a_caller, a_event) == true)
        {
          return true; // Veto the rest of the events
        }
      }
      return false;
    }

    virtual bool OnTouchMove(const tl_size a_caller,
                             const TouchSurfaceEvent& a_event)
    {
      for (tl_size i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnTouchMove(a_caller, a_event) == true)
        {
          return true;
        }
      }
      return false;
    }
  };

  template <class T1,
            class T2 = TLOC_DUMMY_PARAM,
            class T3 = TLOC_DUMMY_PARAM,
            class T4 = TLOC_DUMMY_PARAM>
  struct TouchSurfaceParamList
  {
    T1 m_param1;
    T2 m_param2;
    T3 m_param3;
    T4 m_param4;
  };

  template <typename T_Policy = InputPolicy::Buffered,
    typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class TouchSurface
    : public core::base_classes::DispatcherBaseArray
             <TouchSurfaceCallbacks, TouchSurfaceCallbackGroupT>::type
    , public core::NonCopyable
  , public p_hid::TouchSurface
  {
  public:
    typedef T_Platform                                    platform_type;
    typedef T_Policy                                      policy_type;
    typedef TouchSurfaceEvent                             touch_type;
    typedef touch_type::touch_handle_type                 touch_handle_type;
    typedef core::containers::tl_array<touch_type>::type  touch_container_type;

    typedef TouchSurface<policy_type, platform_type> this_type;

    template <typename T_ParamList>
    TouchSurface(const T_ParamList& a_paramList);
    ~TouchSurface();

    const touch_container_type& GetCurrentTouches() const;
    const touch_type* GetTouch(touch_handle_type a_touch) const;
    bool IsTouchDown(touch_handle_type a_touch) const;

    void SendOnTouchPress(const touch_type& a_event);
    void SendOnTouchRelease(const touch_type& a_event);
    void SendOnTouchMove(const touch_type& a_event);

    void Update();
    void Reset();

  private:

    typedef priv::TouchSurfaceImpl<this_type> impl_type;
    typedef core::smart_ptr::UniquePtr<impl_type> impl_ptr_type;
    
    impl_type*  m_impl;
  };

};};};



#endif
