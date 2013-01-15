#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_

#include <tlocPhysics/tlocPhysicsBase.h>

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
    typedef core::component_system::EntityProcessingSystem base_type;
    typedef base_type::component_type   component_type;
    typedef base_type::error_type       error_type;

    typedef base_type::event_manager    event_manager;
    typedef base_type::entity_manager   entity_manager;
    typedef base_type::entity_type      entity_type;
    typedef base_type::event_type       event_type;
    typedef base_type::event_value_type event_value_type;

    typedef box2d::ContactEvent             contact_event_type;
    typedef box2d::PhysicsManager           physics_manager;

    typedef core::containers::Array<contact_event_type> contact_event_list;
    typedef core::containers::Array<contact_event_list> contact_event_list_list;

  public:
    RigidBodyListenerSystem(event_manager* a_eventMgr, entity_manager* a_entityMgr,
                            physics_manager* a_physicsMgr);

    virtual error_type Pre_Initialize();
    virtual error_type Post_Shutdown();

    virtual error_type InitializeEntity(entity_manager* a_mgr, entity_type* a_ent);
    virtual error_type ShutdownEntity(entity_manager* a_mgr, entity_type* a_ent);

    virtual void Pre_ProcessActiveEntities();
    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent);

  public:
    bool OnContactBegin(const contact_event_type& a_event);
    bool OnContactEnd(const contact_event_type& a_event);

  private:
    physics_manager* m_physicsMgr;
    contact_event_list_list m_allContactEvents;
  };

};};};


#endif