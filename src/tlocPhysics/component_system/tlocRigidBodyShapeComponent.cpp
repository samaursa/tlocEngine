#include "tlocRigidBodyShapeComponent.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyShape::
    RigidBodyShape(const rigid_body_shape_def_type& a_rigidBodyShape)
    : base_type(components::k_rigidBodyShape)
    , m_rigidBodyShape(a_rigidBodyShape)
  {
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<RigidBodyShape>;
  template class core::component_system::ComponentPool_TI<RigidBodyShapePtr>;

};};};