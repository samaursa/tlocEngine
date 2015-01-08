#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocPrimitive.h>
#include <tlocGraphics/component_system/tlocRenderable_TI.h>
#include <tlocGraphics/opengl/tlocAttributeVBO.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_mesh
  {
    struct Mesh2D   {};
    struct Mesh3D   {};
    struct Static   {};
    struct Dynamic  {};
  };

  // ///////////////////////////////////////////////////////////////////////
  // Mesh_T<>

  template <typename T_MeshType, typename T_StaticDynamic>
  class Mesh_T
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_MeshType, p_mesh::Mesh2D>::value ||
       Loki::IsSameType<T_MeshType, p_mesh::Mesh3D>::value), 
       Unsupported_mesh_dimensions);

    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_StaticDynamic, p_mesh::Static>::value ||
       Loki::IsSameType<T_StaticDynamic, p_mesh::Dynamic>::value), 
       Unsupported_mesh_type);
  };

  // ///////////////////////////////////////////////////////////////////////
  // 2D Mesh

  template <>
  class Mesh_T<p_mesh::Mesh2D, p_mesh::Dynamic>
    : public Primitive_I
    , public gfx_cs::Renderable_TI<Mesh_T<p_mesh::Mesh2D, p_mesh::Dynamic>, 
                                   gfx_cs::components::k_mesh_2d>
  {
  public:
    typedef p_mesh::Mesh2D                                mesh_type;
    typedef p_mesh::Dynamic                               static_dynamic_type;

    typedef Primitive_I                                   base_primitive_type;
    typedef Mesh_T<mesh_type, static_dynamic_type>        this_type;
    typedef gfx_cs::Renderable_TI
      <this_type, gfx_cs::components::k_mesh_2d>          base_type;

  public:
    Mesh_T();

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

  // ///////////////////////////////////////////////////////////////////////
  // 2D Mesh - STATIC

  template <>
  class Mesh_T<p_mesh::Mesh2D, p_mesh::Static>
    : public Primitive_I
    , public gfx_cs::Renderable_TI<Mesh_T<p_mesh::Mesh2D, p_mesh::Static>, 
                                   gfx_cs::components::k_mesh_2d_static>
  {
  public:
    typedef p_mesh::Mesh2D                                mesh_type;
    typedef p_mesh::Static                                static_dynamic_type;

    typedef Primitive_I                                   base_primitive_type;
    typedef Mesh_T<mesh_type, static_dynamic_type>        this_type;
    typedef gfx_cs::Renderable_TI
      <this_type, gfx_cs::components::k_mesh_2d_static>   base_type;

  public:
    Mesh_T();

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

  // ///////////////////////////////////////////////////////////////////////
  // 3D Mesh

  template <>
  class Mesh_T<p_mesh::Mesh3D, p_mesh::Dynamic>
    : public Primitive_I
    , public gfx_cs::Renderable_TI<Mesh_T<p_mesh::Mesh3D, p_mesh::Dynamic>, 
                                   gfx_cs::components::k_mesh>
  {
  public:
    typedef p_mesh::Mesh3D                                mesh_type;
    typedef p_mesh::Dynamic                               static_dynamic_type;

    typedef Primitive_I                                   base_primitive_type;
    typedef Mesh_T<mesh_type, static_dynamic_type>        this_type;
    typedef Mesh_T<p_mesh::Mesh3D, p_mesh::Dynamic>       this_type;
    typedef gfx_cs::Renderable_TI
      <this_type, gfx_cs::components::k_mesh>             base_type;

  public:
    Mesh_T();

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

  // ///////////////////////////////////////////////////////////////////////
  // 3D Mesh - STATIC

  template <>
  class Mesh_T<p_mesh::Mesh3D, p_mesh::Static>
    : public Primitive_I
    , public gfx_cs::Renderable_TI<Mesh_T<p_mesh::Mesh3D, p_mesh::Static>, 
                                   gfx_cs::components::k_mesh_static>
  {
  public:
    typedef p_mesh::Mesh3D                                mesh_type;
    typedef p_mesh::Static                                static_dynamic_type;

    typedef Primitive_I                                   base_primitive_type;
    typedef Mesh_T<mesh_type, static_dynamic_type>        this_type;
    typedef Mesh_T<p_mesh::Mesh3D, p_mesh::Static>        this_type;
    typedef gfx_cs::Renderable_TI
      <this_type, gfx_cs::components::k_mesh_static>      base_type;

  public:
    Mesh_T();

    using base_primitive_type::AddVertex;
    using base_primitive_type::GetVertex;
    using base_primitive_type::ModifyVertex;
    using base_primitive_type::begin;
    using base_primitive_type::end;
    using base_primitive_type::size;
    using base_primitive_type::clear;
    using base_primitive_type::GetVertexType;
    using base_primitive_type::GetNumVertices;

    using base_type::SetUpdateRequired;
  };

  //------------------------------------------------------------------------
  // typedef

  typedef Mesh_T<p_mesh::Mesh2D, p_mesh::Dynamic>       Mesh2D;
  typedef Mesh_T<p_mesh::Mesh2D, p_mesh::Static>        Mesh2DStatic;;
  typedef Mesh_T<p_mesh::Mesh3D, p_mesh::Dynamic>       Mesh;
  typedef Mesh_T<p_mesh::Mesh3D, p_mesh::Static>        MeshStatic;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh2D, mesh_2d);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh2D, mesh_2d);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh2D, mesh_2d);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh2DStatic, mesh_2d_static);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh2DStatic, mesh_2d_static);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh2DStatic, mesh_2d_static);

  TLOC_TYPEDEF_ALL_SMART_PTRS(Mesh, mesh);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Mesh, mesh);
  TLOC_TYPEDEF_COMPONENT_POOL(Mesh, mesh);

  TLOC_TYPEDEF_ALL_SMART_PTRS(MeshStatic, mesh_static);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(MeshStatic, mesh_static);
  TLOC_TYPEDEF_COMPONENT_POOL(MeshStatic, mesh_static);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Mesh2D);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::Mesh2D);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Mesh2DStatic);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::Mesh2DStatic);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Mesh);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::Mesh);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::MeshStatic);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::MeshStatic);

#endif