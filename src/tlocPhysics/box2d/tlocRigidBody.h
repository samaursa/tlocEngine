#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_H_
#define _TLOC_PHYSICS_BOX2D_COMPONENT_SYSTEM_RIGID_BODY_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <Box2D/Dynamics/b2Body.h>

namespace tloc { namespace physics { namespace box2d { namespace component_system {

  class RigidBody : public core::component_system::Component_T<RigidBody>
  {
  public:
    typedef core::component_system::Component_T<RigidBody>  base_type;
    typedef b2BodyDef                                       rigid_body_def_type;
    typedef b2Body                                          rigid_body_type;
    
  public:
    RigidBody
      (const rigid_body_def_type& a_box2dRigidBodyDef = rigid_body_def_type());

    TLOC_DECL_AND_DEF_GETTER(rigid_body_def_type, GetBox2dRigidBodyDef, 
                             m_box2dRigidBodyDef);
    TLOC_DECL_AND_DEF_GETTER(rigid_body_type*, GetBox2dRigidBody, 
                             m_box2dRigidBody);

    void SetBox2dRigidBody(rigid_body_type* a_box2dRigidBody);
    void SetBox2dRigidBodyToNull();

  private:
    rigid_body_def_type m_box2dRigidBodyDef;
    rigid_body_type* m_box2dRigidBody;
  };

};};};};
#endif