#include "tlocRigidBodyComponent.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::RigidBody(const rigid_body_def_type& a_box2dRigidBodyDef)
    : base_type(components::k_rigid_body)
    , m_rigidBodyDef(a_box2dRigidBodyDef)
  {
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<RigidBody>;
  template class core::component_system::ComponentPool_TI<RigidBodyPtr>;

};};};
