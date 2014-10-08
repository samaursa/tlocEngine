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
    , m_texCoords(true)
    , m_normals(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Mesh::component_ptr
    Mesh::
    Construct(const vert_cont_type& a_vertices) const
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef ComponentPoolManager    pool_mgr;

    typedef core_conts::Array<gfx_cs::Mesh::vert_type>      vert_cont;
    typedef vert_cont::const_iterator                       vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_pool                     mesh_pool;

    gfx_cs::mesh_pool_vptr meshPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Mesh>();

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    (*itrMesh)->SetValue(MakeShared<gfx_cs::Mesh>() );

    gfx_cs::mesh_sptr meshPtr = *(*itrMesh)->GetValuePtr();

    for (vert_cont_itr itr = a_vertices.begin(), itrEnd = a_vertices.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    meshPtr->SetTexCoordsEnabled(m_texCoords);
    meshPtr->SetNormalsEnabled(m_normals);

    return meshPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Mesh::entity_ptr
    Mesh::
    Create(const vert_cont_type& a_vertices) const
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_vertices);

    return ent;
  }

  void
    Mesh::
    Add(entity_ptr a_ent, const vert_cont_type& a_vertices) const
  {
    // -----------------------------------------------------------------------
    // Transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // Mesh component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_vertices))
                              .DispatchTo(GetListeners()) );
  }

};};};