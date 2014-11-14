#include "tlocRigidBodyShapeComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyShape::
    RigidBodyShape()
    : base_type("RigidBodyShape")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyShape::
    RigidBodyShape(const rigid_body_shape_def& a_rigidBodyShape)
    : base_type("RigidBodyShape")
    , m_rigidBodyShape(a_rigidBodyShape)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RigidBodyShape);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(RigidBodyShape);