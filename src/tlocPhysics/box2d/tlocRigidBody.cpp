#include "tlocRigidBody.h"

#include <tlocPhysics/box2d/tlocComponentType.h>

namespace tloc { namespace physics { namespace box2d { namespace component_system{

  RigidBody::RigidBody(const rigid_body_def_type& a_box2dRigidBodyDef)
    : base_type(components::k_rigid_body)
    , m_box2dRigidBodyDef(a_box2dRigidBodyDef)
    , m_box2dRigidBody(NULL)
  {
  }

  void RigidBody::SetBox2dRigidBody(rigid_body_type* a_box2dRigidBody)
  {
    TLOC_ASSERT(!a_box2dRigidBody,
                "Internal rigid body cannot be set to null! \
                Use SetBox2dRigidBodyToNull");

    m_box2dRigidBody = a_box2dRigidBody;
  }

  void RigidBody::SetBox2dRigidBodyToNull()
  {
    m_box2dRigidBody = NULL;
  }

};};};};
