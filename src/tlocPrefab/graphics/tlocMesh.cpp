#include "tlocMesh.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::mesh_sptr;

  using math_cs::Transform;
  using math_cs::transform_sptr;

  Mesh::entity_type*
    Mesh::
    Create(const vert_cont_type& a_vertices)
  {
    Entity* ent = m_entMgr->CreateEntity();
    Add(ent, a_vertices);

    return ent;
  }

  void
    Mesh::
    Add(entity_type* a_ent, const vert_cont_type& a_vertices)
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef ComponentPoolManager    pool_mgr;

    typedef core_conts::Array<gfx_cs::Mesh::vert_type>      vert_cont;
    typedef vert_cont::const_iterator                       vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_sptr_pool    mesh_pool;
    gfx_cs::mesh_sptr_pool_sptr       meshPool;

    if (m_compPoolMgr->Exists(mesh) == false)
    { meshPool = m_compPoolMgr->CreateNewPool<mesh_sptr>(); }
    else
    { meshPool = m_compPoolMgr->GetPool<mesh_sptr>(); }

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    itrMesh->SetValue(mesh_sptr(new gfx_cs::Mesh()) );

    mesh_sptr meshPtr = itrMesh->GetValue();

    for (vert_cont_itr itr = a_vertices.begin(), itrEnd = a_vertices.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    // -----------------------------------------------------------------------

    typedef math_cs::transform_f32_sptr_pool      t_pool;
    math_cs::transform_f32_sptr_pool_sptr         tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<transform_sptr>(); }
    else
    { tPool = m_compPoolMgr->GetPool<transform_sptr>(); }

    t_pool::iterator  itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // -----------------------------------------------------------------------

    m_entMgr->InsertComponent(a_ent, itrTransform->GetValue().get() );
    m_entMgr->InsertComponent(a_ent, itrMesh->GetValue().get() );
  }

};};};