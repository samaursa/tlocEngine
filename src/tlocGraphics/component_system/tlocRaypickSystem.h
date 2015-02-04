#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RAYPICK_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RAYPICK_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/dispatch/tlocEvent.h>
#include <tlocCore/dispatch/tlocTemplateDispatchDefaults.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/containers/tlocArray.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/types/tlocRay.h>

#include <tlocGraphics/types/tlocDimension.h>

#include <tlocInput/hid/tlocMouse.h>
#include <tlocInput/hid/tlocTouchSurface.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // RaypickEvent

  struct RaypickEvent
  {
  public:
    typedef RaypickEvent                          this_type;
    typedef core_cs::entity_vptr                  entity_ptr;
    typedef math_t::Vec3f                         vec3_type;
    typedef math_t::Vec2f                         vec2_type;
    typedef math_t::Ray3f32                       ray_type;

  public:
    RaypickEvent();

    bool operator ==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

  public:
    entity_ptr      m_ent;
    entity_ptr      m_cameraEnt;
    vec3_type       m_camToEntVec;
    ray_type        m_rayInWorldSpace;
    bool            m_distanceChecked;
  };

  // ///////////////////////////////////////////////////////////////////////
  // RaypickCallbacks

  struct RaypickCallbacks
  {
  public:
    typedef core_dispatch::Event                        event_type;

  public:
    virtual event_type  OnRaypickEvent(const RaypickEvent& a_event) = 0;
    virtual event_type  OnRayUnpickEvent(const RaypickEvent& a_event) = 0;
  };

  // ///////////////////////////////////////////////////////////////////////
  // RaypickCallbackGroupT

  template <typename T>
  struct RaypickCallbackGroup_T
    : public core_dispatch::CallbackGroupTArray<T, RaypickCallbacks>::type
  {
  public:
    typedef typename core_dispatch::
      CallbackGroupTArray<T, RaypickCallbacks>::type          base_type;
    typedef typename base_type::event_type                    event_type;

    using base_type::m_observers;

  public:
    virtual event_type OnRaypickEvent(const RaypickEvent& a_event) override
    {
      for (auto itr = m_observers.begin(), itrEnd = m_observers.end(); 
           itr != itrEnd; ++itr)
      {
        if ((*itr)->OnRaypickEvent(a_event).IsVeto())
        { return core_dispatch::f_event::Veto(); }
      }

      return core_dispatch::f_event::Continue();
    }

    virtual event_type OnRayUnpickEvent(const RaypickEvent& a_event) override
    {
      for (auto itr = m_observers.begin(), itrEnd = m_observers.end(); 
           itr != itrEnd; ++itr)
      {
        if ((*itr)->OnRayUnpickEvent(a_event).IsVeto())
        { return core_dispatch::f_event::Veto(); }
      }

      return core_dispatch::f_event::Continue();
    }
  };

  namespace p_raypick_system
  {
    typedef enum
    {
      k_continuous,
      k_continuous_on_click,
      k_on_click,
    } mode;
  };

  // ///////////////////////////////////////////////////////////////////////
  // RaypickSystem

  class RaypickSystem
    : public core_cs::EntityProcessingSystem
    , public core_dispatch::DispatcherBaseArray<RaypickCallbacks, 
                                                RaypickCallbackGroup_T>::type
    , public input_hid::MouseListener
  {
  public:
    typedef core_cs::EntityProcessingSystem             base_type;
    typedef core_dispatch::
      DispatcherBaseArray<RaypickCallbacks, 
                          RaypickCallbackGroup_T>::type dispatcher_base_type;

    typedef RaypickSystem                               this_type;
    typedef core_conts::Array<RaypickEvent>             raypick_event_cont;

    typedef core_dispatch::Event                        event_type;
    typedef math_t::Vec2f                               vec2_type;
    typedef core_conts::Array<vec2_type>                vec2_cont;

    typedef math_t::Ray3f32                             ray_type;
    typedef core_conts::Array<ray_type>                 ray_cont;

    typedef math_t::Mat4f32                             matrix_type;
    typedef gfx_t::Dimension2                           dim_type;

    typedef p_raypick_system::mode                      picking_mode;
    typedef input_hid::MouseEvent::button_code_type     button_code;
    typedef input::TouchSurfaceEvent::touch_handle_type touch_handle_type;

  public:
    RaypickSystem(event_manager_ptr, entity_manager_ptr);

    virtual error_type InitializeEntity(entity_ptr) override;
    virtual void       Pre_ProcessActiveEntities(f64) override;
    virtual void       ProcessEntity(entity_ptr, f64) override;
    virtual void       Post_ProcessActiveEntities(f64) override;

    this_type&  SetCamera(entity_ptr a_camera);
    TLOC_DECL_AND_DEF_GETTER(entity_ptr, GetCamera, m_sharedCamera);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(dim_type, SetWindowDimensions, m_windowDim);
    TLOC_DECL_AND_DEF_GETTER(dim_type, GetWindowDimensions, m_windowDim);

    this_type& SetPickingMode(picking_mode a_mode, 
                              button_code a_button = input_hid::MouseEvent::left);
    TLOC_DECL_AND_DEF_GETTER(picking_mode, GetPickingMode, m_pickingMode);
    TLOC_DECL_AND_DEF_GETTER(button_code, GetPickingButton, m_pickingButton);

  public:
    event_type OnMouseButtonPress(const tl_size, 
                                  const input_hid::MouseEvent&, 
                                  const input_hid::MouseEvent::button_code_type);
    event_type OnMouseButtonRelease(const tl_size, 
                                    const input_hid::MouseEvent&, 
                                    const input_hid::MouseEvent::button_code_type);
    event_type OnMouseMove(const tl_size, const input_hid::MouseEvent&);

    event_type OnTouchPress(const tl_size, const input::TouchSurfaceEvent& );
    event_type OnTouchRelease(const tl_size, const input::TouchSurfaceEvent& );
    event_type OnTouchMove(const tl_size, const input::TouchSurfaceEvent& );

    using dispatcher_base_type::Register;

  private:
    raypick_event_cont    m_raypickEvents;
    raypick_event_cont    m_alreadyRaypicked;
    raypick_event_cont    m_unraypickEvents;
    RaypickEvent          m_closestToCamera;

    vec2_cont             m_mouseMovements;
    dim_type              m_windowDim;
    ray_cont              m_rays;

    entity_ptr            m_sharedCamera;
    matrix_type           m_camViewMat;
    matrix_type           m_camViewMatInv;
    matrix_type           m_camTransMat;

    picking_mode          m_pickingMode;
    button_code           m_pickingButton;
    touch_handle_type     m_currentTouch;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RaypickSystem, raypick_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(RaypickSystem, raypick_system);
  
};};};

TLOC_DEF_TYPE(tloc::gfx_cs::RaypickSystem);

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::RaypickSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::RaypickSystem);

#endif