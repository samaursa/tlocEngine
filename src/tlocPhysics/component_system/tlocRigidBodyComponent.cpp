#include "tlocRigidBodyComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::
    RigidBody(rigid_body_def_sptr a_rigidBodyDef)
    : base_type(components::k_rigidBody)
    , m_rigidBodyDef(a_rigidBodyDef)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<RigidBody>;
  template class core::component_system::ComponentPool_TI<RigidBodyPtr>;

};};};
