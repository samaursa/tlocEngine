#include "tlocRigidBodyListenerComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyListener::
    RigidBodyListener(rigid_body_listener_type* a_listener)
    : base_type(components::k_rigidBodyListener)
    , m_rigidBodyListener(a_listener)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<RigidBodyListener>;
  template class core::component_system::ComponentPool_TI<RigidBodyListenerPtr>;

};};};