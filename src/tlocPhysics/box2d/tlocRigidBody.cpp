#include "tlocRigidBody.h"
#include "tlocRigidBody.inl.h"

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiation

  template void RigidBody::DoSetType<p_rigid_body::StaticBody>();
  template void RigidBody::DoSetType<p_rigid_body::KinematicBody>();
  template void RigidBody::DoSetType<p_rigid_body::DynamicBody>();

};};};
