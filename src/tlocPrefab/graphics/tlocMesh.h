#ifndef _TLOC_PREFAB_GRAPHICS_MESH_H_
#define _TLOC_PREFAB_GRAPHICS_MESH_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

namespace tloc { namespace prefab { namespace graphics {

  class Mesh
    : public Prefab_TI<Mesh, gfx_cs::Mesh>
  {
  public:
    typedef Mesh                                          this_type;
    typedef Prefab_TI<this_type, component_type>          base_type;

  public:
    Mesh(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    template <typename T_VertexType>
    component_ptr Construct(const core_conts::Array<T_VertexType>& a_vertices) const;

    template <typename T_VertexType>
    entity_ptr   Create(const core_conts::Array<T_VertexType>& a_vertices) const;

    template <typename T_VertexType>
    void         Add(entity_ptr a_ent, 
                     const core_conts::Array<T_VertexType>& a_vertices) const;
  };

  // -----------------------------------------------------------------------
  // template defintions

  template <typename T_VertexType>
  auto
    Mesh::
    Construct(const core_conts::Array<T_VertexType>& a_vertices) const
    -> component_ptr
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef core_cs::ComponentPoolManager                   pool_mgr;

    typedef core_conts::Array<T_VertexType>                 vert_cont;
    typedef vert_cont::const_iterator                       vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_pool                     mesh_pool;

    gfx_cs::mesh_pool_vptr meshPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Mesh>();

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    (*itrMesh)->SetValue(core_sptr::MakeShared<gfx_cs::Mesh>() );

    gfx_cs::mesh_sptr meshPtr = *(*itrMesh)->GetValuePtr();

    for (vert_cont_itr itr = a_vertices.begin(), itrEnd = a_vertices.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    return meshPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_VertexType>
  auto
    Mesh::
    Create(const core_conts::Array<T_VertexType>& a_vertices) const
    -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_vertices);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_VertexType>
  void
    Mesh::
    Add(entity_ptr a_ent, const core_conts::Array<T_VertexType>& a_vertices) const
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

#endif