#include "tlocMesh.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::Mesh;
  using gfx_cs::mesh_sptr;

  using math_cs::Transform;
  using math_cs::transform_sptr;

  core_cs::Entity*
    CreateMesh(core_cs::EntityManager& a_mgr,
               core_cs::ComponentPoolManager& a_poolMgr,
               core_conts::Array<gfx_cs::Mesh::vert_type> a_vertices)
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef ComponentPoolManager    pool_mgr;

    typedef core_conts::Array<gfx_cs::Mesh::vert_type>      vert_cont;
    typedef vert_cont::iterator                             vert_cont_itr;

    // -----------------------------------------------------------------------

    typedef gfx_cs::mesh_sptr_pool    mesh_pool;
    gfx_cs::mesh_sptr_pool_sptr       meshPool;

    if (a_poolMgr.Exists(mesh) == false)
    { meshPool = a_poolMgr.CreateNewPool<mesh_sptr>(); }
    else
    { meshPool = a_poolMgr.GetPool<mesh_sptr>(); }

    mesh_pool::iterator itrMesh = meshPool->GetNext();
    itrMesh->SetValue(mesh_sptr(new Mesh()) );

    mesh_sptr meshPtr = itrMesh->GetValue();

    for (vert_cont_itr itr = a_vertices.begin(), itrEnd = a_vertices.end();
         itr != itrEnd; ++itr)
    { meshPtr->AddVertex(*itr); }

    // -----------------------------------------------------------------------

    typedef math_cs::transform_f32_sptr_pool      t_pool;
    math_cs::transform_f32_sptr_pool_sptr         tPool;

    if (a_poolMgr.Exists(transform) == false)
    { tPool = a_poolMgr.CreateNewPool<transform_sptr>(); }
    else
    { tPool = a_poolMgr.GetPool<transform_sptr>(); }

    t_pool::iterator  itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // -----------------------------------------------------------------------

    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, itrTransform->GetValue().get() );
    a_mgr.InsertComponent(ent, itrMesh->GetValue().get() );

    return ent;
  }

};};};