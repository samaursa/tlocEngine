#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocPhysics/box2d/tlocWorld.h>

namespace tloc { namespace physics { namespace component_system {

  class RigidBody;
  class RigidBodyShape;

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

    typedef box2d::World                world_type;

    typedef RigidBody                   rigid_body_component_type;
    typedef RigidBodyShape              rigid_body_shape_component_type;

  public:
    RigidBodySystem
      (event_manager* a_eventMgr, entity_manager* a_entityMgr,
       world_type* a_world);

    virtual error_type InitializeEntity(entity_manager* a_mgr, 
                                        entity_type* a_ent);

    virtual error_type ShutdownEntity(entity_manager* a_mgr, 
                                      entity_type* a_ent);

    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent);

  private:
    error_type 
      DoInitializeRigidBodyComponent(entity_type* a_ent);

    error_type
      DoShutdownRigidBodyComponent(entity_type* a_ent);

  private:
    world_type* m_world;
  };

};};};


#endif