#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocPrimitive.h>
#include <tlocGraphics/component_system/tlocRenderable_TI.h>
#include <tlocGraphics/opengl/tlocAttributeVBO.h>

namespace tloc { namespace graphics { namespace component_system {

  class Mesh
    : public Primitive_I
    , public gfx_cs::Renderable_TI<Mesh, gfx_cs::components::k_mesh>
  {
  public:
    typedef Primitive_I                                   base_primitive_type;
    typedef Mesh                                          this_type;
    typedef gfx_cs::Renderable_TI
      <this_type, gfx_cs::components::k_mesh>             base_type;

  public:
    Mesh();

    using base_primitive_type::AddVertex;
    using base_primitive_type::GetVertex;
    using base_primitive_type::ModifyVertex;
    using base_primitive_type::begin;
    using base_primitive_type::end;
    using base_primitive_type::size;
    using base_primitive_type::clear;
    using base_primitive_type::GetVertexType;
    using base_primitive_type::GetNumVertices;
  };

  //------------------------------------------------------------------------
  // typedef

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh, mesh);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh, mesh);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh, mesh);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Mesh);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::Mesh);

#endif