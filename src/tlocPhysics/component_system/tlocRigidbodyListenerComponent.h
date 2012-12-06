#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_H_

#include <tlocCore/tlocBase.h>
#include <tloccore/utilities/tlocUtils.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace physics {

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

};};};

#endif