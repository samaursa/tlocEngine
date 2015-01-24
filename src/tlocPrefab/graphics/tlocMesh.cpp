#include "tlocMesh.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocPrefab/graphics/tlocBoundingBox.h>
#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using gfx_cs::mesh_sptr;

  using math_cs::Transform;
  using math_cs::transform_sptr;

  // ///////////////////////////////////////////////////////////////////////
  // Mesh

#define MESH_TEMPS  typename T_MeshType, typename T_StaticDynamic
#define MESH_PARAMS T_MeshType, T_StaticDynamic

  template <MESH_TEMPS>
  Mesh_T<MESH_PARAMS>::
    Mesh_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_drawMode(gfx_rend::mode::k_triangles)
    , m_bb(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_TEMPS>
  void
    Mesh_T<MESH_PARAMS>::
    DoAddTransformComponent(entity_ptr a_ent, gfx_cs::p_mesh::Dynamic) const
  {
    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_TEMPS>
  void
    Mesh_T<MESH_PARAMS>::
    DoAddTransformComponent(entity_ptr , gfx_cs::p_mesh::Static) const
  {
    // Static meshes don't have a transform component
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_TEMPS>
  void
    Mesh_T<MESH_PARAMS>::
    DoAddBoundingBox(entity_ptr a_ent) const
  {
    if (a_ent->HasComponent<gfx_cs::BoundingBox3D>() == false)
    { pref_gfx::BoundingBox3D(m_entMgr, m_compPoolMgr).Add(a_ent); }
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Mesh_T<gfx_cs::p_mesh::Mesh2D, gfx_cs::p_mesh::Static>;
  template class Mesh_T<gfx_cs::p_mesh::Mesh2D, gfx_cs::p_mesh::Dynamic>;

  template class Mesh_T<gfx_cs::p_mesh::Mesh3D, gfx_cs::p_mesh::Static>;
  template class Mesh_T<gfx_cs::p_mesh::Mesh3D, gfx_cs::p_mesh::Dynamic>;

  typedef Mesh::entity_ptr      entity_ptr;
  typedef Mesh::component_ptr   component_ptr;

  template component_ptr Mesh::Construct(const core_conts::Array<gfx_t::Vert3fpnt>&) const;
  template entity_ptr    Mesh::Create(const core_conts::Array<gfx_t::Vert3fpnt>&) const;
  template void          Mesh::Add(entity_ptr, const core_conts::Array<gfx_t::Vert3fpnt>&) const;

};};};