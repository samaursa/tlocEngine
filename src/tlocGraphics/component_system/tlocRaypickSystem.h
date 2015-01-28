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

  public:
    RaypickEvent();

    bool operator ==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

  public:
    entity_ptr      m_pickedEnt;
    entity_ptr      m_cameraEnt;
    vec3_type       m_camToEntVec;
    vec2_type       m_mouseCoords;
    bool            m_noDistanceCheck;
  };

  // ///////////////////////////////////////////////////////////////////////
  // RaypickCallbacks

  struct RaypickCallbacks
  {
  public:
    typedef core_dispatch::Event                        event_type;

  public:
    virtual event_type  OnRaypickEvent(const RaypickEvent& a_event) = 0;
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
      const auto size = m_observers.size();
      for (u32 i = 0 ; i < size; ++i)
      {
        if (m_observers[i]->OnRaypickEvent(a_event).IsVeto())
        { return core_dispatch::f_event::Veto(); }
      }

      return core_dispatch::f_event::Continue();
    }
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
    typedef RaypickSystem                               this_type;
    typedef core_conts::Array<RaypickEvent>             raypick_event_cont;

    typedef core_dispatch::Event                        event_type;
    typedef math_t::Vec2f                               vec2_type;
    typedef core_conts::Array<vec2_type>                vec2_cont;

    typedef math_t::Ray3f32                             ray_type;
    typedef core_conts::Array<ray_type>                 ray_cont;

    typedef math_t::Mat4f32                             matrix_type;
    typedef gfx_t::Dimension2                           dim_type;

  public:
    RaypickSystem(event_manager_ptr, entity_manager_ptr);

    virtual error_type InitializeEntity(entity_ptr) override;
    virtual void       Pre_ProcessActiveEntities(f64) override;
    virtual void       ProcessEntity(entity_ptr, f64) override;
    virtual void       Post_ProcessActiveEntities(f64) override;

    void  SetCamera(entity_ptr a_camera);
    TLOC_DECL_AND_DEF_GETTER(entity_ptr, GetCamera, m_sharedCamera);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(dim_type, SetWindowDimensions, m_windowDim);
    TLOC_DECL_AND_DEF_GETTER(dim_type, GetWindowDimensions, m_windowDim);

  public:
    event_type OnMouseMove(const tl_size, const input_hid::MouseEvent&);

  private:
    raypick_event_cont    m_raypickEvents;
    entity_ptr            m_currentPick;

    vec2_cont             m_mouseMovements;
    dim_type              m_windowDim;
    ray_cont              m_rays;

    entity_ptr            m_sharedCamera;
    matrix_type           m_camTransMat;
  };
  TLOC_DEF_TYPE(RaypickSystem);

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RaypickSystem, raypick_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(RaypickSystem, raypick_system);
  
};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::RaypickSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::RaypickSystem);

#endif