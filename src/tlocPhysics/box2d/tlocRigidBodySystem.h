#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_
#define _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_

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
       world_type* a_world)
       : base_type(a_eventMgr, a_entityMgr, core::Variadic<component_type, 2>(components::k_rigid_body, components::k_fixture))
       , m_world(a_world)
    {

    }

  private:
    world_type* m_world;

  };

};};};};


#endif