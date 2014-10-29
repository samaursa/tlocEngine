#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocPrimitive.h>
#include <tlocGraphics/component_system/tlocRenderable_TI.h>
#include <tlocGraphics/opengl/tlocAttributeVBO.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_VertexStoragePolicy = p_primitive::StructureOfArrays>
  class Mesh_T
    : public Primitive_TI<T_VertexStoragePolicy>
    , public gfx_cs::Renderable_TI<Mesh_T
      <T_VertexStoragePolicy>, T_VertexStoragePolicy::k_component_id>
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_VertexStoragePolicy, p_primitive::ArrayOfStructures>::value ||
      Loki::IsSameType<T_VertexStoragePolicy, p_primitive::StructureOfArrays>::value),
      Unsupported_template_parameter);

  public:
    typedef T_VertexStoragePolicy                         vertex_storage_policy;
    typedef Primitive_TI<vertex_storage_policy>           base_primitive_type;
    typedef Mesh_T<vertex_storage_policy>                 this_type;
    typedef gfx_cs::Renderable_TI
      <this_type,
       vertex_storage_policy::k_component_id>             base_type;

  public:
    Mesh_T();

    using base_primitive_type::AddVertex;
    using base_primitive_type::GetVertex;
    using base_primitive_type::ModifyVertex;
    using base_primitive_type::size;
    using base_primitive_type::clear;

    TLOC_DECL_AND_DEF_SETTER(bool, SetTexCoordsEnabled, m_texCoordsEnabled);
    TLOC_DECL_AND_DEF_SETTER(bool, SetNormalsEnabled, m_normalsEnabled);

    TLOC_DECL_AND_DEF_GETTER(bool, IsTexCoordsEnabled, m_texCoordsEnabled);
    TLOC_DECL_AND_DEF_GETTER(bool, IsNormalsEnabled, m_normalsEnabled);

  private:
    bool               m_texCoordsEnabled, m_normalsEnabled;
  };

  //------------------------------------------------------------------------
  // typedef

  typedef Mesh_T<p_primitive::ArrayOfStructures>  Mesh_Interleaved;
  typedef Mesh_T<p_primitive::StructureOfArrays>  Mesh;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh, mesh);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh, mesh);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh, mesh);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh_Interleaved, mesh_interleaved);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh_Interleaved, mesh_interleaved);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh_Interleaved, mesh_interleaved);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(Mesh);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(Mesh);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(Mesh_Interleaved);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(Mesh_Interleaved);

};};};

#endif