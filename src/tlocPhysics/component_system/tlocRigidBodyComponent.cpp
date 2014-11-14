#include "tlocRigidBodyComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace physics { namespace component_system{

  RigidBody::
    RigidBody()
    : base_type("RigidBody")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::
    RigidBody(rigid_body_def_sptr a_rigidBodyDef)
    : base_type("RigidBody")
    , m_rigidBodyDef(a_rigidBodyDef)
  {
  }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RigidBody);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(RigidBody);
