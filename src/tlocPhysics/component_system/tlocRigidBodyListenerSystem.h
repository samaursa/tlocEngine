#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/containers/tlocArray.h>

namespace tloc { namespace physics { namespace box2d {

  struct ContactEvent;
  class PhysicsManager;

};};};

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyListenerSystem manages all of the
  /// RigidBodyListenerComponents. If an entity has a RigidBody, RigidBodyShape
  /// and a RigidBodyListener, the listener that is tied with the
  /// RigidBodyListener will be called if a contact event occurs.
  ///-------------------------------------------------------------------------
  class RigidBodyListenerSystem :
    public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem           base_type;

    typedef box2d::ContactEvent                       contact_event_type;
    typedef box2d::PhysicsManager                     physics_manager;

    typedef core_conts::Array<contact_event_type>     contact_event_list;
    typedef core_conts::Array<contact_event_list>     contact_event_list_list;

  public:
    RigidBodyListenerSystem(event_manager_sptr a_eventMgr,
                            entity_manager_sptr a_entityMgr,
                            physics_manager* a_physicsMgr);

    virtual error_type Pre_Initialize();
    virtual error_type Post_Shutdown();

    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  public:
    bool OnContactBegin(const contact_event_type& a_event);
    bool OnContactEnd(const contact_event_type& a_event);

  private:
    physics_manager* m_physicsMgr;
    contact_event_list_list m_allContactEvents;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(RigidBodyListenerSystem, rigid_body_listener_system);

};};};


#endif