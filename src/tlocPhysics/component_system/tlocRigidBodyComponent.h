#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocPhysics/box2d/tlocRigidBodyDef.h>
#include <tlocPhysics/box2d/tlocRigidBody.h>
#include <tlocPhysics/box2d/tlocRigidBody.inl>

namespace tloc { namespace physics { namespace component_system {

  class RigidBody : public core::component_system::Component_T<RigidBody>
  {
  public:
    typedef core::component_system::Component_T<RigidBody>  base_type;
    typedef box2d::RigidBodyDef                             rigid_body_def_type;
    typedef box2d::RigidBody                                rigid_body_type;

  public:
    RigidBody
      (const rigid_body_def_type& a_box2dRigidBodyDef = rigid_body_def_type());

    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (rigid_body_type, GetRigidBody, m_rigidBody);

    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (rigid_body_def_type, GetRigidBodyDef, m_rigidBodyDef);

  private:
    rigid_body_def_type m_rigidBodyDef;
    rigid_body_type m_rigidBody;
  };

};};};
#endif