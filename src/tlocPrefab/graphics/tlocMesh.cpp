#include "tlocMesh.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
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

  Mesh::
    Mesh(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
  { }

  // -----------------------------------------------------------------------
  // explicit instantiations

  typedef Mesh::entity_ptr      entity_ptr;
  typedef Mesh::component_ptr   component_ptr;

  template component_ptr Mesh::Construct(const core_conts::Array<gfx_t::Vert3fpnt>&) const;
  template entity_ptr    Mesh::Create(const core_conts::Array<gfx_t::Vert3fpnt>&) const;
  template void          Mesh::Add(entity_ptr, const core_conts::Array<gfx_t::Vert3fpnt>&) const;

};};};