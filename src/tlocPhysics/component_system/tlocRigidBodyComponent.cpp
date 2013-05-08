#include "tlocRigidBodyComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::
    RigidBody(rigid_body_def_sptr a_rigidBodyDef)
    : base_type(k_component_type)
    , m_rigidBodyDef(a_rigidBodyDef)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RigidBody);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(rigid_body_sptr);

};};};
