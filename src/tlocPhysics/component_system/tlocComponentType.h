#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_COMPONENT_TYPE_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_COMPONENT_TYPE_H_

#include <tlocCore/component_system/tlocComponentType.h>

// NOTE: Once more physics systems are added, there must be a central
// tlocComponentType.h that properly distributes the components.

namespace tloc { namespace physics { namespace component_system {

  namespace components
  {
    enum type
    {
      k_rigidBody = core::component_system::components_group::physics,
      k_rigidBodyShape,
      k_rigidBodyListener,

      count
    }; typedef tl_int value_type;
  };

};};};

#endif