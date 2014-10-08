#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyListener is an interface for callbacks that can be tied to
  /// a RigidBodyListener component. Callback functions will be fired when the
  /// RigidBodyListener component receives an event, allowing an external
  /// implementation to handle the event.
  ///-------------------------------------------------------------------------
  class RigidBodyListener
  {
  public:
    typedef core_cs::Entity             entity_type;
    typedef core_cs::const_entity_vptr  const_entity_ptr;

  public:
    virtual void OnContactBegin(const_entity_ptr a_ent) = 0;
    virtual void OnContactEnd(const_entity_ptr a_ent) = 0;

    virtual ~RigidBodyListener() { }
  };

  TLOC_TYPEDEF_VIRTUAL_PTR(RigidBodyListener, rigid_body_listener);

};};

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyListener component allows an external implementation to
  /// receive events from the RigidBody component, funneling it to a
  /// RigidBodyListener callback class.
  ///-------------------------------------------------------------------------
  class RigidBodyListener :
    public core::component_system::Component_T<RigidBodyListener,
                                               components::k_rigidBodyListener>
  {
  public:
    typedef RigidBodyListener                                       this_type;
    typedef core::component_system::Component_T
      <RigidBodyListener, components::k_rigidBodyListener>          base_type;

    typedef physics::rigid_body_listener_vptr         rigid_body_listener_ptr;

  public:
    RigidBodyListener();
    RigidBodyListener(const rigid_body_listener_ptr& a_listener);

  public:

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_listener_ptr, GetRigidBodyListener, m_rigidBodyListener);

  private:
    rigid_body_listener_ptr m_rigidBodyListener;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RigidBodyListener, rigid_body_listener);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(RigidBodyListener, rigid_body_listener);
  TLOC_TYPEDEF_COMPONENT_POOL(RigidBodyListener, rigid_body_listener);

};};};

#endif