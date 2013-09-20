#ifndef TLOC_GFX_COMPONENT_TYPE_H
#define TLOC_GFX_COMPONENT_TYPE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace components
  {
    enum type
    {
      mesh = core::component_system::components_group::graphics,
      mesh_interleaved,
      quad, // specialized mesh
      fan,
      material,
      texture_coords,
      texture_animator,

      scene_node,

      camera,
      arcball,

      count
    }; typedef tl_int value_type;
  };

};};};

#endif