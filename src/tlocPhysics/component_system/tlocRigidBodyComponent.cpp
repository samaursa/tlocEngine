#include "tlocRigidBodyComponent.h"

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::RigidBody(const rigid_body_def_type& a_box2dRigidBodyDef)
    : base_type(components::k_rigid_body)
    , m_rigidBodyDef(a_box2dRigidBodyDef)
  {
  }

};};};
