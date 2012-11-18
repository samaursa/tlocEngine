#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_
#define _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>

#include <tlocPhysics/box2d/tlocComponentType.h>
#include <tlocPhysics/box2d/tlocWorld.h>

namespace tloc { namespace physics { namespace box2d { namespace component_system {

  class RigidBodySystem : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem  base_type;
    typedef base_type::component_type   component_type;
    typedef base_type::error_type       error_type;

    typedef base_type::event_manager    event_manager;
    typedef base_type::entity_manager   entity_manager;
    typedef base_type::entity_type      entity_type;
    typedef base_type::event_type       event_type;
    typedef base_type::event_value_type event_value_type;

    typedef World                       world_type;

  public:
    RigidBodySystem
      (event_manager* a_eventMgr, entity_manager* a_entityMgr,
       world_type* a_world);

    virtual error_type Initialize();

    virtual error_type Shutdown();

    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent);

    virtual void Pre_OnEvent(const event_type& a_event);

    virtual void Post_OnEvent(const event_type& a_event);

  private:
    world_type* m_world;
  };

};};};};


#endif