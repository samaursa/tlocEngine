#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

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
    typedef core::component_system::Entity entity_type;

  public:
    virtual void OnContactBegin(const entity_type* a_ent) = 0;
    virtual void OnContactEnd(const entity_type* a_ent) = 0;
  };

};};

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBodyListener component allows an external implementation to
  /// receive events from the RigidBody component, funneling it to a
  /// RigidBodyListener callback class.
  ///-------------------------------------------------------------------------
  class RigidBodyListener :
    public core::component_system::Component_T<RigidBodyListener>
  {
  public:
    typedef RigidBodyListener                                       this_type;
    typedef core::component_system::Component_T<RigidBodyListener>  base_type;

    typedef physics::RigidBodyListener  rigid_body_listener_type;

  public:
    RigidBodyListener(rigid_body_listener_type* a_listener);

  public:
    rigid_body_listener_type* GetRigidBodyListener()
    { return m_rigidBodyListener; }

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_listener_type*, GetRigidBodyListener, m_rigidBodyListener);

  private:
    rigid_body_listener_type* m_rigidBodyListener;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef core::smart_ptr::SharedPtr<RigidBodyListener> RigidBodyListenerPtr;

  typedef core::component_system::ComponentPool_TI<RigidBodyListenerPtr>
                                                        rigid_body_listener_pool;

};};};

#endif