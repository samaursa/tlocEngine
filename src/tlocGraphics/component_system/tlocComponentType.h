#ifndef TLOC_GFX_COMPONENT_TYPE_H
#define TLOC_GFX_COMPONENT_TYPE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace components
  {
    enum type
    {
      k_mesh = core::component_system::component_group::k_graphics,
      k_mesh_interleaved,
      k_quad, // specialized mesh
      k_fan,
      k_material,
      k_texture_coords,
      k_texture_animator,

      k_scene_node,

      k_camera,
      k_arcball,

      k_dynamic_text,
      k_static_text,

      k_count
    }; typedef tl_int value_type;
  };

};};};

#endif