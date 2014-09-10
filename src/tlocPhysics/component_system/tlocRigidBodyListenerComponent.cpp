#include "tlocRigidBodyListenerComponent.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyListener::
    RigidBodyListener()
    : base_type(k_component_type, "RigidBodyListener")
  { }

  RigidBodyListener::
    RigidBodyListener(const rigid_body_listener_ptr& a_listener)
    : base_type(k_component_type, "RigidBodyListener")
    , m_rigidBodyListener(a_listener)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::physics::RigidBodyListener);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RigidBodyListener);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(RigidBodyListener);
