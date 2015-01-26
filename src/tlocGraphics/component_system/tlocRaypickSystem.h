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
#include <tlocCore/containers/tlocQueue.h>

#include <tlocInput/hid/tlocMouse.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // RaypickEvent

  struct RaypickEvent
  {
  public:
    typedef core_cs::entity_vptr                  entity_ptr;
    typedef math_t::Vec3f                         vec3_type;
    typedef math_t::Vec2f                         vec2_type;

  public:
    RaypickEvent();

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
  {
  public:
    typedef core_cs::EntityProcessingSystem             base_type;
    typedef RaypickSystem                               this_type;
    typedef core_conts::Queue<RaypickEvent>             raypick_even_queue;

    typedef core_dispatch::Event                        event_type;
    typedef math_t::Vec2f                               vec2_type;
    typedef core_conts::Queue<vec2_type>                vec2_queue;

  public:
    RaypickSystem(event_manager_ptr, entity_manager_ptr);

    virtual error_type InitializeEntity(entity_ptr) override;
    virtual void       ProcessEntity(entity_ptr, f64) override;
    virtual void       Post_ProcessActiveEntities(f64) override;

    void  SetCamera();
    TLOC_DECL_AND_DEF_GETTER(entity_ptr, GetCamera, m_camera);

  public:
    event_type OnMouseButtonPress(const tl_size, 
                                  const input_hid::MouseEvent&,
                                  const input_hid::MouseEvent::button_code_type);

    event_type OnMouseButtonRelease(const tl_size, 
                                    const input_hid::MouseEvent&,
                                    const input_hid::MouseEvent::button_code_type);

    event_type OnMouseMove(const tl_size, const input_hid::MouseEvent&);

  private:
    raypick_even_queue    m_raypickEvents;
    vec2_queue            m_mouseMovements;
    entity_ptr            m_camera;
  };
  TLOC_DEF_TYPE(RaypickSystem);

  // -----------------------------------------------------------------------
  // typedefs

};};};

#endif