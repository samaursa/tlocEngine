#include "tlocRigidBodyListenerComponent.h"

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace physics { namespace component_system {

  RigidBodyListener::RigidBodyListener(rigid_body_listener_type* a_listener)
    : base_type(components::k_rigid_body_listener)
    , m_rigidBodyListener(a_listener)
  {
  }

};};};
