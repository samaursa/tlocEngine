#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/component_system/tlocPrimitive.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_VertexStoragePolicy = p_primitive::StructureOfArrays>
  class Mesh_T
    : public Primitive_TI<T_VertexStoragePolicy>
    , public core_cs::Component_T<Mesh_T
      <T_VertexStoragePolicy>, T_VertexStoragePolicy::k_component_id>
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_VertexStoragePolicy, p_primitive::ArrayOfStructures>::value ||
      Loki::IsSameType<T_VertexStoragePolicy, p_primitive::StructureOfArrays>::value),
      Unsupported_template_parameter);
  public:
    typedef T_VertexStoragePolicy                       vertex_storage_policy;
    typedef Primitive_TI<vertex_storage_policy>         base_primitive_type;
    typedef Mesh_T<vertex_storage_policy>               this_type;
    typedef core_cs::Component_T
      <this_type,
       vertex_storage_policy::k_component_id>           base_type;
    typedef Primitive_TI<vertex_storage_policy>         base_primitive_type;

    Mesh_T();
  };

  //------------------------------------------------------------------------
  // typedef

  typedef Mesh_T<p_primitive::ArrayOfStructures>  Mesh_Interleaved;
  typedef Mesh_T<p_primitive::StructureOfArrays>  Mesh;

};};};

#endif