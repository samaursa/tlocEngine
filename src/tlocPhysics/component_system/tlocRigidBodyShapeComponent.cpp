#include "tlocRigidBodyShapeComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyShape::
    RigidBodyShape()
    : base_type(k_component_type)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyShape::
    RigidBodyShape(const rigid_body_shape_def_type& a_rigidBodyShape)
    : base_type(k_component_type)
    , m_rigidBodyShape(a_rigidBodyShape)
  { }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RigidBodyShape);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(RigidBodyShape);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(RigidBodyShape);