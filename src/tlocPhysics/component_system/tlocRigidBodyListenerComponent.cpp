#include "tlocRigidBodyListenerComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyListener::
    RigidBodyListener(rigid_body_listener_type* a_listener)
    : base_type(k_component_type)
    , m_rigidBodyListener(a_listener)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RigidBodyListener);

  template class core::component_system::ComponentPool_TI<rigid_body_listener_sptr>;

};};};