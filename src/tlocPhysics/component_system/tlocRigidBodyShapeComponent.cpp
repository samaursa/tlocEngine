#include "tlocRigidBodyShapeComponent.h"

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyShape::RigidBodyShape(const rigid_body_shape_type* a_rigidBodyShape)
    : base_type(components::k_rigid_body_shape)
    , m_rigidBodyShape(a_rigidBodyShape)
  {
  }

};};};