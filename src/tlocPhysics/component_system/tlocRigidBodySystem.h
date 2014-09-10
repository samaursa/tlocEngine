#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_SYSTEM_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocPhysics/box2d/tlocWorld.h>

namespace tloc { namespace physics { namespace component_system {

  class RigidBody;
  class RigidBodyShape;

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodySystem manages all rigid body components. When processing
  /// it transfers the rigid body components transform to the entity's transform
  /// component. NOTE: All RigidBodyShapes must be added to the entity before
  /// this system is initialized.
  ///-------------------------------------------------------------------------
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

    typedef RigidBody                   rigid_body_component;
    typedef RigidBodyShape              rigid_body_shape_component_type;

  public:
    RigidBodySystem(event_manager_ptr a_eventMgr,
                    entity_manager_ptr a_entityMgr,
                    world_type* a_world);

    virtual error_type InitializeEntity(entity_ptr a_ent);

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  private:
    error_type
      DoInitializeRigidBodyComponent(entity_ptr);

    error_type
      DoShutdownRigidBodyComponent(entity_ptr);

  private:
    world_type* m_world;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RigidBodySystem, rigid_body_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(RigidBodySystem, rigid_body_system);

};};};


#endif