#ifndef _TLOC_PREFAB_GRAPHICS_MESH_H_
#define _TLOC_PREFAB_GRAPHICS_MESH_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/renderer/tlocDrawCommand.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // Mesh_T<>

  template <typename T_MeshType, typename T_StaticDynamic>
  class Mesh_T
    : public Prefab_TI<Mesh_T<T_MeshType, T_StaticDynamic>, 
                       gfx_cs::Mesh_T<T_MeshType, T_StaticDynamic>>
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_MeshType, gfx_cs::p_mesh::Mesh2D>::value ||
       Loki::IsSameType<T_MeshType, gfx_cs::p_mesh::Mesh3D>::value), 
       Unsupported_mesh_dimensions);

    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_StaticDynamic, gfx_cs::p_mesh::Static>::value ||
       Loki::IsSameType<T_StaticDynamic, gfx_cs::p_mesh::Dynamic>::value), 
       Unsupported_mesh_type);

  public:
    typedef T_MeshType                                      mesh_type;
    typedef T_StaticDynamic                                 static_dynamic_type;
    typedef gfx_cs::Mesh_T<mesh_type, static_dynamic_type>  component_type;

    typedef Mesh_T<mesh_type, static_dynamic_type>          this_type;
    typedef Prefab_TI<this_type, component_type>            base_type;

    typedef typename base_type::component_ptr               component_ptr;
    typedef typename base_type::insert_params               insert_params;
    typedef typename base_type::entity_mgr_ptr              entity_mgr_ptr;
    typedef typename base_type::comp_pool_mgr_ptr           comp_pool_mgr_ptr;
    typedef typename base_type::entity_ptr                  entity_ptr;

    using base_type::GetListeners;

  public:
    Mesh_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    template <typename T_VertexType>
    component_ptr Construct(const core_conts::Array<T_VertexType>& a_vertices) const;

    template <typename T_VertexType>
    entity_ptr   Create(const core_conts::Array<T_VertexType>& a_vertices) const;

    template <typename T_VertexType>
    void         Add(entity_ptr a_ent, 
                     const core_conts::Array<T_VertexType>& a_vertices) const;

    TLOC_DECL_PARAM_VAR(gfx_rend::mode::value_type, DrawMode, m_drawMode);
    TLOC_DECL_PARAM_VAR(math_cs::Transform, Transformation, m_transform);
    TLOC_DECL_PARAM_VAR(bool, BoundingBox, m_boundingBox);
    TLOC_DECL_PARAM_VAR(bool, Raypick, m_raypick);

  private:

    template <typename T_VertexType>
    const core_conts::Array<T_VertexType>&
      DoTransformStaticMesh(const core_conts::Array<T_VertexType>& a_vertices, 
                            gfx_cs::p_mesh::Static) const;

    template <typename T_VertexType>
    const core_conts::Array<T_VertexType>&
      DoTransformStaticMesh(const core_conts::Array<T_VertexType>& a_vertices, 
                            gfx_cs::p_mesh::Dynamic) const;

    void  DoAddTransformComponent(entity_ptr, gfx_cs::p_mesh::Static) const;
    void  DoAddTransformComponent(entity_ptr, gfx_cs::p_mesh::Dynamic) const;

    void  DoAddBoundingBox(entity_ptr) const;
    void  DoAddRaypicking(entity_ptr) const;

  private:
    using base_type::m_entMgr;
    using base_type::m_compPoolMgr;
  };

  // -----------------------------------------------------------------------
  // typedef

  typedef Mesh_T<gfx_cs::p_mesh::Mesh2D, gfx_cs::p_mesh::Dynamic> Mesh2D;
  typedef Mesh_T<gfx_cs::p_mesh::Mesh2D, gfx_cs::p_mesh::Static>  Mesh2DStatic;

  typedef Mesh_T<gfx_cs::p_mesh::Mesh3D, gfx_cs::p_mesh::Dynamic> Mesh;
  typedef Mesh_T<gfx_cs::p_mesh::Mesh3D, gfx_cs::p_mesh::Static>  MeshStatic;

  // -----------------------------------------------------------------------
  // template defintions

  template <typename T_MeshType, typename T_StaticDynamic>
  template <typename T_VertexType>
  auto
    Mesh_T<T_MeshType, T_StaticDynamic>::
    Construct(const core_conts::Array<T_VertexType>& a_vertices) const
    -> component_ptr
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef core_cs::ComponentPoolManager                   pool_mgr;

    typedef core_conts::Array<T_VertexType>                 vert_cont;
    typedef typename vert_cont::const_iterator              vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_pool                     mesh_pool;

    gfx_cs::mesh_pool_vptr meshPool
      = m_compPoolMgr->template GetOrCreatePool<gfx_cs::Mesh>();

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    (*itrMesh)->SetValue(core_sptr::MakeShared<gfx_cs::Mesh>() );

    gfx_cs::mesh_sptr meshPtr = *(*itrMesh)->GetValuePtr();

    // if mesh is static, transform it right now
    const vert_cont& modifiedCont = 
      DoTransformStaticMesh(a_vertices, static_dynamic_type());

    for (vert_cont_itr itr = modifiedCont.begin(), itrEnd = modifiedCont.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    meshPtr->SetDrawMode(m_drawMode);

    return meshPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_MeshType, typename T_StaticDynamic>
  template <typename T_VertexType>
  auto
    Mesh_T<T_MeshType, T_StaticDynamic>::
    Create(const core_conts::Array<T_VertexType>& a_vertices) const
    -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_vertices);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_MeshType, typename T_StaticDynamic>
  template <typename T_VertexType>
  void
    Mesh_T<T_MeshType, T_StaticDynamic>::
    Add(entity_ptr a_ent, const core_conts::Array<T_VertexType>& a_vertices) const
  {
    // -----------------------------------------------------------------------
    // Transform component

    DoAddTransformComponent(a_ent, static_dynamic_type());

    // -----------------------------------------------------------------------
    // Raypick

    if (m_raypick)
    { DoAddRaypicking(a_ent); }

    // -----------------------------------------------------------------------
    // BoundingBox

    if (m_boundingBox || m_raypick)
    { DoAddBoundingBox(a_ent); }

    // -----------------------------------------------------------------------
    // Mesh component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_vertices))
                              .DispatchTo(GetListeners()) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  void
    DoTransformNormals(T*, math_t::Mat4f32 a_transformation)
  { }

  template <typename T>
  void
    DoTransformNormals(gfx_t::p_vertex_t::VertexNorm_T<T>* a_norm,
                       math_t::Mat4f32 a_transformation)
  {
    auto norm = math_t::Vec4f32(a_norm->GetNormal(), 1);
    norm = a_transformation * norm;

    a_norm->SetNormal(norm.ConvertTo<math_t::Vec3f32>());
  }

  template <typename T_MeshType, typename T_StaticDynamic>
  template <typename T_VertexType>
  auto
    Mesh_T<T_MeshType, T_StaticDynamic>::
    DoTransformStaticMesh(const core_conts::Array<T_VertexType>& a_vertices, 
                          gfx_cs::p_mesh::Static) const 
                          -> const core_conts::Array<T_VertexType>&
  {
    typedef core_conts::Array<T_VertexType>           cont_type;
    typedef T_VertexType                              vert_type;

    // transform the vertices by
    // - copying the vertices
    // - transforming them
    // - returning the new container
    cont_type verticesCopy(a_vertices);

    for (auto& vert : verticesCopy)
    {
      auto pos = math_t::Vec4f32(vert.GetPosition(), 1);
      pos = m_transform * pos;

      vert.SetPosition(pos.ConvertTo<math_t::Vec3f32>());

      DoTransformNormals(&vert);
    }

    return verticesCopy;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_MeshType, typename T_StaticDynamic>
  template <typename T_VertexType>
  auto
    Mesh_T<T_MeshType, T_StaticDynamic>::
    DoTransformStaticMesh(const core_conts::Array<T_VertexType>& a_vertices, 
                          gfx_cs::p_mesh::Dynamic) const 
                          -> const core_conts::Array<T_VertexType>&
  {
    // return without any transformations
    return a_vertices;
  }

};};};

#endif
