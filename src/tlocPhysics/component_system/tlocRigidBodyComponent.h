#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_H_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocRigidBodyDef.h>
#include <tlocPhysics/box2d/tlocRigidBody.h>
#include <tlocPhysics/box2d/tlocRigidBody.inl.h>
#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  ///-------------------------------------------------------------------------
  /// @brief  RigidBody component is used for giving an entity the "invisible"
  /// physical attributes of a rigid body, such as position, velocity and type.
  /// Note: The component is initialized during the RigidBodySystem
  /// initialization.
  ///-------------------------------------------------------------------------
  class RigidBody
    : public core_cs::Component_T<RigidBody, 
                                  core_cs::component_group::k_physics,
                                  components::k_rigidBody>
  {
  public:
    typedef RigidBody                                       this_type;
    typedef core::component_system::Component_T
      <this_type, k_component_group, k_component_type>      base_type;
    typedef box2d::rigid_body_def_sptr                      rigid_body_def_sptr;
    typedef box2d::RigidBody                                rigid_body_type;

  public:
    RigidBody();
    RigidBody
      (rigid_body_def_sptr a_rigidBodyDef);

    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (rigid_body_type, GetRigidBody, m_rigidBody);

    TLOC_DECL_AND_DEF_GETTER
      (rigid_body_def_sptr, GetRigidBodyDef, m_rigidBodyDef);

  private:
    rigid_body_def_sptr m_rigidBodyDef;
    rigid_body_type m_rigidBody;
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(RigidBody, rigid_body);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(RigidBody, rigid_body);
  TLOC_TYPEDEF_COMPONENT_POOL(RigidBody, rigid_body);

};};};
#endif